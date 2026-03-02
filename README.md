# Nuvant Vision System

Sistema de inspección industrial en tiempo real basado en detección de anomalías no supervisada (PatchCore V32), compuesto por backend de inferencia y bridge de cámara.

## Estado operativo actual

- Flujo principal validado: `CALIBRATE -> TRAIN -> PAUSE -> INSPECT`.
- Entrenamiento dinámico desde cámara: captura configurable y submuestreo aleatorio para entrenar.
- Acceso remoto validado en red (backend expuesto en `:8000`).

## Arquitectura desplegada

- `nuvant-backend` (FastAPI + PatchCore + SQLite).
- `bridge-l1-final` (captura Omron/Sentech `stapipy`, envío por WebSocket).
- Orquestación principal: `docker-compose.yml` (raíz del repositorio).

## Arranque rápido

```bash
chmod +x init_deploy.sh
./init_deploy.sh
docker compose up -d --build
```

UI:
- `http://localhost:8000/static/`
- `http://<IP_SERVIDOR>:8000/static/` (acceso remoto)

## Documentación operativa

- `DOCUMENTACION_TECNICA.md` -> arquitectura real y mapa de componentes.
- `OPERACION_SERVIDOR_REMOTO.md` -> despliegue y acceso desde otros equipos.
- `GUIA_AJUSTES_PRODUCCION.md` -> parametros ajustables para rigidez/sensibilidad y entrenamiento.
- `ARQUITECTURA_Y_TEORIA_PHD.md` -> teoria avanzada (referencia conceptual).

## Nota de versionado documental

Algunos archivos en `Nuvant_VA/docs/` son historicos y no reflejan totalmente el flujo actual de operacion. Para despliegue productivo usar los tres documentos listados arriba.
