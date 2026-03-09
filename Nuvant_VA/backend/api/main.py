from contextlib import asynccontextmanager
from fastapi import FastAPI, WebSocket
from fastapi.middleware.cors import CORSMiddleware
from fastapi.responses import RedirectResponse
from fastapi.staticfiles import StaticFiles
from pathlib import Path
from typing import Dict, List
import asyncio

from backend.db.database import init_db
from backend.api.routers import references, inference, lines


@asynccontextmanager
async def lifespan(app: FastAPI):
    init_db()
    yield
    # shutdown: cleanup si aplica


app = FastAPI(title="Nuvant VA System", version="2.0.0", lifespan=lifespan)


# ══════════════════════════════════════════════════════════════════════════════
# CONNECTION MANAGER — broadcast por (line_id, point_id)
#
# Fase actual: solo (1, 1) — diseñado para escalar a N líneas × N puntos
# sin cambiar este código.
# ══════════════════════════════════════════════════════════════════════════════

class ConnectionManager:
    def __init__(self):
        # Clave: (line_id, point_id) → lista de WebSockets del frontend
        self.active: Dict[tuple, List[WebSocket]] = {}

    async def connect(self, line_id: int, point_id: int, ws: WebSocket):
        await ws.accept()
        key = (line_id, point_id)
        if key not in self.active:
            self.active[key] = []
        self.active[key].append(ws)

    def disconnect(self, line_id: int, point_id: int, ws: WebSocket):
        key = (line_id, point_id)
        if key in self.active:
            try:
                self.active[key].remove(ws)
            except ValueError:
                pass

    async def broadcast(self, line_id: int, point_id: int, data: dict):
        key = (line_id, point_id)
        dead = []
        for ws in self.active.get(key, []):
            try:
                await ws.send_json(data)
            except Exception:
                dead.append(ws)
        for ws in dead:
            self.disconnect(line_id, point_id, ws)


manager = ConnectionManager()

# ── Buffer de frames para entrenamiento desde cámara ──────────────────────
# Clave: (line_id, point_id)
train_buffer: Dict[tuple, List[bytes]] = {}
train_buffer_lock = asyncio.Lock()


# ══════════════════════════════════════════════════════════════════════════════
# MIDDLEWARE, STATIC, STARTUP
# ══════════════════════════════════════════════════════════════════════════════

app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

STATIC_DIR = Path(__file__).parent / "static"
app.mount("/static", StaticFiles(directory=str(STATIC_DIR), html=True), name="static")


@app.get("/")
def read_root():
    return RedirectResponse(url="/static/", status_code=302)


@app.get("/favicon.ico", include_in_schema=False)
def favicon():
    from fastapi.responses import Response
    return Response(status_code=204)


# ── Routers ────────────────────────────────────────────────────────────────
app.include_router(lines.router,      prefix="/api/lines",      tags=["lines"])
app.include_router(references.router, prefix="/api/references", tags=["references"])
app.include_router(inference.router,  prefix="/api/inference",  tags=["inference"])
