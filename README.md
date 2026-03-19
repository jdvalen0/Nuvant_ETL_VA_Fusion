# Nuvant Vision System

Sistema de inspección visual industrial en tiempo real con detección de anomalías no supervisada basada en PatchCore (CVPR 2022), backend FastAPI y bridge de cámara GigE Vision.

## Objetivo

Detectar defectos en rollos de tela en movimiento a velocidad variable usando una cámara industrial GigE Vision, un modelo PatchCore entrenado únicamente con imágenes de tela normal, y comunicación PLC S7 opcional para integración con la línea de producción.

## Arquitectura

```
┌──────────────┐   WS (meta+JPEG)   ┌──────────────────┐   WS (live)   ┌─────────┐
│ camera_bridge │ ─────────────────> │  nuvant-backend   │ ───────────> │ Browser │
│  (GigE cam)  │                    │  (FastAPI + ML)   │              │   UI    │
└──────────────┘                    └──────────────────┘              └─────────┘
                                           │
                                    ┌──────┴──────┐
                                    │  SQLite DB  │
                                    │  + Modelos  │
                                    │  + Imágenes │
                                    └─────────────┘
```

## Flujo operativo

`CALIBRATE` → `TRAIN` → `PAUSE` → `INSPECT`

1. **Calibrar**: video en vivo para ajustar foco/encuadre/iluminación.
2. **Capturar**: acumular frames de tela normal (configurable, default 200).
3. **Entrenar**: submuestreo aleatorio + PatchCore V32 con re-weighting del paper.
4. **Inspeccionar**: inferencia continua por frame con lag skip, debounce de entrada y salida, guardado de defectos, heatmap, señal PLC.

## Motor de detección (PatchCore V32.5)

- Backbone: WideResNet50_2 congelado (layers 2-3).
- Memory bank: coreset subsampling (k-center greedy).
- Scoring: k-NN con density re-weighting alineado al paper original (Eq. 3).
- Preprocesamiento: GaussianBlur denoising + CLAHE + ROI crop.
- Agregación: percentil 99 sobre score_map suavizado espacialmente.
- Umbral: calibrado por imagen durante entrenamiento con margen de producción configurable.

## Servicios Docker

| Servicio | Contenedor | Función |
|----------|-----------|---------|
| `nuvant-backend` | `nuvant-backend` | API, ML, UI, persistencia |
| `bridge-l1-final` | `bridge-linea1-final` | Captura GigE Vision + envío WS |

## Arranque

```bash
docker compose up -d --build
```

UI: `http://localhost:8000/static/` o `http://<IP_SERVIDOR>:8000/static/`

## Rebuild tras cambios de código

```bash
docker compose build --no-cache nuvant-backend && docker compose up -d
```

**Importante**: después de cambios en el pipeline de detección, es obligatorio reentrenar cada referencia activa.

## Documentación

| Documento | Contenido |
|-----------|-----------|
| `DOCUMENTACION_TECNICA.md` | Arquitectura, API, frontend, parámetros, variables de entorno |
| `INSTRUCCIONES_OPERATIVAS.md` | Comandos Docker, flujo operativo completo, PLC, cámara |
| `CHANGELOG_ESTADO_ACTUAL.md` | Correcciones aplicadas, estado vigente |
| `GUIA_AJUSTES_PRODUCCION.md` | Tuning de parámetros para producción |
| `OPERACION_SERVIDOR_REMOTO.md` | Despliegue, recuperación, acceso remoto |
| `CAPTURA_LOGS_PRUEBAS.md` | Captura y análisis de logs |
| `ARQUITECTURA_Y_TEORIA_PHD.md` | Fundamento científico PatchCore |
| `COMPARATIVA_PATCHCORE_PAPER.md` | Análisis comparativo vs paper original |
