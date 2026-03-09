"""
Nuvant VA — Señal PLC Siemens S7 (snap7)
Escribe bit de defecto detectado directamente al PLC.
Configuración vía env: PLC_IP, PLC_DB, PLC_BYTE, PLC_BIT
"""
import os
import threading
from typing import Optional

_plc_lock = threading.Lock()
_plc_client = None


def _get_client():
    global _plc_client
    if _plc_client is not None:
        return _plc_client
    ip = os.getenv("PLC_IP")
    if not ip:
        return None
    try:
        import snap7
        client = snap7.client.Client()
        rack = int(os.getenv("PLC_RACK", "0"))
        slot = int(os.getenv("PLC_SLOT", "1"))
        client.connect(ip, rack, slot)
        _plc_client = client
        return _plc_client
    except Exception as e:
        print(f"[PLC] Conexión fallida: {e}")
        return None


def write_defect_signal(value: bool) -> bool:
    """
    Escribe señal de defecto al PLC.
    DB{PLC_DB}.DBX{PLC_BYTE}.{PLC_BIT}
    """
    ip = os.getenv("PLC_IP")
    if not ip:
        return False
    db_num = int(os.getenv("PLC_DB", "1"))
    byte_offset = int(os.getenv("PLC_BYTE", "0"))
    bit_offset = int(os.getenv("PLC_BIT", "0"))

    with _plc_lock:
        try:
            client = _get_client()
            if not client:
                return False

            # Leer byte actual, modificar bit, escribir (evita pisar otros bits)
            buf = bytearray(client.db_read(db_num, byte_offset, 1))
            if value:
                buf[0] = buf[0] | (1 << bit_offset)
            else:
                buf[0] = buf[0] & ~(1 << bit_offset)
            client.db_write(db_num, byte_offset, buf)
            return True
        except Exception as e:
            print(f"[PLC] Error escribiendo: {e}")
            global _plc_client
            _plc_client = None
            return False


def close_plc():
    global _plc_client
    with _plc_lock:
        if _plc_client:
            try:
                _plc_client.disconnect()
            except Exception:
                pass
            _plc_client = None
