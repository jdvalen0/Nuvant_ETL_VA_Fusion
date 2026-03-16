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
import ipaddress
import cv2
import numpy as np

# ── Compatibilidad asyncio Python 3.7 ──────────────────────────────────────
import websockets  # websockets 10.x compatible con Python 3.7

# ── Configuración desde variables de entorno ────────────────────────────────
CAMERA_MODE       = os.environ.get("CAMERA_MODE", "live").lower()
CAMERA_FPS        = float(os.environ.get("CAMERA_FPS", "5.0"))
CAMERA_IP         = os.environ.get("CAMERA_IP", "")  # vacío = primer dispositivo
CAMERA_FORCE_IP   = os.environ.get("CAMERA_FORCE_IP", "169.254.75.178")  # IP a forzar en cámara GigE (vacío = no forzar)
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
    """Intenta obtener un frame completo; retorna numpy BGR o None.
    Timeouts de RetrieveBuffer se reintentan; otras excepciones se propagan.
    Nota: bloquea el event loop durante captura (StApiPy no es thread-safe)."""
    for attempt in range(max_tries):
        try:
            with ds.retrieve_buffer(timeout=timeout_ms) as buf:
                if buf.info.is_incomplete or not buf.info.is_image_present:
                    continue
                return _convert_to_numpy(buf.get_image())
        except Exception as e:
            err_str = str(e).lower()
            is_timeout = any(
                x in err_str for x in ("timeout", "retrievebuffer", "retrieve_buffer", "istdatastream")
            )
            if is_timeout and attempt < max_tries - 1:
                time.sleep(0.1)
                continue
            raise
    return None


class LiveCamera:
    """Wrapper de la cámara Sentech para captura continua."""

    def __init__(self):
        import stapipy as st
        self._st = st
        self._dev = None
        self._ds = None

    def connect(self):
        import stapipy as st
        self._st.initialize()
        # Filtrar por GigEVision para mayor velocidad y precisión
        sys = self._st.create_system(st.EStSystemVendor.Default, st.EStInterfaceType.GigEVision)

        target_device = None
        detected_names = []
        target_ip_int = int(ipaddress.ip_address(CAMERA_IP)) if CAMERA_IP else None

        # Forzar descubrimiento en todas las interfaces
        for i in range(sys.interface_count):
            iface = sys.get_interface(i)
            iface.update_device_list()
            iface_nm = iface.port.nodemap
            dev_selector = iface_nm.get_node("DeviceSelector")
            try:
                gev_ip_node = iface_nm.get_node("GevDeviceIPAddress")
            except Exception:
                gev_ip_node = None

            for j in range(iface.device_count):
                try:
                    dev_selector.value = j
                except Exception:
                    continue
                dev_info = iface.get_device_info(j)
                detected_names.append(dev_info.display_name)

                # Obtener IP del dispositivo (GevDeviceIPAddress es fiable; display_name puede variar)
                dev_ip_int = None
                if gev_ip_node:
                    try:
                        dev_ip_int = gev_ip_node.value
                    except Exception:
                        pass

                # GIGEVISION FORCE IP: configurar cámara a IP deseada antes de conectar
                if CAMERA_FORCE_IP and (not CAMERA_IP or dev_ip_int == target_ip_int or CAMERA_IP in dev_info.display_name):
                    try:
                        print(f"[Bridge] Forzando IP a {CAMERA_FORCE_IP}...")
                        iface_nm.get_node("GevDeviceForceIPAddress").value = int(ipaddress.ip_address(CAMERA_FORCE_IP))
                        iface_nm.get_node("GevDeviceForceSubnetMask").value = int(ipaddress.ip_address("255.255.255.0"))
                        force_ip_node = iface_nm.get_node("GevDeviceForceIP")
                        (force_ip_node.get() if hasattr(force_ip_node, 'get') else force_ip_node).execute()
                        time.sleep(2)
                    except Exception as e:
                        print(f"[Bridge] Error en Force IP (continuando): {e}")

                # Selección: por IP (GevDeviceIPAddress) o display_name, o primer dispositivo
                if CAMERA_IP:
                    if dev_ip_int is not None and dev_ip_int == target_ip_int:
                        target_device = iface.create_device_by_index(j)
                        break
                    if CAMERA_IP in dev_info.display_name:
                        target_device = iface.create_device_by_index(j)
                        break
                else:
                    target_device = iface.create_device_by_index(j)
                    break
            if target_device:
                break

        if target_device is None:
            print("[Bridge] Cámaras detectadas: {}".format(detected_names))
            err_msg = "Cámara con IP {} no encontrada".format(CAMERA_IP) if CAMERA_IP else "No se encontraron cámaras disponibles"
            raise RuntimeError(err_msg)

        self._dev = target_device

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
        return _grab_one_frame(self._ds, timeout_ms=8000, max_tries=15)

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

    def __init__(self):
        self.mode = "PAUSE"
        self.ref_id = None
        self.inspection_id = None
        self.line_id = CAMERA_LINE_ID
        self.point_id = CAMERA_POINT_ID
        self.running = True


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
                                state.mode = cmd.get("mode", "PAUSE")
                                raw_ref_id = cmd.get("ref_id", state.ref_id)
                                if raw_ref_id is not None:
                                    state.ref_id = int(raw_ref_id)
                                raw_insp_id = cmd.get("inspection_id")
                                state.inspection_id = int(raw_insp_id) if raw_insp_id is not None else None
                                print("[Bridge] Modo → {} | ref_id={} | inspection_id={}".format(
                                    state.mode, state.ref_id, state.inspection_id))

                            elif cmd_type == "ping":
                                await ws.send(json.dumps({"type": "pong"}))

                        except Exception as e:
                            print("[Bridge] Error procesando comando: {}".format(e))

                recv_task = asyncio.ensure_future(recv_commands())

                # ── Loop de captura y envío ────────────────────────────────
                try:
                    frame_count = 0
                    while state.running:
                        # Si el canal de comandos se cerró, forzar reconexión del WS.
                        if recv_task.done():
                            raise ConnectionError("Canal de comandos cerrado por backend")

                        t0 = time.time()
                        if state.mode == "PAUSE":
                            await asyncio.sleep(0.1)
                            continue

                        try:
                            frame = camera.grab()
                        except Exception as grab_err:
                            err_str = str(grab_err).lower()
                            if any(x in err_str for x in ("timeout", "retrievebuffer", "retrieve_buffer", "istdatastream")):
                                print("[Bridge] Timeout captura (reintentando): {}".format(grab_err)[:100])
                                await asyncio.sleep(0.5)
                                continue
                            raise
                        if frame is None:
                            print("[Bridge] Frame vacío, reintentando...")
                            await asyncio.sleep(0.1)
                            continue

                        # Metadata como primer mensaje (JSON)
                        meta = json.dumps({
                            "type":          "frame_meta",
                            "mode":          state.mode,
                            "line_id":       state.line_id,
                            "point_id":      state.point_id,
                            "ref_id":        state.ref_id,
                            "inspection_id": state.inspection_id,
                            "camera_id":     CAMERA_ID,
                            "timestamp":     time.time()
                        })
                        try:
                            await asyncio.wait_for(ws.send(meta), timeout=10.0)
                        except asyncio.TimeoutError:
                            print("[Bridge] Timeout enviando meta — backend no consume. Reconectando.")
                            raise ConnectionError("Send timeout on meta")

                        # Frame como segundo mensaje (bytes JPEG)
                        ret, buf = cv2.imencode(".jpg", frame, encode_params)
                        if not ret:
                            print("[Bridge] ERROR codificando JPEG")
                            continue
                        
                        jpeg_bytes = buf.tobytes()
                        try:
                            await asyncio.wait_for(ws.send(jpeg_bytes), timeout=15.0)
                        except asyncio.TimeoutError:
                            print("[Bridge] Timeout enviando frame JPEG — backend no consume. Reconectando.")
                            raise ConnectionError("Send timeout on frame")
                        
                        frame_count += 1
                        if frame_count % 10 == 0:
                            print("[Bridge] {} frames enviados. Modo: {}".format(frame_count, state.mode))

                        # Control de FPS
                        elapsed = time.time() - t0
                        sleep_t = max(0.0, frame_interval - elapsed)
                        await asyncio.sleep(sleep_t)

                finally:
                    recv_task.cancel()
                    try:
                        await asyncio.wait_for(recv_task, timeout=5.0)
                    except (asyncio.CancelledError, asyncio.TimeoutError):
                        pass

        except (websockets.exceptions.ConnectionClosed,
                websockets.exceptions.InvalidURI,
                ConnectionError,
                OSError) as e:
            print("[Bridge] Desconexión: {}. Reintentando en {}s...".format(e, retry_delay))
            await asyncio.sleep(retry_delay)
            retry_delay = min(retry_delay * 2, 30.0)  # backoff exponencial

        except Exception as e:
            err_str = str(e).lower()
            if any(x in err_str for x in ("timeout", "retrievebuffer", "retrieve_buffer")):
                print("[Bridge] Error captura (reintentando conexión en {}s): {}".format(retry_delay, e)[:120])
            else:
                print("[Bridge] Error inesperado (reintentando en {}s): {}".format(retry_delay, e))
            await asyncio.sleep(retry_delay)
            retry_delay = min(retry_delay * 1.5, 30.0)

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
