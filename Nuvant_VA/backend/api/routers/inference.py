"""
Nuvant VA — Inference Router V2
Soporta multi-punto: ACTIVE_MODEL y ConnectionManager indexados por (line_id, point_id).

Fase actual: 1 línea (id=1), 1 punto (id=1).
Escalar a más líneas/puntos no requiere cambios en este archivo.
"""
import asyncio
import base64
import json
import os
import time
from datetime import datetime
from typing import Dict, Any

import cv2
import numpy as np
from fastapi import APIRouter, Depends, WebSocket, WebSocketDisconnect
from pydantic import BaseModel
from sqlalchemy.orm import Session

from backend.db.database import (
    DefectLog, DefectType, Reference, InspectionPoint,
    ProductionLine, SessionLocal
)
from backend.core.features import FeatureExtractor
from backend.core.anomaly import AnomalyDetector

try:
    from backend.core.anomaly_patchcore import PatchCoreDetector, AnomalyDetectorV32
    PATCHCORE_AVAILABLE = True
except ImportError:
    PATCHCORE_AVAILABLE = False
    print("[Warning] PatchCore V32 not available, using V31 fallback")

router = APIRouter()

# ══════════════════════════════════════════════════════════════════════════════
# CACHE DE MODELOS — por (line_id, point_id)
# Fase actual: solo {(1, 1): {...}}
# ══════════════════════════════════════════════════════════════════════════════
_model_cache: Dict[tuple, Dict[str, Any]] = {}
_cache_lock = asyncio.Lock()
_shared_extractor = FeatureExtractor()


def get_db():
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()


def _resolve_active_ref(point_id: int, db: Session):
    """Retorna la referencia entrenada más reciente del punto."""
    ref = (
        db.query(Reference)
        .filter(Reference.point_id == point_id, Reference.model_path.isnot(None))
        .order_by(Reference.id.desc())
        .first()
    )
    return ref


def load_model_for_point(point_id: int, ref_id: int, db: Session):
    """Carga el modelo para un punto específico. Cachea en _model_cache."""
    global _model_cache

    cached = _model_cache.get((point_id, ref_id))
    if cached and cached.get("detector") is not None:
        return cached["detector"], cached.get("sensitivity", 0.0), cached.get("version")

    ref = db.query(Reference).filter(Reference.id == ref_id).first()
    if not ref or not ref.model_path:
        return None, 0.0, None

    import joblib
    try:
        model_data = joblib.load(ref.model_path)
        model_version = model_data.get("version", "V31_Mahalanobis")
    except Exception:
        model_version = "V31_Mahalanobis"

    if "V32" in model_version and PATCHCORE_AVAILABLE:
        detector = PatchCoreDetector()
    else:
        # V31 fallback o detector estadístico
        detector = AnomalyDetector()
        if "V32" in model_version:
             print("[Model] PatchCore V32 solicitado pero no disponible, usando V31")
             model_version = "V31"

    try:
        detector.load(ref.model_path)
        sensitivity = ref.params.get("sensitivity", 0.0) if ref.params else 0.0
        
        # FIX: Asegurar que la versión cargada sea la real del objeto cargado
        if hasattr(detector, 'backbone_name'): # Es PatchCore
            model_version = "V32_PatchCore"
        else:
            model_version = "V31_Mahalanobis"

        _model_cache[(point_id, ref_id)] = {
            "detector": detector,
            "version": model_version,
            "sensitivity": sensitivity,
        }
        print(f"[Model] Cargado punto={point_id} ref={ref_id} version={model_version}")
        return detector, sensitivity, model_version
    except Exception as e:
        print(f"[Model] Error cargando modelo: {e}")
        return None, 0.0, None


def clear_model_cache(ref_id: int, point_id: int = None):
    """Limpia la caché de un modelo específico."""
    keys_to_remove = [
        k for k in _model_cache
        if k[1] == ref_id and (point_id is None or k[0] == point_id)
    ]
    for k in keys_to_remove:
        del _model_cache[k]
        print(f"[Model] Cache limpiada: punto={k[0]} ref={ref_id}")


# ══════════════════════════════════════════════════════════════════════════════
# WS FRONTED — drag-and-drop (mantiene compatibilidad con flujo anterior)
# ══════════════════════════════════════════════════════════════════════════════

@router.websocket("/ws/{ref_id}")
async def websocket_endpoint(websocket: WebSocket, ref_id: int):
    """WebSocket del frontend (drag-and-drop / webcam). Sin cambios funcionales."""
    await websocket.accept()
    db = SessionLocal()
    try:
        ref = db.query(Reference).filter(Reference.id == ref_id).first()
        point_id = ref.point_id if ref else 1

        detector, sensitivity, model_version = load_model_for_point(point_id, ref_id, db)
        if not detector:
            await websocket.send_json({"error": "Model not ready or reference not found"})
            await websocket.close()
            return

        is_patchcore = model_version and "V32" in model_version

        while True:
            message = await websocket.receive()

            if "text" in message:
                try:
                    cmd = json.loads(message["text"])
                    if cmd.get("type") == "set_sensitivity":
                        sensitivity = float(cmd.get("value", 0.0))
                        _persist_sensitivity(db, ref_id, sensitivity)
                except Exception as e:
                    print(f"[WS] Command error: {e}")
                continue

            if "bytes" not in message:
                continue

            result = await _process_frame(
                message["bytes"], detector, _shared_extractor,
                sensitivity, model_version, is_patchcore, db, ref_id
            )
            await websocket.send_json(result)

    except WebSocketDisconnect:
        pass
    except Exception as e:
        print(f"[WS] Error: {e}")
        try:
            await websocket.close()
        except Exception:
            pass
    finally:
        db.close()


# ══════════════════════════════════════════════════════════════════════════════
# WS BRIDGE — recibe frames del camera_bridge por (line_id, point_id)
# ══════════════════════════════════════════════════════════════════════════════

@router.websocket("/camera_feed")
async def camera_feed(websocket: WebSocket):
    """
    WebSocket exclusivo para el Camera Bridge.

    Protocolo (2 mensajes por frame):
      1. JSON: { "type": "frame_meta", "mode": "TRAIN|INSPECT",
                 "line_id": int, "point_id": int, "ref_id": int }
      2. Bytes: JPEG del frame
    """
    from backend.api.main import manager, train_buffer, train_buffer_lock

    await websocket.accept()
    print("[CameraFeed] Bridge conectado.")

    # Defaults: línea 1, punto 1
    current_line_id  = 1
    current_point_id = 1
    current_ref_id   = None
    current_mode     = "INSPECT"
    expecting_bytes  = False

    db = SessionLocal()

    try:
        while True:
            message = await websocket.receive()

            # ── JSON (meta o comando) ──────────────────────────────────────
            if "text" in message:
                try:
                    data = json.loads(message["text"])
                    t = data.get("type")

                    if t == "frame_meta":
                        current_line_id  = int(data.get("line_id",  current_line_id))
                        current_point_id = int(data.get("point_id", current_point_id))
                        current_ref_id   = data.get("ref_id", current_ref_id)
                        current_mode     = data.get("mode", current_mode)
                        expecting_bytes  = True

                    elif t == "set_mode":
                        current_mode     = data.get("mode", current_mode)
                        current_line_id  = int(data.get("line_id",  current_line_id))
                        current_point_id = int(data.get("point_id", current_point_id))
                        current_ref_id   = data.get("ref_id", current_ref_id)
                        print(f"[CameraFeed] Modo → {current_mode} L{current_line_id}P{current_point_id}")

                    elif t == "ping":
                        await websocket.send_text(json.dumps({"type": "pong"}))

                except Exception as e:
                    print(f"[CameraFeed] Error meta: {e}")
                continue

            # ── Bytes (frame JPEG) ─────────────────────────────────────────
            if "bytes" in message and expecting_bytes:
                expecting_bytes = False
                jpeg_bytes = message["bytes"]
                buf_key = (current_line_id, current_point_id)

                # TRAIN: acumular
                if current_mode == "TRAIN":
                    async with train_buffer_lock:
                        if buf_key not in train_buffer:
                            train_buffer[buf_key] = []
                        train_buffer[buf_key].append(jpeg_bytes)
                        count = len(train_buffer[buf_key])

                    await manager.broadcast(current_line_id, current_point_id, {
                        "type": "train_progress",
                        "line_id": current_line_id,
                        "point_id": current_point_id,
                        "frames_captured": count,
                        "mode": "TRAIN",
                    })
                    continue

                # INSPECT: inferencia
                if current_mode == "INSPECT":
                    # Si ref_id no viene del bridge, usar la más reciente del punto
                    ref_id_to_use = current_ref_id
                    if ref_id_to_use is None:
                        ref = _resolve_active_ref(current_point_id, db)
                        ref_id_to_use = ref.id if ref else None

                    if ref_id_to_use is None:
                        await manager.broadcast(current_line_id, current_point_id, {
                            "type": "error",
                            "message": f"Sin referencia entrenada para punto {current_point_id}",
                        })
                        continue

                    detector, sensitivity, model_version = load_model_for_point(
                        current_point_id, ref_id_to_use, db
                    )
                    if not detector:
                        await manager.broadcast(current_line_id, current_point_id, {
                            "type": "error",
                            "message": "Modelo no listo",
                        })
                        continue

                    is_patchcore = model_version and "V32" in model_version
                    result = await _process_frame(
                        jpeg_bytes, detector, _shared_extractor,
                        sensitivity, model_version, is_patchcore,
                        db, ref_id_to_use
                    )
                    result.update({
                        "ref_id": ref_id_to_use,
                        "line_id": current_line_id,
                        "point_id": current_point_id,
                        "source": "camera",
                    })
                    await manager.broadcast(current_line_id, current_point_id, result)

    except WebSocketDisconnect:
        print("[CameraFeed] Bridge desconectado.")
    except Exception as e:
        print(f"[CameraFeed] Error: {e}")
    finally:
        db.close()


# ══════════════════════════════════════════════════════════════════════════════
# WS FRONTEND LIVE — suscripción a resultados de cámara
# ══════════════════════════════════════════════════════════════════════════════

@router.websocket("/live/{line_id}/{point_id}")
async def live_results(websocket: WebSocket, line_id: int, point_id: int):
    """Frontend se suscribe aquí para recibir resultados de la cámara en tiempo real."""
    from backend.api.main import manager
    await manager.connect(line_id, point_id, websocket)
    try:
        while True:
            msg = await websocket.receive()
            if "text" in msg:
                try:
                    print(f"[Live L{line_id}P{point_id}] Comando: {msg['text']}")
                except Exception:
                    pass
    except WebSocketDisconnect:
        manager.disconnect(line_id, point_id, websocket)
    except Exception:
        manager.disconnect(line_id, point_id, websocket)


# ══════════════════════════════════════════════════════════════════════════════
# POST: entrenar con frames acumulados desde la cámara
# ══════════════════════════════════════════════════════════════════════════════

class TrainFromCameraRequest(BaseModel):
    line_id: int = 1
    point_id: int = 1
    ref_id: int
    contamination: float = 0.01


@router.post("/train_from_camera")
async def train_from_camera(req: TrainFromCameraRequest, db: Session = Depends(get_db)):
    from backend.api.main import train_buffer, train_buffer_lock, manager
    from backend.config import get_storage_path

    buf_key = (req.line_id, req.point_id)

    async with train_buffer_lock:
        frames_bytes = list(train_buffer.get(buf_key, []))

    if len(frames_bytes) < 5:
        return {"status": "error", "message": f"Solo {len(frames_bytes)} frames. Necesita ≥5."}

    images = []
    for jpeg in frames_bytes:
        arr = np.frombuffer(jpeg, np.uint8)
        img = cv2.imdecode(arr, cv2.IMREAD_COLOR)
        if img is not None:
            images.append(img)

    if len(images) < 5:
        return {"status": "error", "message": "No se pudieron decodificar suficientes frames."}

    print(f"[TrainFromCamera] L{req.line_id}P{req.point_id} → {len(images)} imágenes")
    await manager.broadcast(req.line_id, req.point_id, {
        "type": "train_started", "line_id": req.line_id, "point_id": req.point_id,
        "frames": len(images),
    })

    loop = asyncio.get_event_loop()
    try:
        detector = AnomalyDetectorV32() if PATCHCORE_AVAILABLE else AnomalyDetector()
        stats = await loop.run_in_executor(
            None, lambda: detector.train(images=images, contamination=req.contamination)
        )
    except Exception as e:
        await manager.broadcast(req.line_id, req.point_id, {"type": "train_error", "message": str(e)})
        return {"status": "error", "message": str(e)}

    ref = db.query(Reference).filter(Reference.id == req.ref_id).first()
    if not ref:
        return {"status": "error", "message": "Referencia no encontrada"}

    # Asignar punto si no tiene
    if ref.point_id is None:
        ref.point_id = req.point_id

    model_path = get_storage_path(req.ref_id, req.point_id, req.line_id) / "model.pkl"
    detector.save(str(model_path))

    ref.model_path = str(model_path)
    ref.params = {
        "contamination": req.contamination,
        "trained_from": "camera",
        "frame_count": len(images),
        "sensitivity": 0.0,
        "trained_at": datetime.utcnow().isoformat(),
        "line_id": req.line_id,
        "point_id": req.point_id,
        "version": "V32_PatchCore" if PATCHCORE_AVAILABLE else "V31_Mahalanobis"
    }
    db.commit()

    async with train_buffer_lock:
        train_buffer[buf_key] = []

    clear_model_cache(req.ref_id, req.point_id)

    result_msg = {
        "type": "train_complete",
        "line_id": req.line_id,
        "point_id": req.point_id,
        "ref_id": req.ref_id,
        "frames_used": len(images),
        "memory_bank_size": stats.get("memory_bank_size", 0),
        "threshold": round(stats.get("threshold", 0), 4),
    }
    await manager.broadcast(req.line_id, req.point_id, result_msg)
    return {"status": "trained", **result_msg}


# ══════════════════════════════════════════════════════════════════════════════
# POST: controlar modo del bridge desde el frontend
# ══════════════════════════════════════════════════════════════════════════════

class BridgeModeRequest(BaseModel):
    line_id: int = 1
    point_id: int = 1
    ref_id: int = None
    mode: str  # "TRAIN" | "INSPECT"


@router.post("/bridge/set_mode")
async def set_bridge_mode(req: BridgeModeRequest):
    from backend.api.main import manager
    await manager.broadcast(req.line_id, req.point_id, {
        "type": "mode_changed",
        "mode": req.mode,
        "line_id": req.line_id,
        "point_id": req.point_id,
        "ref_id": req.ref_id,
    })
    return {"status": "ok", "mode": req.mode}


# ══════════════════════════════════════════════════════════════════════════════
# POST: log de defecto (con auto-creación de tipo)
# ══════════════════════════════════════════════════════════════════════════════

class DefectLogRequest(BaseModel):
    reference_id: int
    defect_type: str
    score: float
    embedding: list = None


@router.post("/log_defect")
def log_defect(item: DefectLogRequest, db: Session = Depends(get_db)):
    dtype = db.query(DefectType).filter(DefectType.name == item.defect_type).first()
    if not dtype:
        dtype = DefectType(name=item.defect_type)
        db.add(dtype)
        db.commit()
        db.refresh(dtype)
        print(f"[DefectLog] Nuevo tipo creado: '{item.defect_type}'")

    log = DefectLog(
        reference_id=item.reference_id,
        anomaly_score=item.score,
        is_defect=1,
        defect_type_id=dtype.id,
        image_path="",
        embedding=item.embedding,
        timestamp=datetime.utcnow(),
    )
    db.add(log)
    db.commit()
    return {"status": "logged", "id": log.id, "defect_type": item.defect_type}


# ══════════════════════════════════════════════════════════════════════════════
# HELPERS INTERNOS
# ══════════════════════════════════════════════════════════════════════════════

async def _process_frame(jpeg_bytes, detector, extractor, sensitivity,
                         model_version, is_patchcore, db, ref_id):
    start = time.time()
    nparr = np.frombuffer(jpeg_bytes, np.uint8)
    img = cv2.imdecode(nparr, cv2.IMREAD_COLOR)

    if img is None:
        return {"is_defect": False, "score": 0.0, "fps": 0, "error": "decode_failed"}

    try:
        features = extractor.extract(img)
    except ValueError as qe:
        return {
            "is_defect": False, "score": 0.0, "fps": 0,
            "frame_rejected": True, "quality_warning": str(qe),
            "model_version": model_version,
        }

    heatmap_b64 = None
    if is_patchcore:
        is_anomaly, score, heatmap = detector.predict(image=img, sensitivity_offset=sensitivity)
        if heatmap is not None:
            heatmap_colored = cv2.applyColorMap((heatmap * 255).astype(np.uint8), cv2.COLORMAP_JET)
            _, buf = cv2.imencode(".png", heatmap_colored)
            heatmap_b64 = base64.b64encode(buf).decode("utf-8")
    else:
        is_anomaly, score = detector.predict(features, sensitivity_offset=sensitivity)

    proc_ms = (time.time() - start) * 1000
    recognition = _recognize_defect(db, ref_id, features) if is_anomaly else None

    return {
        "is_defect": bool(is_anomaly),
        "score": float(score),
        "fps": round(1000.0 / (proc_ms + 1e-1), 1),
        "timestamp": time.time(),
        "embedding": features.tolist() if is_anomaly else None,
        "recognition": recognition,
        "heatmap": heatmap_b64,
        "model_version": model_version,
        "frame_rejected": False,
    }


def _recognize_defect(db, ref_id, features):
    try:
        prev_logs = db.query(DefectLog).filter(
            DefectLog.reference_id == ref_id,
            DefectLog.embedding.isnot(None),
        ).all()
        if not prev_logs:
            return None

        feat_vec = features.flatten()
        norm = np.linalg.norm(feat_vec)
        best_sim, best = -1.0, None

        for p in prev_logs:
            if not p.embedding:
                continue
            pv = np.array(p.embedding).flatten()
            if pv.shape != feat_vec.shape:
                continue
            sim = np.dot(feat_vec, pv) / (norm * np.linalg.norm(pv) + 1e-9)
            if sim > best_sim:
                best_sim, best = sim, p

        if best and best_sim > 0.95:
            dtype = db.get(DefectType, best.defect_type_id)
            return {"label": dtype.name if dtype else "Unknown", "confidence": float(best_sim)}
    except Exception as e:
        print(f"[Recognition] Error: {e}")
    return None


def _persist_sensitivity(db, ref_id, sensitivity):
    try:
        ref = db.query(Reference).filter(Reference.id == ref_id).first()
        if ref:
            params = ref.params or {}
            params["sensitivity"] = sensitivity
            ref.params = params
            db.commit()
    except Exception as e:
        print(f"[Sensitivity] Error: {e}")
