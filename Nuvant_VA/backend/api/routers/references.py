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
    path = _resolve_image_path(log.image_path)
    if not path:
        raise HTTPException(404, "Archivo de imagen no encontrado")
    return FileResponse(path=path, media_type="image/jpeg")


@router.get("/defect/{defect_log_id}/heatmap")
def get_defect_heatmap(defect_log_id: int, db: Session = Depends(get_db)):
    """Sirve el heatmap PNG del defecto (si existe)."""
    log = db.query(DefectLog).filter(DefectLog.id == defect_log_id).first()
    if not log or not log.image_path or not log.image_path.strip():
        raise HTTPException(404, "Defecto sin imagen")
    img_path = _resolve_image_path(log.image_path)
    if not img_path:
        raise HTTPException(404, "Imagen base no encontrada")
    stem = img_path.rsplit(".", 1)[0]
    heatmap_path = stem + "_heatmap.png"
    if not os.path.isfile(heatmap_path):
        raise HTTPException(404, "Heatmap no disponible")
    return FileResponse(path=heatmap_path, media_type="image/png")


@router.get("/{ref_id}/unclassified_defects")
def list_unclassified_defects(ref_id: int, db: Session = Depends(get_db)):
    """Cola de defectos sin clasificar. Incluye has_image y has_heatmap para la UI."""
    ref = db.query(Reference).filter(Reference.id == ref_id).first()
    if not ref:
        raise HTTPException(404, "Referencia no encontrada")
    sin_clasificar = db.query(DefectType).filter(DefectType.name == "Sin clasificar").first()
    q = db.query(DefectLog).filter(DefectLog.reference_id == ref_id, DefectLog.is_defect == 1)
    if sin_clasificar:
        q = q.filter((DefectLog.defect_type_id.is_(None)) | (DefectLog.defect_type_id == sin_clasificar.id))
    else:
        q = q.filter(DefectLog.defect_type_id.is_(None))
    rows = q.order_by(DefectLog.timestamp.desc()).all()

    result = []
    for r in rows:
        img_path = _resolve_image_path(r.image_path) if (r.image_path and r.image_path.strip()) else ""
        has_image = bool(img_path)
        has_heatmap = bool(img_path) and os.path.isfile(img_path.rsplit(".", 1)[0] + "_heatmap.png")
        result.append({
            "id": r.id,
            "timestamp": r.timestamp.isoformat() if r.timestamp else None,
            "anomaly_score": round(r.anomaly_score, 4),
            "inspection_id": r.inspection_id,
            "has_image": has_image,
            "has_heatmap": has_heatmap,
        })
    return result


@router.get("/{ref_id}/classified_defects")
def list_classified_defects(ref_id: int, limit: int = 100, db: Session = Depends(get_db)):
    """Lista defectos ya clasificados (excluye Sin clasificar y NULL)."""
    ref = db.query(Reference).filter(Reference.id == ref_id).first()
    if not ref:
        raise HTTPException(404, "Referencia no encontrada")
    sin_clasificar = db.query(DefectType).filter(DefectType.name == "Sin clasificar").first()
    q = db.query(DefectLog).filter(DefectLog.reference_id == ref_id, DefectLog.is_defect == 1)
    q = q.filter(DefectLog.defect_type_id.isnot(None))
    if sin_clasificar:
        q = q.filter(DefectLog.defect_type_id != sin_clasificar.id)
    rows = q.order_by(DefectLog.timestamp.desc()).limit(limit).all()

    result = []
    for r in rows:
        dtype = db.get(DefectType, r.defect_type_id) if r.defect_type_id else None
        img_path = _resolve_image_path(r.image_path) if (r.image_path and r.image_path.strip()) else ""
        has_image = bool(img_path)
        has_heatmap = bool(img_path) and os.path.isfile(img_path.rsplit(".", 1)[0] + "_heatmap.png")
        result.append({
            "id": r.id,
            "timestamp": r.timestamp.isoformat() if r.timestamp else None,
            "anomaly_score": round(r.anomaly_score, 4),
            "defect_type": dtype.name if dtype else "Desconocido",
            "inspection_id": r.inspection_id,
            "has_image": has_image,
            "has_heatmap": has_heatmap,
        })
    return result


def _resolve_image_path(path: str) -> str:
    """
    Resuelve ruta de imagen; retorna path absoluto si existe, o vacío.
    Soporta:
      - Ruta absoluta directa (en contenedor o host)
      - Ruta con prefijo /app/local_storage/ (contenedor)
      - Ruta con segmento local_storage/ (legacy y modular)
    """
    if not path or not path.strip():
        return ""

    candidates = [os.path.abspath(path)]

    path_norm = path.replace("\\", "/")

    # Modular path en contenedor: /app/local_storage/line_X/point_Y/...
    if "/app/local_storage/" in path_norm and STORAGE_DIR:
        rel = path_norm.split("/app/local_storage/")[-1].lstrip("/")
        if rel:
            candidates.append(str(STORAGE_DIR / rel))

    # Legacy path con local_storage/
    if "local_storage/" in path_norm and STORAGE_DIR:
        rel = path_norm.split("local_storage/")[-1].lstrip("/")
        if rel:
            candidates.append(str(STORAGE_DIR / rel))

    # Si STORAGE_DIR está definido y la ruta parece relativa
    if STORAGE_DIR and not os.path.isabs(path):
        candidates.append(str(STORAGE_DIR / path.lstrip("/")))

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
    """
    Borra archivos de imagen y heatmap de defectos. Vacía image_path SOLO si el archivo
    fue encontrado y borrado exitosamente. Si no se encuentra, conserva el path original
    para reintentos futuros.
    Retorna cantidad de imágenes borradas.
    """
    deleted = 0
    for r in rows:
        if not r.image_path or not r.image_path.strip():
            continue
        path = _resolve_image_path(r.image_path)
        if not path:
            # Archivo no encontrado → conservar image_path para no perder referencia
            continue
        try:
            if os.path.isfile(path):
                os.remove(path)
                deleted += 1
                # Borrar heatmap asociado (mismo stem + _heatmap.png)
                stem = path.rsplit(".", 1)[0]
                heatmap_path = stem + "_heatmap.png"
                if os.path.isfile(heatmap_path):
                    try:
                        os.remove(heatmap_path)
                    except OSError:
                        pass
                r.image_path = ""
        except OSError as e:
            print(f"[Report] No se pudo borrar {path}: {e}")
    db.commit()
    return deleted


def _read_heatmap_base64(image_path: str) -> str:
    """Lee heatmap PNG asociado a una imagen y retorna data URI base64."""
    resolved = _resolve_image_path(image_path)
    if not resolved:
        return ""
    stem = resolved.rsplit(".", 1)[0]
    heatmap_path = stem + "_heatmap.png"
    if not os.path.isfile(heatmap_path):
        return ""
    try:
        with open(heatmap_path, "rb") as f:
            b64 = base64.b64encode(f.read()).decode("utf-8")
        return f"data:image/png;base64,{b64}"
    except OSError:
        return ""


def _build_report_html(ref_name: str, ref_id: int, rows: list, db, unclassified_count: int = 0):
    """Construye HTML con imágenes embebidas, heatmap overlay y lightbox para zoom."""
    rows_data = []
    for r in rows:
        dtype = db.get(DefectType, r.defect_type_id) if r.defect_type_id else None
        img_data = _read_image_base64(r.image_path) if r.image_path else ""
        heatmap_data = _read_heatmap_base64(r.image_path) if r.image_path else ""
        rows_data.append({
            "id": r.id,
            "timestamp": r.timestamp.strftime("%Y-%m-%d %H:%M:%S") if r.timestamp else "-",
            "score": round(r.anomaly_score, 4),
            "clasificacion": dtype.name if dtype else "Sin clasificar",
            "img_src": img_data,
            "heatmap_src": heatmap_data,
        })

    rows_html = ""
    for i, d in enumerate(rows_data):
        uid = f"def_{d['id']}"
        if d["img_src"]:
            if d["heatmap_src"]:
                img_tag = f'''
                <div class="img-wrap" onclick="openLightbox('{uid}')">
                  <img src="{d['img_src']}" alt="defecto" class="thumb"/>
                  <img src="{d['heatmap_src']}" alt="heatmap" class="heatmap-overlay"/>
                  <span class="zoom-hint">🔍 Zoom</span>
                </div>
                <div id="lb_{uid}" class="lightbox" onclick="this.style.display='none'">
                  <div class="lb-inner" onclick="event.stopPropagation()">
                    <button class="lb-close" onclick="document.getElementById('lb_{uid}').style.display='none'">✕</button>
                    <div class="lb-toggle">
                      <button onclick="toggleHeatmapLb('{uid}',false)">Imagen</button>
                      <button onclick="toggleHeatmapLb('{uid}',true)">Heatmap</button>
                    </div>
                    <div class="lb-imgs">
                      <img id="lbimg_{uid}" src="{d['img_src']}" class="lb-img"/>
                      <img id="lbheat_{uid}" src="{d['heatmap_src']}" class="lb-img" style="display:none;opacity:0.7"/>
                    </div>
                    <p>ID: {d['id']} | Score: {d['score']} | {d['clasificacion']}</p>
                  </div>
                </div>'''
            else:
                img_tag = f'''
                <div class="img-wrap" onclick="openLightbox('{uid}')">
                  <img src="{d['img_src']}" alt="defecto" class="thumb"/>
                  <span class="zoom-hint">🔍 Zoom</span>
                </div>
                <div id="lb_{uid}" class="lightbox" onclick="this.style.display='none'">
                  <div class="lb-inner" onclick="event.stopPropagation()">
                    <button class="lb-close" onclick="document.getElementById('lb_{uid}').style.display='none'">✕</button>
                    <img src="{d['img_src']}" class="lb-img"/>
                    <p>ID: {d['id']} | Score: {d['score']} | {d['clasificacion']}</p>
                  </div>
                </div>'''
        else:
            img_tag = '<span class="no-img">Sin imagen</span>'

        badge_cls = "badge-ok" if d["clasificacion"] != "Sin clasificar" else "badge-pending"
        rows_html += f"""
        <div class="defect-card">
          <div class="defect-meta">
            <span class="defect-id">#{ d['id']}</span>
            <span class="defect-ts">{d['timestamp']}</span>
            <span class="defect-score">Score: {d['score']}</span>
            <span class="badge {badge_cls}">{d['clasificacion']}</span>
          </div>
          <div class="defect-img">{img_tag}</div>
        </div>"""

    total = len(rows_data)
    sin_cls = sum(1 for d in rows_data if d["clasificacion"] == "Sin clasificar")
    con_img = sum(1 for d in rows_data if d["img_src"])
    warn_banner = (
        f'<p class="subtitle" style="background:#7c2d12;color:#fca5a5;padding:10px;border-radius:8px;margin-bottom:16px;">'
        f'⚠️ Este informe incluye {unclassified_count} defecto(s) sin clasificar. Use la cola de clasificación para completarlos.</p>'
        if unclassified_count > 0 else ""
    )

    html = f"""<!DOCTYPE html>
<html lang="es">
<head>
<meta charset="UTF-8"/>
<title>Reporte {ref_name}</title>
<style>
*{{box-sizing:border-box;margin:0;padding:0;}}
body{{font-family:'Segoe UI',sans-serif;background:#0f172a;color:#e2e8f0;padding:24px;}}
h1{{color:#38bdf8;font-size:1.8rem;margin-bottom:4px;}}
.subtitle{{color:#64748b;font-size:.9rem;margin-bottom:20px;}}
.stats{{display:flex;gap:16px;margin-bottom:24px;flex-wrap:wrap;}}
.stat-box{{background:#1e293b;border:1px solid #334155;border-radius:10px;padding:12px 20px;text-align:center;}}
.stat-box .val{{font-size:2rem;font-weight:bold;color:#38bdf8;}}
.stat-box .lbl{{font-size:.75rem;color:#64748b;margin-top:2px;}}
.defect-grid{{display:grid;grid-template-columns:repeat(auto-fill,minmax(320px,1fr));gap:16px;}}
.defect-card{{background:#1e293b;border:1px solid #334155;border-radius:12px;overflow:hidden;}}
.defect-meta{{padding:12px;display:flex;flex-wrap:wrap;gap:8px;align-items:center;border-bottom:1px solid #334155;}}
.defect-id{{font-weight:bold;color:#94a3b8;font-size:.85rem;}}
.defect-ts{{color:#64748b;font-size:.8rem;flex:1;}}
.defect-score{{font-size:.8rem;color:#fbbf24;}}
.badge{{padding:3px 10px;border-radius:999px;font-size:.75rem;font-weight:bold;}}
.badge-ok{{background:#065f46;color:#6ee7b7;}}
.badge-pending{{background:#7c2d12;color:#fca5a5;}}
.defect-img{{padding:12px;display:flex;justify-content:center;}}
.img-wrap{{position:relative;cursor:pointer;display:inline-block;}}
.thumb{{max-width:280px;max-height:200px;border-radius:6px;display:block;}}
.heatmap-overlay{{position:absolute;top:0;left:0;width:100%;height:100%;border-radius:6px;opacity:0.5;transition:opacity .2s;}}
.img-wrap:hover .heatmap-overlay{{opacity:0.75;}}
.zoom-hint{{position:absolute;bottom:6px;right:8px;background:rgba(0,0,0,.7);color:#fff;font-size:.7rem;padding:2px 6px;border-radius:4px;}}
.no-img{{color:#475569;font-size:.85rem;font-style:italic;}}
.lightbox{{display:none;position:fixed;inset:0;background:rgba(0,0,0,.85);z-index:9999;justify-content:center;align-items:center;}}
.lightbox{{display:none;position:fixed;inset:0;background:rgba(0,0,0,.85);z-index:9999;}}
.lb-inner{{position:absolute;top:50%;left:50%;transform:translate(-50%,-50%);background:#1e293b;border-radius:14px;padding:24px;max-width:90vw;max-height:90vh;overflow:auto;text-align:center;}}
.lb-img{{max-width:80vw;max-height:70vh;border-radius:8px;display:block;margin:0 auto 12px;}}
.lb-close{{position:absolute;top:12px;right:16px;background:#ef4444;color:#fff;border:none;border-radius:50%;width:28px;height:28px;font-size:1rem;cursor:pointer;}}
.lb-toggle{{margin-bottom:12px;display:flex;gap:8px;justify-content:center;}}
.lb-toggle button{{background:#334155;color:#e2e8f0;border:1px solid #475569;border-radius:6px;padding:4px 14px;cursor:pointer;font-size:.85rem;}}
.lb-toggle button:hover{{background:#475569;}}
</style>
</head>
<body>
<h1>Reporte de Inspección — {ref_name}</h1>
<p class="subtitle">Referencia ID: {ref_id} | Generado: {datetime.utcnow().strftime("%Y-%m-%d %H:%M:%S")} UTC</p>
{warn_banner}
<div class="stats">
  <div class="stat-box"><div class="val">{total}</div><div class="lbl">Total Defectos</div></div>
  <div class="stat-box"><div class="val">{total - sin_cls}</div><div class="lbl">Clasificados</div></div>
  <div class="stat-box"><div class="val">{sin_cls}</div><div class="lbl">Sin Clasificar</div></div>
  <div class="stat-box"><div class="val">{con_img}</div><div class="lbl">Con Imagen</div></div>
</div>
<div class="defect-grid">{rows_html}</div>
<script>
function openLightbox(uid){{document.getElementById('lb_'+uid).style.display='block';}}
function toggleHeatmapLb(uid,showHeat){{
  var img=document.getElementById('lbimg_'+uid);
  var heat=document.getElementById('lbheat_'+uid);
  if(img)img.style.display=showHeat?'none':'block';
  if(heat)heat.style.display=showHeat?'block':'none';
}}
</script>
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
    # Permitir informe con defectos clasificados Y sin clasificar (mostrar ambos)
    sin_cls_type = db.query(DefectType).filter(DefectType.name == "Sin clasificar").first()
    sin_cls_id = sin_cls_type.id if sin_cls_type else None
    sin_clasificar = sum(
        1 for r in rows
        if r.defect_type_id is None or (sin_cls_id is not None and r.defect_type_id == sin_cls_id)
    )
    html, _ = _build_report_html(ref.name, ref_id, rows, db, unclassified_count=sin_clasificar)
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
    if not rows and insp.started_at:
        # Fallback: defectos con inspection_id=NULL guardados dentro del rango de esta inspección.
        # Acotado por started_at/stopped_at para evitar incluir entradas de otras sesiones.
        stopped = insp.stopped_at or datetime.utcnow()
        rows = (
            db.query(DefectLog)
            .filter(
                DefectLog.reference_id == ref_id,
                DefectLog.inspection_id.is_(None),
                DefectLog.is_defect == 1,
                DefectLog.timestamp >= insp.started_at,
                DefectLog.timestamp <= stopped,
            )
            .order_by(DefectLog.timestamp)
            .all()
        )
    # Permitir defectos sin clasificar en el informe (mostrar ambos)
    sin_cls_type = db.query(DefectType).filter(DefectType.name == "Sin clasificar").first()
    sin_cls_id = sin_cls_type.id if sin_cls_type else None
    uncl = sum(1 for r in rows if r.defect_type_id is None or (sin_cls_id and r.defect_type_id == sin_cls_id))
    html, _ = _build_report_html(ref.name, ref_id, rows, db, unclassified_count=uncl)
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
