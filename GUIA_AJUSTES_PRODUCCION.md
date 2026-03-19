# Guía de Ajustes en Producción

## 1. Parámetros y su uso

### 1.1 Entrenamiento

| Parámetro | Dónde | Cuándo | Efecto |
|-----------|-------|--------|--------|
| `capture_limit` | UI / `TRAIN_CAPTURE_LIMIT` | TRAIN | Frames totales en buffer de captura |
| `train_sample_size` | UI / `TRAIN_SAMPLE_SIZE` | train_from_camera | Muestra aleatoria del buffer para entrenar |
| `contamination` | UI (Rigor) | Entrenamiento | Calibra umbral base. Mayor = más estricto |

### 1.2 Inspección en caliente

| Parámetro | Dónde | Cuándo | Efecto |
|-----------|-------|--------|--------|
| `sensOffset` | UI (Ajuste Umbral) | INSPECT | Modifica umbral sin reentrenar. Positivo = más estricto |
| `pause_on_unknown_sec` | UI (Pausa defecto) | INSPECT | Pausa N segundos ante defecto no reconocido. 0 = continuo |

### 1.3 Pipeline de detección (variables de entorno)

| Variable | Default | Requiere reentrenar | Efecto |
|----------|---------|---------------------|--------|
| `PATCHCORE_THRESHOLD_MARGIN` | 1.5 | Sí | Multiplicador de producción sobre umbral base |
| `PATCHCORE_SCORE_PERCENTILE` | 99 | Sí | Percentil para agregación. 99 = robusto; 95 = más sensible |
| `PATCHCORE_CORESET_RATIO` | 0.1 | Sí | Fracción de memory bank. Mayor = más preciso pero más lento |
| `PATCHCORE_NEIGHBORS` | 9 | No | Vecinos k-NN. Mayor = scoring más estable, más lento |
| `PATCHCORE_ROI_CROP` | 0.08 | Sí | Recorte de bordes. 0 = sin recorte |
| `PATCHCORE_USE_CLAHE` | true | Sí | Normalización de contraste |

### 1.4 Control temporal (variables de entorno)

| Variable | Default | Requiere reentrenar | Efecto |
|----------|---------|---------------------|--------|
| `INSPECT_DEBOUNCE_FRAMES` | 1 | No | Frames anómalos consecutivos para confirmar defecto |
| `INSPECT_LAG_SKIP_SEC` | 0.3 | No | Descarta frames con lag > N segundos. 0 = desactivado |
| `INSPECT_OK_FRAMES_TO_RESET` | 5 | No | Frames OK para resetear flag de defecto activo |

### 1.5 PLC S7 (archivo `.env` en raíz)

| Variable | Default | Descripción |
|----------|---------|-------------|
| `PLC_IP` | (vacío) | IP del PLC. Vacío = PLC deshabilitado |
| `PLC_DB` | 1 | Data Block |
| `PLC_BYTE` | 0 | Offset byte |
| `PLC_BIT` | 0 | Bit (0–7) |

## 2. Rangos iniciales recomendados

- `capture_limit`: 100–300
- `train_sample_size`: 30–150 (mínimo funcional: 5)
- `contamination`: 0.01–0.03
- `sensOffset`: iniciar en 0, ajustar durante inspección
- `pause_on_unknown_sec`: 0 para inspección continua; 5–15 para clasificación asistida
- `INSPECT_LAG_SKIP_SEC`: 0.3 (óptimo para ~220ms de inferencia en CPU)

## 3. Estrategia de ajuste

1. Fijar iluminación y posición de cámara.
2. `CALIBRATE`: verificar imagen en vivo.
3. Capturar y entrenar con muestra representativa (mínimo 50 imágenes).
4. `INSPECT` mínimo 2–3 minutos con rollo real.
5. Ajustar en este orden:
   - **Primero `sensOffset`** (sin reentrenar, efecto inmediato).
   - **Después `contamination`** (requiere reentrenar) si sensOffset queda en extremos.
   - **`PATCHCORE_THRESHOLD_MARGIN`** si el rango de sensOffset no es suficiente.

## 4. Matriz síntoma → acción

| Síntoma | Acción rápida | Acción estructural |
|---------|---------------|-------------------|
| Muchos falsos positivos | `sensOffset` más negativo | Reducir `contamination`, reentrenar |
| No detecta defectos reales | `sensOffset` más positivo | Aumentar `contamination`, reentrenar |
| Score oscila en estático | Normal (ruido sensor). Verificar que el debounce de salida funciona | Reducir `PATCHCORE_SCORE_PERCENTILE` a 95 |
| Lag en detección (procesa frames viejos) | `INSPECT_LAG_SKIP_SEC=0.2` | Reducir `CAMERA_FPS` o usar GPU |
| Defectos duplicados en un evento | Aumentar `INSPECT_OK_FRAMES_TO_RESET` | — |
| Defectos se pasan sin detectar | Reducir `INSPECT_DEBOUNCE_FRAMES` a 1 | Verificar FOV vs velocidad rollo |

## 5. Despliegue de cambios

| Tipo de cambio | Acción |
|----------------|--------|
| Código Python/JS/HTML | `docker compose build --no-cache nuvant-backend && docker compose up -d` + reentrenar |
| Variables en `docker-compose.yml` con "Requiere reentrenar=Sí" | Rebuild + reentrenar |
| Variables con "Requiere reentrenar=No" | Solo restart: `docker compose down && docker compose up -d` |
| Ajustes en UI (sensOffset, pausa) | Sin restart, efecto inmediato |
| Variables en `.env` (PLC_IP, CAMERA_IP) | Solo restart |
