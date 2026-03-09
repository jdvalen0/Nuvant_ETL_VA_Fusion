import base64
import os
from datetime import datetime
from fastapi import APIRouter, Depends, HTTPException, UploadFile, File, BackgroundTasks, Query
from fastapi.responses import StreamingResponse, FileResponse
from sqlalchemy.orm import Session
from backend.db.database import SessionLocal, Reference, DefectLog, DefectType, Inspection
from backend.core.features import FeatureExtractor
from backend.core.anomaly import AnomalyDetector
from backend.config import STORAGE_DIR, REPORTS_DIR, get_storage_path
import shutil
import cv2
import joblib
import numpy as np

router = APIRouter()

from pydantic import BaseModel
class TrainRequest(BaseModel):
    contamination: float = 0.01
    pca_variance: float = 0.95
    sensitivity: float = 0.0

# Dependency
def get_db():
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()

# Use config based storage path logic
def _delete_folder_robust(path: str):
    """Attempts to delete a folder, handling potential lock errors."""
    if not os.path.exists(path):
        return
    try:
        shutil.rmtree(path)
    except OSError as e:
        print(f"Error deleting {path}: {e}")
        # Simplistic retry or ignore logic - in prod, might rename first then delete
        # On linux, open files usually don't block deletion (unlink), but it's good practice
        pass

@router.post("/")
def create_reference(name: str, db: Session = Depends(get_db)):
    if db.query(Reference).filter(Reference.name == name).first():
        raise HTTPException(status_code=400, detail="Reference name already exists")
    
    ref = Reference(name=name)
    db.add(ref)
    db.commit()
    db.refresh(ref)
    
    # Create folder for this reference
    ref_path = get_storage_path(ref.id)
    os.makedirs(ref_path, exist_ok=True)
    
    return ref

@router.post("/{ref_id}/upload_samples")
async def upload_samples(ref_id: int, files: list[UploadFile] = File(...), db: Session = Depends(get_db)):
    ref = db.query(Reference).filter(Reference.id == ref_id).first()
    if not ref:
        raise HTTPException(404, "Reference not found")
        
    ref_dir = get_storage_path(ref_id) / "samples"
    os.makedirs(ref_dir, exist_ok=True)
    
    saved_files = []
    for file in files:
        file_path = ref_dir / file.filename
        with open(file_path, "wb") as buffer:
            shutil.copyfileobj(file.file, buffer)
        saved_files.append(str(file_path))
        
    return {"message": f"Uploaded {len(saved_files)} images", "paths": saved_files}

def _train_task(ref_id: int, cont: float, pca_v: float, sens: float, db_session_factory):
    """Tarea de fondo para realizar el entrenamiento sin bloquear la API."""
    db = db_session_factory()
    try:
        ref = db.query(Reference).filter(Reference.id == ref_id).first()
        if not ref:
            return

        ref_dir = get_storage_path(ref_id) / "samples"
        image_paths = [os.path.join(ref_dir, f) for f in os.listdir(ref_dir) if f.lower().endswith(('.png', '.jpg', '.jpeg'))]
        
        images = []
        for path in image_paths:
            img = cv2.imread(path)
            if img is not None:
                images.append(img)

        if not images:
            print(f"[BackgroundTask] Error: No se pudieron cargar imágenes para ref {ref_id}")
            return

        try:
            from backend.core.anomaly_patchcore import AnomalyDetectorV32
            detector = AnomalyDetectorV32()
            print(f"[BackgroundTask] Usando PatchCore V32 para ref {ref_id}")
        except ImportError:
            from backend.core.anomaly import AnomalyDetector
            detector = AnomalyDetector()
            print(f"[BackgroundTask] Usando Mahalanobis V31 fallback para ref {ref_id}")

        print(f"[BackgroundTask] Iniciando entrenamiento para ref {ref_id} con {len(images)} imágenes...")
        detector.train(images=images, contamination=cont)

        # Save model
        model_path = get_storage_path(ref_id) / "model.pkl"
        detector.save(str(model_path))

        ref.model_path = str(model_path)
        ref.params = {
            "contamination": cont,
            "pca_variance": pca_v,
            "sensitivity": sens,
            "status": "trained"
        }
        db.commit()

        # Clear cache
        from backend.api.routers.inference import clear_model_cache
        clear_model_cache(ref_id)
        print(f"[BackgroundTask] Entrenamiento completado para ref {ref_id}")

    except Exception as e:
        print(f"[BackgroundTask] Error durante el entrenamiento: {e}")
        try:
            ref = db.query(Reference).filter(Reference.id == ref_id).first()
            if ref:
                params = ref.params or {}
                params["status"] = "error"
                params["error_msg"] = str(e)
                ref.params = params
                db.commit()
        except:
            pass
    finally:
        db.close()

@router.post("/{ref_id}/train")
async def train_reference(ref_id: int, background_tasks: BackgroundTasks, req: TrainRequest = None, db: Session = Depends(get_db)):
    ref = db.query(Reference).filter(Reference.id == ref_id).first()
    if not ref:
        raise HTTPException(404, "Reference not found")
    
    ref_dir = get_storage_path(ref_id) / "samples"
    if not os.path.exists(ref_dir) or not os.listdir(ref_dir):
        raise HTTPException(400, "No samples uploaded yet")
    
    # Use request params if provided, else defaults
    cont = req.contamination if req else 0.01
    pca_v = req.pca_variance if req else 0.95
    sens = req.sensitivity if req else 0.0

    # Marcar como "entrenando" para que la UI sepa
    params = ref.params or {}
    params["status"] = "training"
    ref.params = params
    db.commit()

    # Encolar la tarea
    background_tasks.add_task(_train_task, ref_id, cont, pca_v, sens, SessionLocal)
    
    return {
        "status": "training_started", 
        "message": "El entrenamiento se ha iniciado en segundo plano. La interfaz se actualizará al finalizar.",
        "ref_id": ref_id
    }

@router.delete("/{ref_id}")
def delete_reference(ref_id: int, db: Session = Depends(get_db)):
    ref = db.query(Reference).filter(Reference.id == ref_id).first()
    if not ref:
        raise HTTPException(404, "Reference not found")
        
    try:
        from backend.db.database import DefectLog
        db.query(DefectLog).filter(DefectLog.reference_id == ref_id).delete()
        db.query(Inspection).filter(Inspection.reference_id == ref_id).delete()
        db.delete(ref)
        db.commit()
    except Exception as e:
        db.rollback()
        print(f"DB Error deleting reference: {e}")
        raise HTTPException(500, f"Database error deleting reference: {str(e)}")

    # Delete folders: legacy (local_storage/ref_id) y modular (line_1/point_1/ref_id)
    ref_path = get_storage_path(ref_id)
    _delete_folder_robust(str(ref_path))
    mod_path = STORAGE_DIR / "line_1" / "point_1" / str(ref_id)
    _delete_folder_robust(str(mod_path))
    
    # Notify Inference Engine to clear cache (Global state hack for prototype)
    # Ideally use a proper Event Bus or Shared Manager
    from backend.api.routers.inference import clear_model_cache
    clear_model_cache(ref_id)
    
    return {"status": "deleted", "id": ref_id}

@router.get("/defect_types")
def list_defect_types(db: Session = Depends(get_db)):
    from backend.db.database import DefectType
    return db.query(DefectType).all()

@router.post("/defect_types")
def create_defect_type(name: str, db: Session = Depends(get_db)):
    from backend.db.database import DefectType
    
    # Check if already exists
    existing = db.query(DefectType).filter(DefectType.name == name).first()
    if existing:
        raise HTTPException(400, "Defect type already exists")
    
    new_type = DefectType(name=name)
    db.add(new_type)
    db.commit()
    db.refresh(new_type)
    return new_type

@router.get("/")
def list_references(db: Session = Depends(get_db)):
    return db.query(Reference).all()


@router.get("/defect/{defect_log_id}/image")
def get_defect_image(defect_log_id: int, db: Session = Depends(get_db)):
    """Sirve la imagen de un defecto para la interfaz de clasificación."""
    log = db.query(DefectLog).filter(DefectLog.id == defect_log_id).first()
    if not log or not log.image_path or not log.image_path.strip():
        raise HTTPException(404, "Imagen no disponible")
    path = os.path.abspath(log.image_path)
    if not os.path.isfile(path):
        raise HTTPException(404, "Archivo de imagen no encontrado")
    return FileResponse(path=path, media_type="image/jpeg")


@router.get("/{ref_id}/unclassified_defects")
def list_unclassified_defects(ref_id: int, db: Session = Depends(get_db)):
    """Cola de defectos sin clasificar (NULL o tipo 'Sin clasificar')."""
    ref = db.query(Reference).filter(Reference.id == ref_id).first()
    if not ref:
        raise HTTPException(404, "Referencia no encontrada")
    sin_clasificar = db.query(DefectType).filter(DefectType.name == "Sin clasificar").first()
    q = db.query(DefectLog).filter(DefectLog.reference_id == ref_id, DefectLog.is_defect == 1)
    if sin_clasificar:
        q = q.filter((DefectLog.defect_type_id.is_(None)) | (DefectLog.defect_type_id == sin_clasificar.id))
    else:
        q = q.filter(DefectLog.defect_type_id.is_(None))
    rows = q.order_by(DefectLog.timestamp).all()
    return [
        {
            "id": r.id,
            "timestamp": r.timestamp.isoformat() if r.timestamp else None,
            "anomaly_score": round(r.anomaly_score, 4),
            "has_image": bool(r.image_path and r.image_path.strip()),
        }
        for r in rows
    ]


def _resolve_image_path(path: str) -> str:
    """Resuelve ruta de imagen; retorna path absoluto si existe, o vacío."""
    if not path or not path.strip():
        return ""
    candidates = [os.path.abspath(path)]
    if STORAGE_DIR:
        path_norm = path.replace("\\", "/")
        if "local_storage" in path_norm:
            rel = path_norm.split("local_storage/")[-1].lstrip("/")
            if rel:
                candidates.append(str(STORAGE_DIR / rel))
    for p in candidates:
        if os.path.isfile(p):
            return p
    return ""


def _read_image_base64(path: str) -> str:
    """Lee imagen y retorna data URI base64. Vacío si no existe."""
    p = _resolve_image_path(path)
    if not p:
        return ""
    try:
        with open(p, "rb") as f:
            b64 = base64.b64encode(f.read()).decode("utf-8")
        return f"data:image/jpeg;base64,{b64}"
    except OSError:
        return ""


def _delete_defect_images(rows, db) -> int:
    """Borra archivos de imagen de defectos y vacía image_path en DB. Retorna cantidad borrada."""
    deleted = 0
    for r in rows:
        if not r.image_path or not r.image_path.strip():
            continue
        path = _resolve_image_path(r.image_path)
        if not path:
            continue
        try:
            if os.path.isfile(path):
                os.remove(path)
                deleted += 1
        except OSError as e:
            print(f"[Report] No se pudo borrar {path}: {e}")
        r.image_path = ""
    db.commit()
    return deleted


def _build_report_html(ref_name: str, ref_id: int, rows: list, db):
    """Construye HTML con imágenes embebidas."""
    rows_data = []
    for r in rows:
        dtype = db.get(DefectType, r.defect_type_id) if r.defect_type_id else None
        img_data = _read_image_base64(r.image_path) if r.image_path else ""
        rows_data.append({
            "id": r.id,
            "timestamp": r.timestamp.strftime("%Y-%m-%d %H:%M:%S") if r.timestamp else "-",
            "score": round(r.anomaly_score, 4),
            "clasificacion": dtype.name if dtype else "Sin clasificar",
            "img_src": img_data,
        })

    rows_html = ""
    for d in rows_data:
        img_tag = f'<img src="{d["img_src"]}" alt="defecto" style="max-width:200px;max-height:150px;"/>' if d["img_src"] else '<span style="color:#888">Imagen no disponible</span>'
        rows_html += f"""
        <tr>
            <td>{d["id"]}</td>
            <td>{d["timestamp"]}</td>
            <td>{d["score"]}</td>
            <td>{d["clasificacion"]}</td>
            <td>{img_tag}</td>
        </tr>"""

    html = f"""<!DOCTYPE html>
<html lang="es">
<head><meta charset="UTF-8"/><title>Reporte {ref_name}</title>
<style>
body{{font-family:sans-serif;margin:20px;background:#1e293b;color:#e2e8f0;}}
h1{{color:#38bdf8;}}
table{{border-collapse:collapse;width:100%;margin-top:20px;}}
th,td{{border:1px solid #475569;padding:8px;text-align:left;}}
th{{background:#334155;color:#94a3b8;}}
tr:nth-child(even){{background:#0f172a;}}
</style>
</head>
<body>
<h1>Reporte de Inspección — {ref_name}</h1>
<p>Referencia ID: {ref_id} | Generado: {datetime.utcnow().strftime("%Y-%m-%d %H:%M:%S")} UTC</p>
<table>
<thead><tr><th>ID</th><th>Fecha/Hora</th><th>Score</th><th>Clasificación</th><th>Imagen</th></tr></thead>
<tbody>{rows_html}</tbody>
</table>
</body>
</html>"""
    return html, rows


@router.get("/{ref_id}/report")
def report_by_reference(
    ref_id: int,
    db: Session = Depends(get_db),
    date_from: str = Query(None, description="YYYY-MM-DD"),
    date_to: str = Query(None, description="YYYY-MM-DD"),
):
    """
    Informe solo tras clasificación. Documento HTML con imágenes embebidas. Tras generar: borra imágenes, conserva informe.
    Requiere TODOS los defectos clasificados.
    """
    ref = db.query(Reference).filter(Reference.id == ref_id).first()
    if not ref:
        raise HTTPException(404, "Referencia no encontrada")

    q = db.query(DefectLog).filter(DefectLog.reference_id == ref_id, DefectLog.is_defect == 1)
    if date_from:
        try:
            df = datetime.strptime(date_from, "%Y-%m-%d")
            q = q.filter(DefectLog.timestamp >= df)
        except ValueError:
            pass
    if date_to:
        try:
            dt = datetime.strptime(date_to, "%Y-%m-%d")
            dt = dt.replace(hour=23, minute=59, second=59, microsecond=999999)
            q = q.filter(DefectLog.timestamp <= dt)
        except ValueError:
            pass

    rows = q.order_by(DefectLog.timestamp).all()
    sin_clasificar = sum(1 for r in rows if r.defect_type_id is None)
    if sin_clasificar > 0:
        raise HTTPException(400, f"Debe clasificar TODOS los defectos. Quedan {sin_clasificar} sin clasificar. Use la cola de clasificación.")

    html, _ = _build_report_html(ref.name, ref_id, rows, db)
    images_deleted = _delete_defect_images(rows, db)

    fname = f"reporte_ref_{ref_id}_{datetime.utcnow().strftime('%Y%m%d_%H%M%S')}.html"
    report_path = REPORTS_DIR / fname
    with open(report_path, "w", encoding="utf-8") as f:
        f.write(html)

    from fastapi.responses import FileResponse
    return FileResponse(
        path=str(report_path),
        filename=fname,
        media_type="text/html",
        headers={"X-Images-Deleted": str(images_deleted)},
    )


@router.get("/{ref_id}/inspections")
def list_inspections(ref_id: int, db: Session = Depends(get_db)):
    """Lista inspecciones de una referencia (sesiones Iniciar→Detener)."""
    ref = db.query(Reference).filter(Reference.id == ref_id).first()
    if not ref:
        raise HTTPException(404, "Referencia no encontrada")
    rows = (
        db.query(Inspection)
        .filter(Inspection.reference_id == ref_id)
        .order_by(Inspection.started_at.desc())
        .all()
    )
    return [
        {
            "id": r.id,
            "reference_id": r.reference_id,
            "started_at": r.started_at.isoformat() if r.started_at else None,
            "stopped_at": r.stopped_at.isoformat() if r.stopped_at else None,
        }
        for r in rows
    ]


@router.get("/{ref_id}/inspections/{inspection_id}/report")
def report_by_inspection(
    ref_id: int,
    inspection_id: int,
    db: Session = Depends(get_db),
):
    """
    Informe de una inspección concreta. Solo defectos de esa inspección.
    Tras generar: borra solo imágenes de defectos de esta inspección.
    """
    insp = db.query(Inspection).filter(
        Inspection.id == inspection_id,
        Inspection.reference_id == ref_id,
    ).first()
    if not insp:
        raise HTTPException(404, "Inspección no encontrada")
    ref = db.query(Reference).filter(Reference.id == ref_id).first()
    if not ref:
        raise HTTPException(404, "Referencia no encontrada")

    rows = (
        db.query(DefectLog)
        .filter(
            DefectLog.reference_id == ref_id,
            DefectLog.inspection_id == inspection_id,
            DefectLog.is_defect == 1,
        )
        .order_by(DefectLog.timestamp)
        .all()
    )
    if not rows:
        # Fallback: defectos con inspection_id=NULL (race, bridge sin inspection_id)
        rows = (
            db.query(DefectLog)
            .filter(
                DefectLog.reference_id == ref_id,
                DefectLog.inspection_id.is_(None),
                DefectLog.is_defect == 1,
            )
            .order_by(DefectLog.timestamp)
            .all()
        )
    # Permitir defectos sin clasificar (tipo "Sin clasificar") en el informe
    html, _ = _build_report_html(ref.name, ref_id, rows, db)
    images_deleted = _delete_defect_images(rows, db)

    fname = f"reporte_inspeccion_{inspection_id}_{datetime.utcnow().strftime('%Y%m%d_%H%M%S')}.html"
    report_path = REPORTS_DIR / fname
    with open(report_path, "w", encoding="utf-8") as f:
        f.write(html)

    from fastapi.responses import FileResponse
    return FileResponse(
        path=str(report_path),
        filename=fname,
        media_type="text/html",
        headers={"X-Images-Deleted": str(images_deleted)},
    )
