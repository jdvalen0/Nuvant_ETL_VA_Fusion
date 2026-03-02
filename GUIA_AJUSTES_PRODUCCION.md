# Guía de Ajustes en Producción (Tuning Operativo)

Documento de referencia para ajustar el sistema durante despliegue sin modificar arquitectura.

## 1) Parámetros clave y dónde se cambian

## Captura de entrenamiento (cantidad de frames)

- Variable: `TRAIN_CAPTURE_LIMIT`
- Archivo: `docker-compose.yml` (servicio `nuvant-backend`, `environment`)
- Uso en código: `Nuvant_VA/backend/api/routers/inference.py` (`camera_feed`)

Efecto:
- define cuántas imágenes máximas se capturan en modo `TRAIN`.

## Muestra de entrenamiento usada por el modelo

- Variable: `TRAIN_SAMPLE_SIZE`
- Archivo: `docker-compose.yml`
- Uso en código: `Nuvant_VA/backend/api/routers/inference.py` (`train_from_camera`)

Efecto:
- de las imágenes capturadas, toma `TRAIN_SAMPLE_SIZE` aleatorias para entrenar.

## Rigidez del detector (entrenamiento)

- Variable lógica: `contamination`
- UI: `Nuvant_VA/backend/api/static/index.html` (`contRange`)
- Backend default: `TrainFromCameraRequest.contamination` en `inference.py`

Efecto:
- menor `contamination` -> más estricto (más detecciones).
- mayor `contamination` -> más tolerante (menos falsos positivos).

## Rigidez del detector (inspección en caliente)

- Control UI: `sensOffset`
- Archivo: `Nuvant_VA/backend/api/static/index.html`
- Envío WS: `set_sensitivity`
- Aplicación en backend: `predict(... sensitivity_offset=...)`

Efecto:
- `sensOffset` negativo -> menos estricto.
- `sensOffset` positivo -> más estricto.

## Normalización fotométrica

- Variable: `PATCHCORE_USE_CLAHE`
- Archivo: `docker-compose.yml`
- Valor recomendado de base: `true`

Efecto:
- mejora robustez ante variación de iluminación.

## Umbral cargado del modelo

- Archivo: `Nuvant_VA/backend/core/anomaly_patchcore.py` (`load`)
- Comportamiento actual: usa exactamente el `threshold` guardado en `model.pkl`.
- Si falta `threshold` en un modelo antiguo/corrupto, lanza error y exige reentrenar.

## 2) Valores base recomendados (arranque productivo)

- `TRAIN_CAPTURE_LIMIT=200`
- `TRAIN_SAMPLE_SIZE=50`
- `PATCHCORE_USE_CLAHE=true`
- `contamination` inicial: `0.03`
- `sensOffset` inicial: `-100`

## 3) Cómo desplegar cambios de parámetros

```bash
docker compose up -d --build --force-recreate nuvant-backend bridge-l1-final
```

Verificación rápida de UI:
```bash
curl -s http://localhost:8000/static/ | grep -E 'id="contVal"|id="contRange"|id="sensOffset"|id="currentSensVal"'
```

## 4) Estrategia de ajuste sin romper operación

1. Fijar setup de cámara/iluminación.
2. Ejecutar `CALIBRATE`.
3. Capturar `TRAIN` y entrenar.
4. Probar `INSPECT` en estático 2-3 min.
5. Si hay falsos positivos:
   - primero bajar rigidez en caliente (`sensOffset` más negativo),
   - luego subir `contamination` en próximo entrenamiento (ej. `0.03 -> 0.04`),
   - mantener `TRAIN_CAPTURE_LIMIT` alto y `TRAIN_SAMPLE_SIZE` fijo.

## 5) Matriz rápida de síntomas -> ajuste

- Sintoma: "todo defecto en estático"
  - bajar rigidez (`sensOffset` negativo), reentrenar con `contamination` mayor.

- Sintoma: "no detecta fallos reales"
  - subir rigidez (`sensOffset` hacia 0/positivo), reentrenar con `contamination` menor.

- Sintoma: "inicia bien y deriva a defecto"
  - revisar estabilidad de iluminación/exposición; mantener `CLAHE=true`.

## 6) Rutas de código críticas para mantenimiento

- Backend inferencia y entrenamiento: `Nuvant_VA/backend/api/routers/inference.py`
- Frontend operación: `Nuvant_VA/backend/api/static/index.html`
- Bridge de cámara: `camera_bridge/camera_bridge.py`
- Orquestación de entorno: `docker-compose.yml`

