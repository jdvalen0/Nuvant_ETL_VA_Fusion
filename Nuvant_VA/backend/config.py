import os
from pathlib import Path

# ── Raíz del proyecto ──────────────────────────────────────────────────────
BASE_DIR = Path(__file__).resolve().parent.parent

# ── Almacenamiento de modelos ──────────────────────────────────────────────
STORAGE_DIR = Path(os.getenv("STORAGE_DIR", BASE_DIR / "local_storage"))

# ── Base de datos ──────────────────────────────────────────────────────────
DATABASE_URL = os.getenv("DATABASE_URL", f"sqlite:///{BASE_DIR}/db/nuvant.db")

# ── Garantizar directorios ─────────────────────────────────────────────────
os.makedirs(STORAGE_DIR, exist_ok=True)
os.makedirs(BASE_DIR / "db", exist_ok=True)


def get_storage_path(ref_id: int,
                     point_id: int = None,
                     line_id: int = None) -> Path:
    """
    Retorna la ruta de almacenamiento para un modelo.

    Estructura jerárquica (modular para escalar a multi-línea):
        local_storage/line_{N}/point_{M}/{ref_id}/

    Si no se proveen line_id/point_id usa rutas legacy planas:
        local_storage/{ref_id}/
    """
    if line_id is not None and point_id is not None:
        path = STORAGE_DIR / f"line_{line_id}" / f"point_{point_id}" / str(ref_id)
    else:
        path = STORAGE_DIR / str(ref_id)

    path.mkdir(parents=True, exist_ok=True)
    return path
