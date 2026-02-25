"""
Nuvant Camera Bridge — v1.0
Python 3.7 compatible (stapipy wheel requirement)

Captura frames desde cámara Sentech (GigE Vision) vía stapipy
y los retransmite al backend Nuvant VA por WebSocket interno.

Modos:
  INSPECT  → frames van al motor PatchCore (producción)
  TRAIN    → frames se acumulan para entrenamiento de la referencia activa

Variables de entorno:
  CAMERA_MODE       : "live" | "simulate"  (default: live)
  CAMERA_FPS        : float   (default: 5.0)
  CAMERA_IP         : str     (opcional, filtra por IP de cámara en la red)
  VA_BACKEND_WS_URL : str     (default: ws://nuvant-backend:8000/api/inference/camera_feed)
  SIMULATE_DIR      : str     (carpeta con PNGs para modo simulate, default: /simulate_images)
"""

import os
import sys
import time
import asyncio
import json
import cv2
import numpy as np

# ── Compatibilidad asyncio Python 3.7 ──────────────────────────────────────
import websockets  # websockets 10.x compatible con Python 3.7

# ── Configuración desde variables de entorno ────────────────────────────────
CAMERA_MODE       = os.environ.get("CAMERA_MODE", "live").lower()
CAMERA_FPS        = float(os.environ.get("CAMERA_FPS", "5.0"))
CAMERA_IP         = os.environ.get("CAMERA_IP", "")  # vacío = primer dispositivo
VA_BACKEND_WS_URL = os.environ.get(
    "VA_BACKEND_WS_URL",
    "ws://nuvant-backend:8000/api/inference/camera_feed"
)
SIMULATE_DIR = os.environ.get("SIMULATE_DIR", "/simulate_images")

# Identificación del punto de inspección al que pertenece este bridge
CAMERA_LINE_ID  = int(os.environ.get("CAMERA_LINE_ID",  "1"))
CAMERA_POINT_ID = int(os.environ.get("CAMERA_POINT_ID", "1"))
CAMERA_ID       = os.environ.get("CAMERA_ID",       "cam-l1-final")

JPEG_QUALITY = int(os.environ.get("JPEG_QUALITY", "80"))  # balance calidad/velocidad


# ══════════════════════════════════════════════════════════════════════════════
# CAPTURA DE CÁMARA
# ══════════════════════════════════════════════════════════════════════════════

def _convert_to_numpy(st_image):
    """Convierte StImage a numpy BGR."""
    import stapipy as st
    data = st_image.get_image_data()
    h, w = st_image.height, st_image.width
    pf = st.get_pixel_format_info(st_image.pixel_format)

    if pf.is_mono:
        gray = np.frombuffer(data, np.uint8).reshape(h, w)
        return cv2.cvtColor(gray, cv2.COLOR_GRAY2BGR)

    if pf.is_bayer:
        raw = np.frombuffer(data, np.uint8).reshape(h, w)
        return cv2.cvtColor(raw, cv2.COLOR_BAYER_BG2BGR)

    raise ValueError("PixelFormat no soportado: {}".format(st_image.pixel_format))


def _grab_one_frame(ds, timeout_ms=5000, max_tries=30):
    """Intenta obtener un frame completo; retorna numpy BGR o None."""
    for _ in range(max_tries):
        with ds.retrieve_buffer(timeout=timeout_ms) as buf:
            if buf.info.is_incomplete or not buf.info.is_image_present:
                continue
            return _convert_to_numpy(buf.get_image())
    return None


class LiveCamera:
    """Wrapper de la cámara Sentech para captura continua."""

    def __init__(self):
        import stapipy as st
        self._st = st
        self._dev = None
        self._ds = None

    def connect(self):
        self._st.initialize()
        sys = self._st.create_system()

        if CAMERA_IP:
            # Buscar por IP si se especificó
            devices = sys.detect()
            target = None
            for d in devices:
                if CAMERA_IP in d.display_name:
                    target = d
                    break
            if target is None:
                raise RuntimeError("Cámara con IP {} no encontrada".format(CAMERA_IP))
            self._dev = target.create_device()
        else:
            self._dev = sys.create_first_device()

        print("[Bridge] Conectado a: {}".format(self._dev.info.display_name))

        nm = self._dev.remote_port.nodemap
        # Configuración GigE para streaming continuo
        for name, val in [
            ("TriggerMode", 0),
            ("AcquisitionMode", 2),      # Continuous
            ("GevSCPSPacketSize", 1500),
            ("GevSCPD", 10000),
            ("AcquisitionFrameRate", CAMERA_FPS),
        ]:
            try:
                nm.get_node(name).value = val
            except Exception:
                pass  # Nodo no disponible en este modelo, continuar

        self._ds = self._dev.create_datastream()
        self._ds.start_acquisition()
        self._dev.acquisition_start()
        print("[Bridge] Streaming iniciado a {} FPS".format(CAMERA_FPS))

    def grab(self):
        """Retorna numpy BGR o None."""
        return _grab_one_frame(self._ds, timeout_ms=3000, max_tries=20)

    def disconnect(self):
        try:
            self._dev.acquisition_stop()
        except Exception:
            pass
        try:
            self._ds.stop_acquisition()
        except Exception:
            pass
        print("[Bridge] Cámara desconectada.")


class SimulateCamera:
    """Cámara simulada: lee PNGs de SIMULATE_DIR en loop."""

    def __init__(self):
        self._files = []
        self._idx = 0

    def connect(self):
        exts = (".png", ".jpg", ".jpeg")
        self._files = sorted([
            os.path.join(SIMULATE_DIR, f)
            for f in os.listdir(SIMULATE_DIR)
            if f.lower().endswith(exts)
        ])
        if not self._files:
            raise RuntimeError("No hay imágenes en SIMULATE_DIR: {}".format(SIMULATE_DIR))
        print("[Bridge][SIM] {} imágenes encontradas en {}".format(len(self._files), SIMULATE_DIR))

    def grab(self):
        path = self._files[self._idx % len(self._files)]
        self._idx += 1
        img = cv2.imread(path)
        return img

    def disconnect(self):
        print("[Bridge][SIM] Simulación detenida.")


# ══════════════════════════════════════════════════════════════════════════════
# ESTADO COMPARTIDO DEL BRIDGE
# ══════════════════════════════════════════════════════════════════════════════

class BridgeState:
    """Estado mutable del bridge."""
    mode:     str = "INSPECT"   # "TRAIN" | "INSPECT"
    ref_id:   int = None
    line_id:  int = CAMERA_LINE_ID
    point_id: int = CAMERA_POINT_ID
    running:  bool = True


state = BridgeState()


# ══════════════════════════════════════════════════════════════════════════════
# LOOP PRINCIPAL
# ══════════════════════════════════════════════════════════════════════════════

async def bridge_loop():
    """Conecta al backend VA y envía frames de forma continua."""
    frame_interval = 1.0 / CAMERA_FPS

    # Seleccionar cámara
    camera = SimulateCamera() if CAMERA_MODE == "simulate" else LiveCamera()

    try:
        camera.connect()
    except Exception as e:
        print("[Bridge] ERROR conectando cámara: {}".format(e))
        sys.exit(1)

    retry_delay = 2.0
    encode_params = [cv2.IMWRITE_JPEG_QUALITY, JPEG_QUALITY]

    while state.running:
        try:
            print("[Bridge] Conectando a: {}".format(VA_BACKEND_WS_URL))
            async with websockets.connect(VA_BACKEND_WS_URL, max_size=None) as ws:
                print("[Bridge] WebSocket conectado al backend VA.")
                retry_delay = 2.0  # reset on success

                # ── Hilo de recepción de comandos desde backend ────────────
                async def recv_commands():
                    """Recibe comandos del backend (cambio de modo, ref_id)."""
                    async for msg in ws:
                        try:
                            cmd = json.loads(msg)
                            cmd_type = cmd.get("type")

                            if cmd_type == "set_mode":
                                state.mode = cmd.get("mode", "INSPECT")
                                state.ref_id = int(cmd.get("ref_id", state.ref_id))
                                print("[Bridge] Modo → {} | ref_id={}".format(state.mode, state.ref_id))

                            elif cmd_type == "ping":
                                await ws.send(json.dumps({"type": "pong"}))

                        except Exception as e:
                            print("[Bridge] Error procesando comando: {}".format(e))

                recv_task = asyncio.ensure_future(recv_commands())

                # ── Loop de captura y envío ────────────────────────────────
                try:
                    while state.running:
                        t0 = time.time()

                        frame = camera.grab()
                        if frame is None:
                            print("[Bridge] Frame vacío, reintentando...")
                            await asyncio.sleep(0.1)
                            continue

                        # Metadata como primer mensaje (JSON)
                        meta = json.dumps({
                            "type":      "frame_meta",
                            "mode":      state.mode,
                            "line_id":   state.line_id,
                            "point_id":  state.point_id,
                            "ref_id":    state.ref_id,
                            "camera_id": CAMERA_ID,
                            "timestamp": time.time()
                        })
                        await ws.send(meta)

                        # Frame como segundo mensaje (bytes JPEG)
                        ret, buf = cv2.imencode(".jpg", frame, encode_params)
                        if not ret:
                            print("[Bridge] ERROR codificando JPEG")
                            continue
                        await ws.send(buf.tobytes())

                        # Control de FPS
                        elapsed = time.time() - t0
                        sleep_t = max(0.0, frame_interval - elapsed)
                        await asyncio.sleep(sleep_t)

                finally:
                    recv_task.cancel()
                    try:
                        await recv_task
                    except asyncio.CancelledError:
                        pass

        except (websockets.exceptions.ConnectionClosed,
                websockets.exceptions.InvalidURI,
                OSError) as e:
            print("[Bridge] Desconexión: {}. Reintentando en {}s...".format(e, retry_delay))
            await asyncio.sleep(retry_delay)
            retry_delay = min(retry_delay * 2, 30.0)  # backoff exponencial

        except Exception as e:
            print("[Bridge] Error inesperado: {}".format(e))
            await asyncio.sleep(retry_delay)

    camera.disconnect()


if __name__ == "__main__":
    print("=" * 60)
    print("  Nuvant Camera Bridge v1.0")
    print("  Modo: {}  |  FPS: {}  |  ref_id: {}".format(
        CAMERA_MODE, CAMERA_FPS, state.ref_id
    ))
    print("  Backend: {}".format(VA_BACKEND_WS_URL))
    print("=" * 60)

    loop = asyncio.get_event_loop()
    try:
        loop.run_until_complete(bridge_loop())
    except KeyboardInterrupt:
        print("\n[Bridge] Detenido por usuario.")
    finally:
        loop.close()
