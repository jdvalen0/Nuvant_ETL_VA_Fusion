# Documentación Técnica — Estado Operativo Vigente

## 1. Topología

| Componente | Ruta | Responsabilidad |
|---|---|---|
| Orquestación | `docker-compose.yml` | Servicios, red, volúmenes, variables de entorno |
| Backend IA | `Nuvant_VA/backend/` | API FastAPI, entrenamiento, inferencia, WebSockets, persistencia |
| Bridge cámara | `camera_bridge/` | Captura GigE Vision (stapipy), codifica JPEG, envía por WS |
| Frontend | `Nuvant_VA/backend/api/static/` | `index.html` (operación), `classify.html` (cola clasificación) |
| Motor detección | `Nuvant_VA/backend/core/anomaly_patchcore.py` | PatchCore V32.5 |
| PLC S7 | `Nuvant_VA/backend/core/plc_s7.py` | Señal de defecto a PLC Siemens (opcional) |

## 2. Flujo dinámico

### Modos de operación

1. **PAUSE**: estado seguro inicial.
2. **CALIBRATE**: video en vivo sin procesamiento ML. Para ajustar foco/encuadre/iluminación.
3. **TRAIN**: captura automática de frames hasta `capture_limit`. Buffer en memoria.
4. **train_from_camera**: submuestreo aleatorio del buffer + entrenamiento PatchCore V32.5.
5. **INSPECT**: inferencia continua con lag skip + debounce + guardado de defectos + heatmap + señal PLC.

### Inspección por sesión

- Cada "Iniciar Inspección" crea un registro `Inspection` en DB.
- "Detener" cierra la sesión (`stopped_at`).
- Todos los defectos se asocian a la inspección activa (`inspection_id`).
- El informe se genera por inspección.

### Transporte

| Canal | Dirección | Contenido |
|-------|-----------|-----------|
| `WS /api/inference/camera_feed` | bridge → backend | Metadata JSON + JPEG binario |
| `WS /api/inference/live/{line_id}/{point_id}` | backend → browser | Estado, resultados, imágenes |
| `POST /api/inference/bridge/set_mode` | backend → bridge | Comandos de modo |

## 3. Motor PatchCore V32.5

### Pipeline de inferencia

```
Imagen JPEG
  → cv2.imdecode
  → ROI crop (8% bordes)
  → GaussianBlur(3x3, σ=0.7)    ← denoising sensor/JPEG
  → CLAHE (clipLimit=2.0)        ← normalización lumínica
  → Resize 224×224
  → WideResNet50_2 (layer2+3)   ← extracción de features
  → k-NN vs memory bank          ← distancias
  → Density re-weighting (1-w)·d ← paper Eq. 3
  → Reshape H×W
  → GaussianBlur(3x3, σ=1.0)    ← smoothing espacial
  → Percentil 99                 ← score robusto
  → score vs threshold           ← decisión
```

### Density re-weighting (Eq. 3 del paper)

```
w = max(exp(d_j)) / Σ exp(d_j)     para j ∈ k-NN
score = (1 - w) · base_dist
```

- `w` captura qué tan dominante es el vecino más lejano.
- `(1-w)` suprime scores de patches con match confiable (normal bien cubierto).
- Rango típico de `(1-w)`: 0.65–0.89.

### Calibración de umbral

- Se calcula sobre las distancias **máximas por imagen** del set de entrenamiento.
- Percentil 97% (con `contamination=0.03`) × margen de producción (default 3.0×).
- El mismo pipeline (smoothing + percentil) se aplica en `train()` y `predict()`.

## 4. Mecanismos de control temporal

### Lag skip (`INSPECT_LAG_SKIP_SEC`)

La cámara captura a 15 FPS (66ms/frame) pero la inferencia toma ~220ms/frame en CPU. Sin lag skip, el buffer WS acumula frames y el backend procesa frames obsoletos con lag creciente.

Con `INSPECT_LAG_SKIP_SEC=0.3`: frames con >300ms de antigüedad se descartan. El backend siempre procesa el frame más reciente disponible. Solo aplica en modo INSPECT.

### Debounce de entrada (`INSPECT_DEBOUNCE_FRAMES`)

N frames consecutivos anómalos requeridos para confirmar un defecto. Default: 1 (inmediato). Con N=1, el umbral `PATCHCORE_THRESHOLD_MARGIN` controla falsos positivos.

### Debounce de salida (`_defect_active_flag`)

Una vez guardado un defecto, el flag permanece activo. Se requieren N frames OK consecutivos (`INSPECT_OK_FRAMES_TO_RESET`, default 5) para resetear. Previene re-guardar el mismo defecto en oscilación de score. Para rollo a 15 FPS, 5 frames OK = 0.33s de material nuevo sin defecto.

## 5. Variables de entorno

### Backend (`docker-compose.yml`)

| Variable | Default | Descripción |
|----------|---------|-------------|
| `PATCHCORE_CORESET_RATIO` | 0.1 | Fracción de patches retenidos en memory bank |
| `PATCHCORE_NEIGHBORS` | 9 | Vecinos k-NN para scoring |
| `PATCHCORE_ROI_CROP` | 0.08 | Recorte perimetral (fracción) |
| `PATCHCORE_USE_CLAHE` | true | Normalización local de contraste |
| `PATCHCORE_THRESHOLD_MARGIN` | 1.5 | Multiplicador de producción sobre umbral base |
| `PATCHCORE_SCORE_PERCENTILE` | 99 | Percentil para agregación de score |
| `INSPECT_DEBOUNCE_FRAMES` | 1 | Frames anómalos para confirmar defecto |
| `INSPECT_LAG_SKIP_SEC` | 0.3 | Descarta frames más viejos que N segundos |
| `INSPECT_OK_FRAMES_TO_RESET` | 5 | Frames OK para resetear flag de defecto |
| `TRAIN_CAPTURE_LIMIT` | 200 | Frames máximos en buffer de captura |
| `TRAIN_SAMPLE_SIZE` | 150 | Muestra aleatoria para entrenamiento |
| `PLC_IP` | (vacío) | IP del PLC S7. Vacío = PLC deshabilitado |
| `PLC_DB` | 1 | Data Block del PLC |
| `PLC_BYTE` | 0 | Offset byte |
| `PLC_BIT` | 0 | Bit dentro del byte (0–7) |

### Bridge

| Variable | Default | Descripción |
|----------|---------|-------------|
| `CAMERA_MODE` | live | `live` o `simulate` |
| `CAMERA_FPS` | 15.0 | Tasa de captura objetivo |
| `CAMERA_LINE_ID` | 1 | ID de línea |
| `CAMERA_POINT_ID` | 1 | ID de punto de inspección |
| `CAMERA_IP` | (vacío) | IP cámara GigE (vacío = primera disponible) |
| `CAMERA_FORCE_IP` | (vacío) | Forzar IP a la cámara al conectar |

## 6. API principal

### Inspección

| Endpoint | Descripción |
|----------|-------------|
| `GET /api/references/{ref_id}/inspections` | Lista inspecciones |
| `GET /api/references/{ref_id}/inspections/{insp_id}/report` | Informe HTML |
| `GET /api/references/{ref_id}/unclassified_defects?inspection_id=X` | Cola clasificación |
| `POST /api/inference/bridge/set_mode` | Cambiar modo (INSPECT, TRAIN, CALIBRATE, PAUSE) |
| `POST /api/inference/train_from_camera` | Entrenar desde buffer de cámara |
| `GET /api/inference/bridge/status` | Estado del bridge |

### Informes

- Solo incluyen defectos **clasificados** (automáticamente reconocidos + clasificados manualmente).
- Defectos "Sin clasificar" se **excluyen** del informe.
- El botón de informe se deshabilita si hay defectos pendientes de clasificación en esa inspección.
- Tras generar, se borran las imágenes de defectos de esa inspección.

## 7. Frontend

### Badges de detección

| Estado | Badge | Color |
|--------|-------|-------|
| Defecto nuevo guardado | "NUEVO DEFECTO REGISTRADO #N" | Rojo |
| Mismo defecto en seguimiento | "DEFECTO #N EN SEGUIMIENTO" | Ámbar |
| Sin defecto | "CALIDAD OK" | Verde |
| Error de modelo | Mensaje de error | Naranja |

### Parámetros de UI

- **Rigor/Contaminación**: calibración base del umbral (solo al entrenar).
- **Sensibilidad (sensOffset)**: ajuste de umbral en caliente durante inspección. Positivo = más estricto.
- **Captura (frames)**: límite de frames en TRAIN.
- **Entrenar (frames)**: muestra aleatoria para entrenamiento.
- **Pausa defecto (s)**: pausa al detectar defecto no reconocido (0 = continuo).

## 8. Persistencia

| Contenido | Ruta (host) |
|-----------|-------------|
| Base de datos | `Nuvant_VA/backend/db/nuvant.db` |
| Modelos | `Nuvant_VA/backend/local_storage/line_N/point_M/{ref_id}/model.pkl` |
| Defectos | `Nuvant_VA/backend/local_storage/line_N/point_M/{ref_id}/defects/` |
| Reportes | `Nuvant_VA/backend/local_storage/reports/` |

Persisten entre recreaciones de contenedores (volúmenes bind).

## 9. Diagnóstico

```bash
docker compose ps
curl -s http://localhost:8000/api/inference/bridge/status
docker compose logs --tail=100 nuvant-backend
docker compose logs --tail=100 bridge-l1-final
```

Patrones de log relevantes:
- `[InspectMetrics]`: score, threshold, is_defect por frame.
- `[LagSkip]`: frames descartados por lag.
- `[DefectLog]`: defectos guardados.
- `[PLC]`: errores de conexión PLC.
