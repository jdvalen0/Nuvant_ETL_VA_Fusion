# Arquitectura y Fundamentación Científica

## 1. Arquitectura de ejecución

El sistema se desacopla en dos procesos Docker:

1. **`camera_bridge`**: captura imagen desde cámara GigE Vision (stapipy), codifica JPEG, envía metadata+frame por WebSocket al backend.
2. **`nuvant-backend`**: recibe frames, ejecuta entrenamiento/inferencia, publica resultados al frontend, persiste estado en SQLite + filesystem.

Motivo del desacople: aislar fallos de hardware de la lógica ML; permitir evolución independiente.

## 2. Base científica: PatchCore (CVPR 2022)

**Referencia**: Roth, K. et al. *"Towards Total Recall in Industrial Anomaly Detection"* (arXiv:2106.08265).

### 2.1 Hipótesis

Se modela exclusivamente la distribución de normalidad. Cualquier observación fuera de esa distribución es anomalía. No se requieren imágenes de defectos para entrenar.

### 2.2 Extracción de features

- Backbone congelado `WideResNet50_2` preentrenado en ImageNet.
- Capas intermedias (`layer2` + `layer3`): capturan textura y estructura a escala media.
- `layer3` se interpola al tamaño espacial de `layer2` y se concatena → 1536 canales por patch.
- Agregación local (`AvgPool2d`, kernel 3×3, stride 1) para robustez posicional.

### 2.3 Memory bank (coreset)

- Se extraen features de todas las imágenes de entrenamiento.
- Coreset subsampling (k-center greedy): selecciona un subconjunto que maximiza la cobertura geométrica del manifold normal.
- Ratio configurable (`PATCHCORE_CORESET_RATIO`, default 0.1).
- Normalización L2 de todos los vectores para usar similitud coseno como distancia.

### 2.4 Inferencia con density re-weighting

Para cada patch de la imagen de prueba:

1. Se calcula similitud coseno con los k vecinos más cercanos del memory bank.
2. `base_dist = 1 - max_similarity` (distancia al vecino más cercano).
3. **Re-weighting** (Ecuación 3 del paper):

```
d_j = 1 - sim_j                     para j ∈ k-NN
w = max(exp(d_j)) / Σ exp(d_j)      peso del vecino más lejano
score_patch = (1 - w) · base_dist
```

- Si el vecindario k-NN es compacto: `w ≈ 1/k` → `(1-w) ≈ 0.89` → score preservado.
- Si el vecindario es disperso (zona frontera): `w` aumenta → `(1-w)` baja → score suprimido.
- Efecto: reduce falsos positivos en regiones mal cubiertas por el memory bank.

4. Score de imagen: `percentile(score_map_smoothed, 99)` (robusto contra patches ruidosos individuales).

### 2.5 Heatmap de localización

- El mapa de distancias por patch se redimensiona al tamaño original de la imagen.
- Se aplica GaussianBlur (σ=4, paper) para suavizar bordes de patches.
- Se normaliza relativo al umbral ajustado para visualización.
- Permite localizar visualmente la región anómala.

### 2.6 Calibración del umbral

- Para cada imagen de entrenamiento: se calcula su score (mismo pipeline que `predict()`).
- Se toma el percentil correspondiente a `1 - contamination` de los scores por imagen.
- Se multiplica por un margen de producción (`PATCHCORE_THRESHOLD_MARGIN`).
- Resultado: un umbral que, aplicado al set de entrenamiento, produciría `contamination × 100%` de falsos positivos.

## 3. Preprocesamiento industrial

Adaptaciones respecto al paper original para el contexto de inspección de tela:

| Etapa | Implementación | Motivo |
|-------|---------------|--------|
| ROI crop | 8% bordes recortados | Eliminar zona no útil del sensor |
| Denoising | GaussianBlur(3×3, σ=0.7) | Reducir ruido sensor/JPEG antes de features |
| CLAHE | clipLimit=2.0, tileGrid=8×8 | Robustez a variaciones de iluminación |
| Spatial smoothing | GaussianBlur(3×3, σ=1.0) en score_map | Promediar patches ruidosos aislados |
| Score aggregation | Percentil 99 (configurable) | Robusto vs max puro contra outliers |

## 4. Control temporal en producción

### Lag skip

A 15 FPS de captura y ~220ms de inferencia (CPU), el backend solo procesa ~4.5 FPS. Sin control, los frames se acumulan en buffer WebSocket con lag creciente. `INSPECT_LAG_SKIP_SEC=0.3` descarta frames >300ms de antigüedad, garantizando que cada inferencia sea sobre contenido actual.

### Debounce de entrada

`INSPECT_DEBOUNCE_FRAMES=1`: un solo frame anómalo basta para guardar defecto. El margen del umbral controla la tasa de falsos positivos.

### Debounce de salida

Una vez detectado un defecto, `_defect_active_flag` previene re-guardarlo mientras el score oscile. Se requieren 5 frames OK consecutivos (~0.33s a 15 FPS) para resetear. En rollo en movimiento, esto corresponde a material nuevo; en imagen estática, previene duplicados.

## 5. Señal PLC S7

Comunicación directa con PLC Siemens S7 vía snap7. Un bit en `DB{N}.DBX{B}.{b}` indica defecto (1) o normal (0) por cada frame procesado. Solo se escribe si el valor cambió. Ejecución en `ThreadPoolExecutor` (no bloquea event loop). Opcional: sin `PLC_IP` definido, no se intenta conexión.

## 6. Límites y buenas prácticas

- **Entrenamiento con pocas imágenes**: alta varianza del umbral, sobreajuste al lote.
- **Cambios de iluminación**: entre entrenamiento e inspección alteran la distribución → falsos positivos.
- **Velocidad del rollo**: el sistema es agnóstico a la velocidad, pero la cobertura depende de FOV vs velocidad/FPS_efectivo.
- **sensOffset extremo**: valores muy positivos/negativos sesgan la operación.
- **Mitigación**: entrenar con muestra representativa, mantener setup físico estable, usar sensOffset para ajuste fino.
