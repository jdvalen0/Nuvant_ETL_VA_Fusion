"""
Nuvant VA — Router de Líneas de Producción y Puntos de Inspección

CRUD completo para la jerarquía:
    ProductionLine → InspectionPoint

Diseñado modular: en producción actual solo habrá 1 línea y 1 punto.
Escalar = agregar datos via estos endpoints, sin cambiar código.
"""
from fastapi import APIRouter, Depends, HTTPException
from pydantic import BaseModel
from sqlalchemy.orm import Session
from typing import Optional

from backend.db.database import (
    SessionLocal, ProductionLine, InspectionPoint, Reference
)

router = APIRouter()


def get_db():
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()


# ── Schemas ────────────────────────────────────────────────────────────────

class LineCreate(BaseModel):
    name: str
    description: Optional[str] = None


class PointCreate(BaseModel):
    name: str
    position: Optional[str] = None
    camera_id: Optional[str] = None


class PointUpdate(BaseModel):
    name: Optional[str] = None
    position: Optional[str] = None
    camera_id: Optional[str] = None


# ══════════════════════════════════════════════════════════════════════════════
# LÍNEAS DE PRODUCCIÓN
# ══════════════════════════════════════════════════════════════════════════════

@router.get("/")
def list_lines(db: Session = Depends(get_db)):
    """Lista todas las líneas de producción con sus puntos."""
    lines = db.query(ProductionLine).all()
    result = []
    for line in lines:
        points = db.query(InspectionPoint).filter(
            InspectionPoint.line_id == line.id
        ).all()
        result.append({
            "id": line.id,
            "name": line.name,
            "description": line.description,
            "created_at": line.created_at,
            "points": [
                {
                    "id": p.id,
                    "name": p.name,
                    "position": p.position,
                    "camera_id": p.camera_id,
                    "reference_count": db.query(Reference).filter(
                        Reference.point_id == p.id
                    ).count(),
                }
                for p in points
            ],
        })
    return result


@router.post("/")
def create_line(body: LineCreate, db: Session = Depends(get_db)):
    if db.query(ProductionLine).filter(ProductionLine.name == body.name).first():
        raise HTTPException(400, "Ya existe una línea con ese nombre")
    line = ProductionLine(name=body.name, description=body.description)
    db.add(line)
    db.commit()
    db.refresh(line)
    return line


@router.delete("/{line_id}")
def delete_line(line_id: int, db: Session = Depends(get_db)):
    line = db.query(ProductionLine).filter(ProductionLine.id == line_id).first()
    if not line:
        raise HTTPException(404, "Línea no encontrada")
    db.delete(line)
    db.commit()
    return {"status": "deleted", "id": line_id}


# ══════════════════════════════════════════════════════════════════════════════
# PUNTOS DE INSPECCIÓN
# ══════════════════════════════════════════════════════════════════════════════

@router.get("/{line_id}/points")
def list_points(line_id: int, db: Session = Depends(get_db)):
    line = db.query(ProductionLine).filter(ProductionLine.id == line_id).first()
    if not line:
        raise HTTPException(404, "Línea no encontrada")
    points = db.query(InspectionPoint).filter(
        InspectionPoint.line_id == line_id
    ).all()
    return [
        {
            "id": p.id,
            "line_id": p.line_id,
            "name": p.name,
            "position": p.position,
            "camera_id": p.camera_id,
            "created_at": p.created_at,
            "references": [
                {"id": r.id, "name": r.name, "trained": bool(r.model_path)}
                for r in db.query(Reference).filter(
                    Reference.point_id == p.id
                ).all()
            ],
        }
        for p in points
    ]


@router.post("/{line_id}/points")
def create_point(line_id: int, body: PointCreate, db: Session = Depends(get_db)):
    line = db.query(ProductionLine).filter(ProductionLine.id == line_id).first()
    if not line:
        raise HTTPException(404, "Línea no encontrada")
    point = InspectionPoint(
        line_id=line_id,
        name=body.name,
        position=body.position,
        camera_id=body.camera_id,
    )
    db.add(point)
    db.commit()
    db.refresh(point)
    return point


@router.put("/{line_id}/points/{point_id}")
def update_point(line_id: int, point_id: int,
                 body: PointUpdate, db: Session = Depends(get_db)):
    point = db.query(InspectionPoint).filter(
        InspectionPoint.id == point_id,
        InspectionPoint.line_id == line_id
    ).first()
    if not point:
        raise HTTPException(404, "Punto no encontrado")
    if body.name is not None:
        point.name = body.name
    if body.position is not None:
        point.position = body.position
    if body.camera_id is not None:
        point.camera_id = body.camera_id
    db.commit()
    db.refresh(point)
    return point


@router.delete("/{line_id}/points/{point_id}")
def delete_point(line_id: int, point_id: int, db: Session = Depends(get_db)):
    point = db.query(InspectionPoint).filter(
        InspectionPoint.id == point_id,
        InspectionPoint.line_id == line_id
    ).first()
    if not point:
        raise HTTPException(404, "Punto no encontrado")
    db.delete(point)
    db.commit()
    return {"status": "deleted", "id": point_id}
