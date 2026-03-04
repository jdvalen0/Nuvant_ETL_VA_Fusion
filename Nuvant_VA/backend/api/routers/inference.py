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
import random
import time
from datetime import datetime
from typing import Dict, Any, Optional

import cv2
import numpy as np
from fastapi import APIRouter, Depends, WebSocket, WebSocketDisconnect, HTTPException
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
_bridge_connections: Dict[tuple, WebSocket] = {}
_bridge_lock = asyncio.Lock()
_runtime_control: Dict[tuple, Dict[str, Any]] = {}
_auto_resume_tasks: Dict[tuple, asyncio.Task] = {}
_inspect_metrics_counter: Dict[tuple, int] = {}


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


def _get_runtime_control(line_id: int, point_id: int) -> Dict[str, Any]:
    """Obtiene parámetros runtime por punto (sin tocar algoritmo)."""
    key = (line_id, point_id)
    if key not in _runtime_control:
        _runtime_control[key] = {
            "capture_limit": int(os.getenv("TRAIN_CAPTURE_LIMIT", "200")),
            "train_sample_size": int(os.getenv("TRAIN_SAMPLE_SIZE", "50")),
            "pause_on_unknown_sec": int(os.getenv("PAUSE_ON_UNKNOWN_SEC", "0")),
        }
    return _runtime_control[key]


def _set_runtime_control(
    line_id: int,
    point_id: int,
    capture_limit: Optional[int] = None,
    train_sample_size: Optional[int] = None,
    pause_on_unknown_sec: Optional[int] = None,
) -> Dict[str, Any]:
    ctrl = _get_runtime_control(line_id, point_id)
    if capture_limit is not None:
        ctrl["capture_limit"] = max(5, min(int(capture_limit), 2000))
    if train_sample_size is not None:
        ctrl["train_sample_size"] = max(5, min(int(train_sample_size), 2000))
    if pause_on_unknown_sec is not None:
        ctrl["pause_on_unknown_sec"] = max(0, min(int(pause_on_unknown_sec), 120))
    return ctrl


def _schedule_auto_resume(line_id: int, point_id: int, ref_id: int, seconds: int):
    """Pausa temporal por defecto no reconocido y retoma inspección."""
    if seconds <= 0:
        return
    key = (line_id, point_id)
    prev = _auto_resume_tasks.get(key)
    if prev and not prev.done():
        prev.cancel()

    async def _resume():
        from backend.api.main import manager
        try:
            await asyncio.sleep(seconds)
            await _send_to_bridge(line_id, point_id, {
                "type": "set_mode",
                "mode": "INSPECT",
                "line_id": line_id,
                "point_id": point_id,
                "ref_id": ref_id,
            })
            await manager.broadcast(line_id, point_id, {
                "type": "mode_changed",
                "mode": "INSPECT",
                "line_id": line_id,
                "point_id": point_id,
                "ref_id": ref_id,
            })
        except asyncio.CancelledError:
            pass
        finally:
            if _auto_resume_tasks.get(key) is asyncio.current_task():
                _auto_resume_tasks.pop(key, None)

    _auto_resume_tasks[key] = asyncio.create_task(_resume())


def _tick_inspect_counter(line_id: int, point_id: int) -> int:
    key = (line_id, point_id)
    _inspect_metrics_counter[key] = _inspect_metrics_counter.get(key, 0) + 1
    return _inspect_metrics_counter[key]


def _cancel_auto_resume(line_id: int, point_id: int):
    """Cancela cualquier reanudación automática pendiente para este punto."""
    key = (line_id, point_id)
    task = _auto_resume_tasks.get(key)
    if task and not task.done():
        task.cancel()
    _auto_resume_tasks.pop(key, None)


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


async def _register_bridge(line_id: int, point_id: int, ws: WebSocket):
    async with _bridge_lock:
        _bridge_connections[(line_id, point_id)] = ws
        print(f"[Bridge] Registrado L{line_id}P{point_id}. Total: {len(_bridge_connections)}")


async def _unregister_bridge(ws: WebSocket):
    async with _bridge_lock:
        dead_keys = [k for k, v in _bridge_connections.items() if v is ws]
        for k in dead_keys:
            _bridge_connections.pop(k, None)


async def _send_to_bridge(line_id: int, point_id: int, payload: dict) -> bool:
    key = (line_id, point_id)
    async with _bridge_lock:
        ws = _bridge_connections.get(key)
    if ws is None:
        print(f"[Bridge] Error: No hay conexión para L{line_id}P{point_id}")
        return False
    try:
        await ws.send_text(json.dumps(payload))
        print(f"[Bridge] Comando enviado a L{line_id}P{point_id}: {payload.get('type')} -> {payload.get('mode')}")
        return True
    except Exception as e:
        print(f"[Bridge] Fallo al enviar a L{line_id}P{point_id}: {e}")
        await _unregister_bridge(ws)
        return False


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
        point_id = (ref.point_id if (ref and ref.point_id is not None) else 1)

        detector, sensitivity, model_version = load_model_for_point(point_id, ref_id, db)
        if not detector:
            print(f"[WS] Modelo no listo para ref {ref_id}. Manteniendo conexión.")
            await websocket.send_json({"type": "info", "message": "Model not ready. Please train first."})
            # No cerramos, dejamos que el usuario suba imágenes o espere.
        
        is_patchcore = model_version and "V32" in model_version if detector else False

        while True:
            message = await websocket.receive()
            if message.get("type") == "websocket.disconnect":
                break

            if "text" in message:
                try:
                    cmd = json.loads(message["text"])
                    if cmd.get("type") == "set_sensitivity":
                        sensitivity = float(cmd.get("value", 0.0))
                        _persist_sensitivity(db, ref_id, sensitivity, point_id=point_id)
                except Exception as e:
                    print(f"[WS] Command error: {e}")
                continue

            if "bytes" not in message:
                continue

            if not detector:
                # Si no hay detector, solo permitimos recibir comandos (como set_sensitivity)
                # pero no procesamos frames locales (bytes)
                if "bytes" in message:
                     await websocket.send_json({"type": "error", "message": "No model loaded for processing"})
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
    from backend.api.main import manager, train_buffer, train_buffer_lock

    await websocket.accept()
    print("[CameraFeed] Bridge conectado.")

    # Defaults
    current_line_id  = 1
    current_point_id = 1
    current_ref_id   = None
    current_mode     = "PAUSE"
    expecting_bytes  = False
    current_frame_ts = 0.0
    train_limit = int(os.getenv("TRAIN_CAPTURE_LIMIT", "200"))
    train_limit_notified = set()
    await _register_bridge(current_line_id, current_point_id, websocket)

    async def _safe_receive():
        try:
            return await websocket.receive()
        except Exception:
            return {"type": "websocket.disconnect"}

    async def _ping_loop():
        """Mantiene la conexión viva para evitar cierre por idle (count=0 visto desde fuera)."""
        while True:
            await asyncio.sleep(20)
            try:
                await websocket.send_text(json.dumps({"type": "ping"}))
            except Exception:
                break

    ping_task = asyncio.create_task(_ping_loop())
    try:
        while True:
            message = await _safe_receive()
            if message["type"] == "websocket.disconnect":
                break

            if "text" in message:
                try:
                    data = json.loads(message["text"])
                    t = data.get("type")
                    if t == "frame_meta":
                        prev_key = (current_line_id, current_point_id)
                        prev_mode = current_mode
                        current_line_id  = int(data.get("line_id", current_line_id))
                        current_point_id = int(data.get("point_id", current_point_id))
                        current_ref_id   = data.get("ref_id", current_ref_id)
                        current_mode     = data.get("mode", current_mode)
                        current_frame_ts = data.get("timestamp", time.time())
                        expecting_bytes  = True
                        if current_mode == "TRAIN" and prev_mode != "TRAIN":
                            async with train_buffer_lock:
                                train_buffer[(current_line_id, current_point_id)] = []
                            train_limit_notified.discard((current_line_id, current_point_id))
                            print(f"[CameraFeed] Buffer RESET for L{current_line_id}P{current_point_id}")
                        if (current_line_id, current_point_id) != prev_key:
                            await _register_bridge(current_line_id, current_point_id, websocket)
                    elif t == "set_mode":
                        _cancel_auto_resume(
                            int(data.get("line_id", current_line_id)),
                            int(data.get("point_id", current_point_id)),
                        )
                        new_mode = data.get("mode", current_mode)
                        if new_mode == "TRAIN" and current_mode != "TRAIN":
                            # Reset buffer when starting a new training session
                            async with train_buffer_lock:
                                train_buffer[(current_line_id, current_point_id)] = []
                                print(f"[CameraFeed] Buffer RESET for L{current_line_id}P{current_point_id}")
                            train_limit_notified.discard((current_line_id, current_point_id))
                        current_mode     = new_mode
                        current_line_id  = int(data.get("line_id", current_line_id))
                        current_point_id = int(data.get("point_id", current_point_id))
                        current_ref_id   = data.get("ref_id", current_ref_id)
                    elif t == "ping":
                        await websocket.send_text(json.dumps({"type": "pong"}))
                except: continue
                continue

            if "bytes" in message and expecting_bytes:
                expecting_bytes = False
                jpeg_bytes = message["bytes"]
                buf_key = (current_line_id, current_point_id)

                # LAG PREVENTION: si el frame es muy viejo (>0.5s), lo saltamos en INSPECT
                if current_mode == "INSPECT":
                    delay = time.time() - current_frame_ts
                    if delay > 0.5:
                        # print(f"[CameraFeed] Lag detectado ({delay:.2f}s). Saltando frame.")
                        continue

                if current_mode == "TRAIN":
                    runtime = _get_runtime_control(current_line_id, current_point_id)
                    train_limit = runtime.get("capture_limit", train_limit)
                    async with train_buffer_lock:
                        if buf_key not in train_buffer: train_buffer[buf_key] = []
                        # Cap de captura para acelerar entrenamiento y evitar buffer excesivo.
                        is_new_frame = False
                        frame_index = max(0, len(train_buffer[buf_key]) - 1)
                        if len(train_buffer[buf_key]) < train_limit:
                            train_buffer[buf_key].append(jpeg_bytes)
                            is_new_frame = True
                            frame_index = len(train_buffer[buf_key]) - 1
                        count = len(train_buffer[buf_key])
                    await manager.broadcast(current_line_id, current_point_id, {
                        "type": "train_progress", "line_id": current_line_id,
                        "point_id": current_point_id, "frames_captured": count, "mode": "TRAIN",
                        "capture_limit": train_limit
                    })
                    
                    # Enviar también el frame al UI para que el usuario vea qué se captura
                    img_b64 = base64.b64encode(jpeg_bytes).decode("utf-8")
                    await manager.broadcast(current_line_id, current_point_id, {
                        "type": "live_frame",
                        "image": img_b64,
                        "mode": "TRAIN",
                        "frame_index": frame_index,
                        "frames_captured": count,
                        "source": "camera",
                        "ref_id": current_ref_id
                    })
                    if count >= train_limit and buf_key not in train_limit_notified:
                        train_limit_notified.add(buf_key)
                        await manager.broadcast(current_line_id, current_point_id, {
                            "type": "train_capture_complete",
                            "line_id": current_line_id,
                            "point_id": current_point_id,
                            "mode": "TRAIN",
                            "frames_captured": count,
                            "capture_limit": train_limit,
                            "message": f"Captura completada con {count} imágenes.",
                        })
                        # Al completar la captura, pausar automáticamente la cámara para evitar ruido extra.
                        await _send_to_bridge(current_line_id, current_point_id, {
                            "type": "set_mode",
                            "mode": "PAUSE",
                            "line_id": current_line_id,
                            "point_id": current_point_id,
                            "ref_id": current_ref_id,
                        })
                        current_mode = "PAUSE"
                        await manager.broadcast(current_line_id, current_point_id, {
                            "type": "mode_changed",
                            "mode": "PAUSE",
                            "line_id": current_line_id,
                            "point_id": current_point_id,
                            "ref_id": current_ref_id,
                        })
                    if is_new_frame and count % 10 == 0:
                        print(f"[CameraFeed] Broadcast frame TRAIN (L{current_line_id}P{current_point_id}, frames={count})")
                    continue

                if current_mode == "CALIBRATE":
                    img_b64 = base64.b64encode(jpeg_bytes).decode("utf-8")
                    await manager.broadcast(current_line_id, current_point_id, {
                        "type": "live_frame",
                        "image": img_b64,
                        "mode": "CALIBRATE",
                        "source": "camera",
                        "ref_id": current_ref_id
                    })
                    continue

                if current_mode == "INSPECT":
                    # Usar una sesión de DB fresca para cada frame para evitar problemas de hilos/deadlocks
                    with SessionLocal() as db_session:
                        ref_id_to_use = current_ref_id
                        if ref_id_to_use is None:
                            ref = _resolve_active_ref(current_point_id, db_session)
                            ref_id_to_use = ref.id if ref else None

                        if ref_id_to_use is None:
                            await manager.broadcast(current_line_id, current_point_id, {"type":"error","message":"No ref"})
                            continue

                        detector, sensitivity, model_version = load_model_for_point(current_point_id, ref_id_to_use, db_session)
                        if not detector: continue

                        is_patchcore = model_version and "V32" in model_version
                        
                        # ALTA CPU -> Mover a executor
                        loop = asyncio.get_event_loop()
                        result = await loop.run_in_executor(
                            None, 
                            lambda: _sync_process_frame(
                                jpeg_bytes, detector, _shared_extractor, 
                                sensitivity, model_version, is_patchcore, 
                                ref_id_to_use
                            )
                        )

                        # AGREGAR IMAGEN BASE64 PARA EL UI (Indispensable para ver video)
                        img_b64 = base64.b64encode(jpeg_bytes).decode("utf-8")
                        result.update({
                            "type": "live_frame", # El frontend espera este tipo para actualizar el feed
                            "image": img_b64,
                            "ref_id": ref_id_to_use, "line_id": current_line_id,
                            "point_id": current_point_id, "source": "camera"
                        })
                        tick = _tick_inspect_counter(current_line_id, current_point_id)
                        if tick % 20 == 0:
                            print(
                                "[InspectMetrics] "
                                f"L{current_line_id}P{current_point_id} ref={ref_id_to_use} "
                                f"score={result.get('score')} anomaly_index={result.get('anomaly_index')} "
                                f"is_defect={result.get('is_defect')}"
                            )
                        runtime = _get_runtime_control(current_line_id, current_point_id)
                        pause_sec = int(runtime.get("pause_on_unknown_sec", 0))
                        is_unknown_defect = bool(result.get("is_defect")) and not result.get("recognition")
                        if is_unknown_defect and pause_sec > 0:
                            result["hold_for_labeling"] = True
                            result["hold_seconds"] = pause_sec
                            await manager.broadcast(current_line_id, current_point_id, result)
                            await _send_to_bridge(current_line_id, current_point_id, {
                                "type": "set_mode",
                                "mode": "PAUSE",
                                "line_id": current_line_id,
                                "point_id": current_point_id,
                                "ref_id": ref_id_to_use,
                            })
                            current_mode = "PAUSE"
                            await manager.broadcast(current_line_id, current_point_id, {
                                "type": "mode_changed",
                                "mode": "PAUSE",
                                "line_id": current_line_id,
                                "point_id": current_point_id,
                                "ref_id": ref_id_to_use,
                                "reason": "unknown_defect_hold",
                                "hold_seconds": pause_sec,
                            })
                            _schedule_auto_resume(current_line_id, current_point_id, ref_id_to_use, pause_sec)
                        else:
                            await manager.broadcast(current_line_id, current_point_id, result)
    except Exception as e:
        print(f"[CameraFeed] Error: {e}")
    finally:
        ping_task.cancel()
        try:
            await ping_task
        except asyncio.CancelledError:
            pass
        await _unregister_bridge(websocket)
        print("[CameraFeed] Bridge desconectado.")


def _sync_process_frame(jpeg_bytes, detector, extractor, sensitivity, 
                       model_version, is_patchcore, ref_id):
    """Versión sincrónica para ejecutar en ThreadPoolExecutor y no bloquear el event loop."""
    import time, base64
    start = time.time()
    nparr = np.frombuffer(jpeg_bytes, np.uint8)
    img = cv2.imdecode(nparr, cv2.IMREAD_COLOR)
    if img is None: return {"is_defect": False, "score": 0.0, "fps": 0, "error": "decode_failed"}

    try:
        features = extractor.extract(img)
    except Exception as e:
        return {"is_defect": False, "score": 0.0, "fps": 0, "frame_rejected": True, "error": str(e)}

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
    
    # RECONOCIMIENTO (Sincrónico)
    # Nota: _recognize_defect necesita DB. Para simplificar, lo llamamos fuera o pasamos sesión.
    # Pero para inferencia rápida, a menudo se omite o se cachea.
    # Aquí abrimos una mini-sesión si es necesario o lo dejamos para después.
    recognition = None
    with SessionLocal() as db:
        recognition = _recognize_defect(db, ref_id, features) if is_anomaly else None

    return {
        "is_defect": bool(is_anomaly),
        "score": float(score),
        "anomaly_index": float(max(0.0, min(100.0, 100.0 - float(score)))),
        "fps": round(1000.0 / (proc_ms + 1e-1), 1),
        "timestamp": time.time(),
        "embedding": features.tolist() if is_anomaly else None,
        "recognition": recognition,
        "heatmap": heatmap_b64,
        "model_version": model_version,
        "frame_rejected": False,
    }



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
            # Mantener conexión abierta
            message = await websocket.receive()
            if message["type"] == "websocket.disconnect":
                break
            
            if "text" in message:
                try:
                    cmd = json.loads(message["text"])
                    cmd_type = cmd.get("type")
                    if cmd_type == "set_mode" or cmd_type == "mode_changed":
                        _cancel_auto_resume(line_id, point_id)
                        _set_runtime_control(
                            line_id,
                            point_id,
                            capture_limit=cmd.get("capture_limit"),
                            train_sample_size=cmd.get("train_sample_size"),
                            pause_on_unknown_sec=cmd.get("pause_on_unknown_sec"),
                        )
                        # Reenviar al bridge
                        await _send_to_bridge(line_id, point_id, {
                            "type": "set_mode",
                            "mode": cmd.get("mode", "INSPECT"),
                            "line_id": line_id,
                            "point_id": point_id,
                            "ref_id": cmd.get("ref_id")
                        })
                    elif cmd_type == "set_sensitivity":
                        # El pipeline de cámara usa sensibilidad desde cache (load_model_for_point);
                        # persistimos y sincronizamos cache para efecto inmediato en inspección live.
                        sensitivity = float(cmd.get("value", 0.0))
                        ref_id = cmd.get("ref_id")
                        if ref_id is not None:
                            with SessionLocal() as db:
                                _persist_sensitivity(db, int(ref_id), sensitivity, point_id=point_id)
                except Exception:
                    pass
    except WebSocketDisconnect:
        manager.disconnect(line_id, point_id, websocket)
    except Exception:
        manager.disconnect(line_id, point_id, websocket)
    finally:
        manager.disconnect(line_id, point_id, websocket)


# ══════════════════════════════════════════════════════════════════════════════
# POST: entrenar con frames acumulados desde la cámara
# ══════════════════════════════════════════════════════════════════════════════

class TrainFromCameraRequest(BaseModel):
    line_id: int = 1
    point_id: int = 1
    ref_id: int
    contamination: float = 0.03
    sample_size: Optional[int] = None


@router.post("/train_from_camera")
async def train_from_camera(req: TrainFromCameraRequest, db: Session = Depends(get_db)):
    from backend.api.main import train_buffer, train_buffer_lock, manager
    from backend.config import get_storage_path

    buf_key = (req.line_id, req.point_id)

    async with train_buffer_lock:
        all_frames = list(train_buffer.get(buf_key, []))

    frames_bytes = list(all_frames)
    runtime = _get_runtime_control(req.line_id, req.point_id)
    train_sample_size = req.sample_size or runtime.get("train_sample_size", int(os.getenv("TRAIN_SAMPLE_SIZE", "50")))
    train_sample_size = max(5, min(int(train_sample_size), 2000))

    if len(frames_bytes) > train_sample_size:
        sampled_indices = sorted(random.sample(range(len(frames_bytes)), train_sample_size))
        frames_bytes = [frames_bytes[i] for i in sampled_indices]
        print(f"[TrainFromCamera] Sub-sampling: {len(frames_bytes)} images (Original: {len(all_frames)})")

    if len(frames_bytes) < 5:
        raise HTTPException(status_code=400, detail=f"Solo {len(frames_bytes)} frames. Necesita ≥5.")

    images = []
    for jpeg in frames_bytes:
        arr = np.frombuffer(jpeg, np.uint8)
        img = cv2.imdecode(arr, cv2.IMREAD_COLOR)
        if img is not None:
            images.append(img)

    if len(images) < 5:
        raise HTTPException(status_code=400, detail="No se pudieron decodificar suficientes frames.")

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
        raise HTTPException(status_code=500, detail=str(e))

    ref = db.query(Reference).filter(Reference.id == req.ref_id).first()
    if not ref:
        raise HTTPException(status_code=404, detail="Referencia no encontrada")

    # Asignar punto si no tiene
    if ref.point_id is None:
        ref.point_id = req.point_id

    model_path = get_storage_path(req.ref_id, req.point_id, req.line_id) / "model.pkl"
    detector.save(str(model_path))

    ref.model_path = str(model_path)
    ref.params = {
        "contamination": req.contamination,
        "trained_from": "camera",
        "captured_frames": len(all_frames),
        "frame_count": len(images),
        "train_sample_size": train_sample_size,
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

    # Broadcast que el entrenamiento ha FINALIZADO para que el UI se actualice
    await manager.broadcast(req.line_id, req.point_id, {
        "type": "train_finished", 
        "line_id": req.line_id, 
        "point_id": req.point_id,
        "ref_id": req.ref_id,
        "status": "success"
    })

    result_msg = {
        "type": "train_complete",
        "line_id": req.line_id,
        "point_id": req.point_id,
        "ref_id": req.ref_id,
        "frames_captured": len(all_frames),
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
    mode: str  # "TRAIN" | "INSPECT" | "CALIBRATE" | "PAUSE"
    capture_limit: Optional[int] = None
    train_sample_size: Optional[int] = None
    pause_on_unknown_sec: Optional[int] = None


@router.post("/bridge/set_mode")
async def set_bridge_mode(req: BridgeModeRequest):
    from backend.api.main import manager
    _cancel_auto_resume(req.line_id, req.point_id)
    runtime = _set_runtime_control(
        req.line_id,
        req.point_id,
        capture_limit=req.capture_limit,
        train_sample_size=req.train_sample_size,
        pause_on_unknown_sec=req.pause_on_unknown_sec,
    )
    delivered = await _send_to_bridge(req.line_id, req.point_id, {
        "type": "set_mode",
        "mode": req.mode,
        "line_id": req.line_id,
        "point_id": req.point_id,
        "ref_id": req.ref_id,
    })
    await manager.broadcast(req.line_id, req.point_id, {
        "type": "mode_changed",
        "mode": req.mode,
        "line_id": req.line_id,
        "point_id": req.point_id,
        "ref_id": req.ref_id,
    })
    return {
        "status": "ok",
        "mode": req.mode,
        "bridge_delivered": delivered,
        "runtime_control": runtime,
    }


@router.get("/bridge/status")
async def get_bridge_status():
    async with _bridge_lock:
        conns = {str(k): "CONECTADO" for k in _bridge_connections}
    return {"active_bridges": conns, "count": len(conns)}


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
        "anomaly_index": float(max(0.0, min(100.0, 100.0 - float(score)))),
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


def _set_cached_sensitivity(ref_id: int, sensitivity: float, point_id: int = None):
    for key, value in _model_cache.items():
        k_point_id, k_ref_id = key
        if k_ref_id != ref_id:
            continue
        if point_id is not None and k_point_id != point_id:
            continue
        value["sensitivity"] = sensitivity


def _persist_sensitivity(db, ref_id, sensitivity, point_id=None):
    try:
        ref = db.query(Reference).filter(Reference.id == ref_id).first()
        if ref:
            # Forzar objeto nuevo: SQLAlchemy JSON no siempre detecta mutación in-place.
            params = dict(ref.params or {})
            params["sensitivity"] = sensitivity
            ref.params = params
            db.commit()
            _set_cached_sensitivity(ref_id, sensitivity, point_id=point_id)
            print(f"[Sensitivity] ref={ref_id} point={point_id} -> {sensitivity}")
    except Exception as e:
        print(f"[Sensitivity] Error: {e}")
