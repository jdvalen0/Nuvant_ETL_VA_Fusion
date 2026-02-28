"""
Nuvant VA — Database Models V2
Arquitectura modular: ProductionLine → InspectionPoint → Reference → DefectLog

Diseñado para escalar a múltiples líneas/cámaras sin reescribir código:
- Fase actual: 1 línea, 1 punto, pre-poblados por defecto
- Fase futura: N líneas × N puntos via CRUD API
"""
from sqlalchemy import (
    create_engine, Column, Integer, String, Float,
    DateTime, ForeignKey, JSON
)
from sqlalchemy.orm import declarative_base, sessionmaker, relationship
from datetime import datetime

from backend.config import DATABASE_URL

engine = create_engine(DATABASE_URL, connect_args={"check_same_thread": False})
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)
Base = declarative_base()


# ══════════════════════════════════════════════════════════════════════════════
# NIVEL 1: Línea de Producción
# ══════════════════════════════════════════════════════════════════════════════
class ProductionLine(Base):
    __tablename__ = "production_lines"

    id          = Column(Integer, primary_key=True, index=True)
    name        = Column(String, unique=True, index=True)   # "Línea 1", "Línea 2"
    description = Column(String, nullable=True)
    created_at  = Column(DateTime, default=datetime.utcnow)

    points = relationship("InspectionPoint", back_populates="line",
                          cascade="all, delete-orphan")


# ══════════════════════════════════════════════════════════════════════════════
# NIVEL 2: Punto de Inspección (cámara dentro de la línea)
# ══════════════════════════════════════════════════════════════════════════════
class InspectionPoint(Base):
    __tablename__ = "inspection_points"

    id         = Column(Integer, primary_key=True, index=True)
    line_id    = Column(Integer, ForeignKey("production_lines.id"), nullable=False)
    name       = Column(String)          # "Final / Enrollado", "Inicio"
    position   = Column(String, nullable=True)   # descripción libre de posición
    camera_id  = Column(String, nullable=True)   # identificador del bridge asignado
    created_at = Column(DateTime, default=datetime.utcnow)

    line       = relationship("ProductionLine", back_populates="points")
    references = relationship("Reference", back_populates="point",
                              cascade="all, delete-orphan")


# ══════════════════════════════════════════════════════════════════════════════
# NIVEL 3: Referencia de tela (modelo PatchCore)
# ══════════════════════════════════════════════════════════════════════════════
class Reference(Base):
    __tablename__ = "references"

    id         = Column(Integer, primary_key=True, index=True)
    # FK al punto — nullable por compatibilidad con datos legacy (sin punto asignado)
    point_id   = Column(Integer, ForeignKey("inspection_points.id"), nullable=True)
    name       = Column(String, unique=True, index=True)
    created_at = Column(DateTime, default=datetime.utcnow)

    model_path     = Column(String, nullable=True)
    params         = Column(JSON, default=None)
    thumbnail_path = Column(String, nullable=True)

    point = relationship("InspectionPoint", back_populates="references")
    logs  = relationship("DefectLog", back_populates="reference",
                         cascade="all, delete-orphan")


# ══════════════════════════════════════════════════════════════════════════════
# NIVEL 4: Log de defectos
# ══════════════════════════════════════════════════════════════════════════════
class DefectLog(Base):
    __tablename__ = "defect_logs"

    id           = Column(Integer, primary_key=True, index=True)
    reference_id = Column(Integer, ForeignKey("references.id"))
    timestamp    = Column(DateTime, default=datetime.utcnow)

    anomaly_score   = Column(Float)
    is_defect       = Column(Integer)   # 0 | 1
    defect_type_id  = Column(Integer, ForeignKey("defect_types.id"), nullable=True)
    image_path      = Column(String)
    embedding       = Column(JSON, nullable=True)

    reference   = relationship("Reference", back_populates="logs")
    defect_type = relationship("DefectType", back_populates="logs")


# ══════════════════════════════════════════════════════════════════════════════
# CATÁLOGO: Tipos de defecto
# ══════════════════════════════════════════════════════════════════════════════
class DefectType(Base):
    __tablename__ = "defect_types"

    id          = Column(Integer, primary_key=True, index=True)
    name        = Column(String, unique=True)
    description = Column(String, nullable=True)

    logs = relationship("DefectLog", back_populates="defect_type")


# ══════════════════════════════════════════════════════════════════════════════
# INICIALIZACIÓN Y MIGRACIÓN
# ══════════════════════════════════════════════════════════════════════════════
def init_db():
    """
    Crea tablas si no existen y puebla datos por defecto.
    Migra referencias legacy (sin point_id) al punto por defecto.
    """
    Base.metadata.create_all(bind=engine)
    session = SessionLocal()

    try:
        # 1. Asegurar esquema (ALTER TABLE manual si es necesario)
        _ensure_columns_exist()

        # 2. Poblar datos base
        _seed_default_line_and_point(session)
        _seed_default_defect_types(session)

        # 3. Migrar datos legacy
        _migrate_legacy_references(session)
    finally:
        session.close()


def _ensure_columns_exist():
    """
    SQLAlchemy's create_all no añade columnas a tablas existentes.
    Este helper asegura que 'point_id' exista en 'references'.
    """
    import sqlite3
    db_path = DATABASE_URL.replace("sqlite:///", "")
    try:
        conn = sqlite3.connect(db_path)
        cursor = conn.cursor()

        # Verificar si 'point_id' existe en 'references'
        cursor.execute("PRAGMA table_info(\"references\")")
        columns = [row[1] for row in cursor.fetchall()]

        if 'point_id' not in columns:
            print("[DB] 🛠️ Añadiendo columna 'point_id' a tabla 'references'...")
            cursor.execute("ALTER TABLE \"references\" ADD COLUMN point_id INTEGER REFERENCES inspection_points(id)")
            conn.commit()
            print("[DB] ✅ Columna añadida correctamente.")

        conn.close()
    except Exception as e:
        print(f"[DB] ⚠️ Error en auto-migración: {e}")


def _seed_default_line_and_point(session):
    """Garantiza que exista al menos Línea 1 → Punto 1."""
    if session.query(ProductionLine).count() == 0:
        line = ProductionLine(
            name="Línea 1",
            description="Línea de producción principal"
        )
        session.add(line)
        session.flush()

        point = InspectionPoint(
            line_id=line.id,
            name="Final / Enrollado",
            position="Punto de control al final de la línea",
            camera_id="cam-l1-final"
        )
        session.add(point)
        session.commit()
        print("[DB] ✅ Línea 1 y Punto 'Final/Enrollado' creados por defecto.")
    else:
        print("[DB] Línea por defecto ya existe.")


def _seed_default_defect_types(session):
    """Inserta tipos de defecto comunes si la tabla está vacía."""
    if session.query(DefectType).count() == 0:
        defaults = [
            "Mancha de Aceite", "Rotura de Trama",
            "Destonificado", "Suciedad", "Otro"
        ]
        for name in defaults:
            session.add(DefectType(name=name))
        session.commit()
        print(f"[DB] ✅ {len(defaults)} tipos de defecto inicializados.")


def _migrate_legacy_references(session):
    """
    Las referencias creadas antes de la arquitectura multi-línea
    (point_id = NULL) se asignan automáticamente al Punto 1.
    """
    default_point = session.query(InspectionPoint).first()
    if not default_point:
        return

    orphans = session.query(Reference).filter(Reference.point_id.is_(None)).all()
    if orphans:
        for ref in orphans:
            ref.point_id = default_point.id
        session.commit()
        print(f"[DB] 🔄 {len(orphans)} referencia(s) legacy migrada(s) al Punto 1.")
