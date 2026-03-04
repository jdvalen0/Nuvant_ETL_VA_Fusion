# Nuvant Vision System

Sistema de inspección industrial en tiempo real con detección de anomalías no supervisada (PatchCore V32), backend FastAPI y bridge de cámara GigE.

## Estado vigente

- Flujo productivo: `CALIBRATE -> TRAIN -> PAUSE -> INSPECT`.
- Entrenamiento dinámico: captura desde cámara con límite configurable + submuestreo aleatorio configurable.
- Ajuste en caliente: slider de sensibilidad (`sensOffset`) aplicado sobre umbral ya entrenado.
- Persistencia: modelos y base de datos SQLite en volúmenes locales.

## Servicios activos

- `nuvant-backend`: API, entrenamiento, inferencia y UI.
- `bridge-l1-final`: adquisición de cámara (`stapipy`) y envío WS a backend.
- Orquestación: `docker-compose.yml` en la raíz.

## Arranque rápido

```bash
chmod +x init_deploy.sh
./init_deploy.sh
docker compose up -d --build
```

UI:
- `http://localhost:8000/static/`
- `http://<IP_SERVIDOR>:8000/static/`

## Documentación canónica

- `DOCUMENTACION_TECNICA.md`: arquitectura, flujo funcional, frontend y parámetros.
- `OPERACION_SERVIDOR_REMOTO.md`: despliegue/operación en servidor y recuperación de fallos.
- `GUIA_AJUSTES_PRODUCCION.md`: metodología de tuning (`contamination`, `sensOffset`, captura/muestra).
- `ARQUITECTURA_Y_TEORIA_PHD.md`: fundamento científico y traducción exacta al código.

## Nota

Documentos en `Nuvant_VA/docs/` se mantienen como históricos o de soporte; para operación actual usar los 4 documentos canónicos listados arriba.
