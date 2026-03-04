# Guía de Ajustes en Producción (Tuning Operativo)

Guía de tuning sin modificar algoritmo.

## 1) Qué parámetro se usa, cuándo y para qué

### 1.1 `TRAIN_CAPTURE_LIMIT` (captura)

- Dónde: `docker-compose.yml` / runtime UI (`Captura (frames)`).
- Cuándo actúa: modo `TRAIN`.
- Para qué sirve: limita cuántos frames totales se guardan en buffer.

### 1.2 `TRAIN_SAMPLE_SIZE` (muestra usada en entrenamiento)

- Dónde: `docker-compose.yml` / runtime UI (`Entrenar (frames)`).
- Cuándo actúa: `train_from_camera`.
- Para qué sirve: toma una muestra aleatoria de tamaño fijo desde lo capturado.

### 1.3 `contamination` (rigor base del modelo)

- Dónde: UI (`Rigor / Contaminación`).
- Cuándo actúa: entrenamiento (no inspección live).
- Para qué sirve: calibrar el umbral base del modelo entrenado.
- Sentido correcto:
  - `contamination` mayor -> percentil menor -> umbral más bajo -> modelo más estricto.
  - `contamination` menor -> percentil mayor -> umbral más alto -> modelo más tolerante.

### 1.4 `sensOffset` (sensibilidad en caliente)

- Dónde: UI (`Ajuste de Umbral en Caliente`, rango -1000..1000).
- Cuándo actúa: inspección live.
- Para qué sirve: mover umbral sin reentrenar.
- Sentido:
  - positivo -> más estricto.
  - negativo -> más tolerante.

### 1.5 `pca_variance` (compatibilidad)

- Dónde: UI (`Sensibilidad Varianza PCA`).
- Estado actual: relevante para flujo legacy V31; en flujo dinámico V32 no es control principal de decisión.

### 1.6 `pause_on_unknown_sec` (control operativo)

- Dónde: UI (`Pausa defecto (s)`).
- Cuándo actúa: inspección, cuando hay anomalía sin reconocimiento previo.
- Para qué sirve: dar tiempo al operador para clasificar antes de reanudar.

## 2) Rango inicial recomendado

- `capture_limit`: 100-300
- `train_sample_size`: 30-100 (mínimo funcional: 5)
- `contamination`: 0.01-0.03
- `sensOffset`: iniciar en -100 y ajustar en operación
- `pause_on_unknown_sec`: 5-15s según operación

## 3) Estrategia de ajuste

1. Fijar iluminación y posición de cámara.
2. Ejecutar `CALIBRATE`.
3. Capturar y entrenar con muestra representativa.
4. Probar `INSPECT` mínimo 2-3 minutos en estático + eventos reales.
5. Ajustar en este orden:
   - primero `sensOffset` (rápido, sin reentrenar),
   - después `contamination` (requiere reentrenar) si el slider queda en extremos.

## 4) Matriz síntoma -> acción

- Muchos falsos positivos:
  - mover `sensOffset` más negativo,
  - si persiste, reducir `contamination` y reentrenar.

- No detecta defectos reales:
  - mover `sensOffset` hacia 0/positivo,
  - si persiste, aumentar `contamination` y reentrenar.

- Comportamiento inestable por lote/luz:
  - repetir entrenamiento con muestra más representativa,
  - verificar `PATCHCORE_USE_CLAHE=true`.

## 5) Despliegue de cambios

Cambios de código/config estática:

```bash
docker compose up -d --build --force-recreate nuvant-backend bridge-l1-final
```

Cambios solo operativos en UI:
- no requieren rebuild.

## 6) Puntos de código

- `Nuvant_VA/backend/api/routers/inference.py`
- `Nuvant_VA/backend/api/static/index.html`
- `Nuvant_VA/backend/core/anomaly_patchcore.py`
- `camera_bridge/camera_bridge.py`

