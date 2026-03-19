# Nuvant_VA (Backend + UI)

Módulo principal del sistema de visión artificial.

## Contenido

- **`backend/api/`**: API FastAPI (inferencia, entrenamiento, referencias, inspecciones, reportes).
- **`backend/core/`**: Motor PatchCore V32.5 (`anomaly_patchcore.py`), extractor de features, PLC S7.
- **`backend/api/static/`**: UI operativa (`index.html`, `classify.html`).
- **`backend/db/`**: SQLite + modelos SQLAlchemy.
- **`backend/local_storage/`**: Modelos entrenados, imágenes de defectos, reportes.

## Despliegue

El despliegue se hace desde la **raíz del repositorio**, no desde `Nuvant_VA/docker/`.

```bash
cd ~/Escritorio/Nuvant_ETL_VA_Fusion
docker compose up -d --build
```

UI: `http://localhost:8000/static/`

## Documentación

Toda la documentación canónica está en la raíz del repositorio (`../`).
