import os
import time
import cv2
import numpy as np
import stapipy as st


def get_node(nodemap, name):
    try:
        return nodemap.get_node(name)
    except Exception:
        return None


def try_set(nodemap, name, value):
    node = get_node(nodemap, name)
    if node is None:
        print(f"[SKIP] Nodo no existe: {name}")
        return False
    try:
        node.value = value
        print(f"[OK] {name} = {value}")
        return True
    except Exception as e:
        print(f"[WARN] No pude setear {name} a {value}: {e}")
        return False


def convert_to_numpy(st_image):
    data = st_image.get_image_data()
    h, w = st_image.height, st_image.width
    pf = st.get_pixel_format_info(st_image.pixel_format)

    if pf.is_mono:
        return np.frombuffer(data, np.uint8).reshape(h, w)

    if pf.is_bayer:
        raw = np.frombuffer(data, np.uint8).reshape(h, w)
        return cv2.cvtColor(raw, cv2.COLOR_BAYER_BG2BGR)

    raise ValueError(f"PixelFormat no soportado: {st_image.pixel_format}")


def grab_one_frame(ds, timeout_ms=5000, max_tries=50):
    """
    Intenta leer hasta max_tries buffers para obtener un frame completo.
    Devuelve numpy array o None si no se logró.
    """
    for i in range(max_tries):
        with ds.retrieve_buffer(timeout=timeout_ms) as buf:
            if buf.info.is_incomplete or (not buf.info.is_image_present):
                if i % 10 == 0:
                    try:
                        print(f"[WARN] Incompleto: filled={buf.info.size_filled}/{buf.info.buffer_size}")
                    except Exception:
                        print("[WARN] Incompleto")
                continue

            img = buf.get_image()
            return convert_to_numpy(img)

    return None


def capture_every_60s(out_dir="captures", interval_s=60, timeout_ms=5000):
    os.makedirs(out_dir, exist_ok=True)

    st.initialize()
    sys = st.create_system()
    dev = sys.create_first_device()
    print("Connected to device:", dev.info.display_name)

    ds = dev.create_datastream()
    nm = dev.remote_port.nodemap

    # Configuración GigE/GenICam (ANTES de iniciar streaming)
    try_set(nm, "TriggerMode", 0)
    try_set(nm, "TriggerSelector", 0)
    try_set(nm, "AcquisitionMode", 2)

    # Red: mantener 1500 si no confirmas jumbo end-to-end
    try_set(nm, "GevSCPSPacketSize", 1500)

    # Clave para tu caso (reduce pérdida de paquetes): ajusta si hace falta
    try_set(nm, "GevSCPD", 20000)

    # Baja FPS si el nodo lo permite (en tu caso existe AcquisitionFrameRate)
    try_set(nm, "AcquisitionFrameRate", 5.0)

    # Bloqueo opcional de TL params
    try_set(nm, "TLParamsLocked", 1)

    # Start (orden que en tu entorno funciona)
    ds.start_acquisition()
    dev.acquisition_start()
    print("[OK] Streaming iniciado. Guardando 1 imagen cada", interval_s, "segundos.")

    try:
        while True:
            t0 = time.time()

            frame = grab_one_frame(ds, timeout_ms=timeout_ms, max_tries=80)
            if frame is None:
                print("[ERROR] No se pudo obtener un frame completo en este ciclo.")
            else:
                ts = time.strftime("%Y%m%d-%H%M%S")
                path = os.path.join(out_dir, f"frame_{ts}.png")
                ok = cv2.imwrite(path, frame)
                if ok:
                    print("[OK] Guardado:", path)
                else:
                    print("[ERROR] cv2.imwrite falló:", path)

            # Espera hasta completar el intervalo (60s)
            elapsed = time.time() - t0
            sleep_s = max(0, interval_s - elapsed)
            time.sleep(sleep_s)

    finally:
        # Stop limpio
        try:
            dev.acquisition_stop()
        except Exception:
            pass
        try:
            ds.stop_acquisition()
        except Exception:
            pass
        try_set(nm, "TLParamsLocked", 0)
        print("[DONE] Adquisición detenida.")


if __name__ == "__main__":
    capture_every_60s(out_dir="captures", interval_s=60, timeout_ms=5000)
