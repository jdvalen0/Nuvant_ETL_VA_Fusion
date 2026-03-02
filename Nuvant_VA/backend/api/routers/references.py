from fastapi import APIRouter, Depends, HTTPException, UploadFile, File, BackgroundTasks
from sqlalchemy.orm import Session
from backend.db.database import SessionLocal, Reference
from backend.core.features import FeatureExtractor
from backend.core.anomaly import AnomalyDetector
from backend.config import STORAGE_DIR, get_storage_path
import shutil
import os
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
        # Manually cascade delete logs (SQLAlchemy relationship cascade not strictly enforced in code)
        from backend.db.database import DefectLog
        db.query(DefectLog).filter(DefectLog.reference_id == ref_id).delete()
        
        # Delete the reference
        db.delete(ref)
        db.commit()
    except Exception as e:
        db.rollback()
        print(f"DB Error deleting reference: {e}")
        raise HTTPException(500, f"Database error deleting reference: {str(e)}")

    # Delete folder
    ref_path = get_storage_path(ref_id)
    _delete_folder_robust(str(ref_path))
    
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
