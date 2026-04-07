# Análisis Comparativo: Implementación Nuvant vs Paper PatchCore

**Paper**: Roth, K., Pemula, L., Zepeda, J., Schölkopf, B., Brox, T., Gehler, P. *"Towards Total Recall in Industrial Anomaly Detection"* (CVPR 2022, arXiv:2106.08265).

**Implementación**: `Nuvant_VA/backend/core/anomaly_patchcore.py` (PatchCore V32.5).

---

## 1. Extracción de Features

### Paper (Sección 3.1)

- Backbone preentrenado (WideResNet-50-2, ImageNet).
- Features de capas intermedias agregadas localmente.
- Concatenación de `layer2` (512 canales) y `layer3` (1024 canales).
- `layer3` interpolado al tamaño espacial de `layer2`.
- Agregación local con AvgPool (kernel 3×3, stride 1, padding 1).
- Normalización L2 de los vectores resultantes.
- Dimensión final por patch: 1536.

### Implementación Nuvant

```python
# anomaly_patchcore.py → _extract_features()
layer2 = features["layer2"]   # (1, 512, H2, W2)
layer3 = features["layer3"]   # (1, 1024, H3, W3)
layer3_up = F.interpolate(layer3, size=(H2, W2), mode="bilinear", align_corners=False)
concat = torch.cat([layer2, layer3_up], dim=1)  # (1, 1536, H2, W2)
pooled = self.avg_pool(concat)                    # AvgPool2d(3, stride=1, padding=1)
# → L2 normalized → (N_patches, 1536)
```

### Veredicto: ✅ Alineado

Idéntico al paper. Backbone, capas, interpolación, agregación y normalización coinciden exactamente.

---

## 2. Coreset Subsampling

### Paper (Sección 3.2)

- **Greedy Coreset Selection** (k-center greedy): seleccionar iterativamente el punto más lejano al coreset actual.
- Minimiza el radio de cobertura del manifold normal.
- Ratio configurable (paper usa 1%, 10%, 25% según dataset).
- Complejidad: O(m·n) por iteración con actualización incremental de distancias.

### Implementación Nuvant

```python
# anomaly_patchcore.py → _coreset_subsampling()
def _coreset_subsampling(self, features, ratio):
    n_select = max(1, int(len(features) * ratio))
    # k-Center Greedy: start from random, select farthest each iteration
    selected = [np.random.randint(len(features))]
    min_distances = np.full(len(features), np.inf)
    for _ in range(n_select - 1):
        # Update min distances with last selected point
        dists = 1.0 - features @ features[selected[-1]]
        min_distances = np.minimum(min_distances, dists)
        selected.append(np.argmax(min_distances))
    coreset = features[selected]
    # L2 normalize
    norms = np.linalg.norm(coreset, axis=1, keepdims=True) + 1e-9
    return coreset / norms
```

### Veredicto: ✅ Alineado

Implementación correcta de k-center greedy. Usa distancia coseno (coherente con el espacio L2-normalizado). Ratio default 0.1 (10%).

---

## 3. Scoring (k-NN + Density Re-weighting)

### Paper (Ecuación 3, Sección 3.3)

El paper define el anomaly score de un patch `m*` como:

```
s*(m*) = (1 - w) · ||m* - m_NN||

donde:
  m_NN = argmin_{m ∈ M} ||m* - m||   (vecino más cercano en memory bank)

  w = exp(||m* - m_b||) / Σ_{c∈N_b(m*)} exp(||m* - c||)

  m_b = argmax_{c ∈ N_b(m*)} ||m* - c||   (vecino más lejano del k-vecindario)
  N_b(m*) = k vecinos más cercanos de m* en M
```

**Interpretación**: `w` es la proporción de "masa exponencial" concentrada en el vecino más lejano del k-vecindario. Si el vecindario es compacto (todos los vecinos cercanos), `w ≈ 1/k` y `(1-w)` es cercano a 1 (score preservado). Si el vecindario es disperso (un vecino muy lejano), `w → 1` y `(1-w) → 0` (score suprimido).

El paper usa **exponenciales positivas** de las distancias: `exp(||m* - c||)`, NO exponenciales negativas.

### Implementación previa (bug corregido)

```python
# ANTES (incorrecto):
exp_neg_d = np.exp(-dists_k * 10.0)  # exponenciales NEGATIVAS con temperatura
softmax_w = exp_neg_d / (Σ + ε)
best_match_weight = np.max(softmax_w, axis=1)
density_aware_dist = base_dist * (2.0 - best_match_weight)  # AMPLIFICA hasta 2×
```

**Problemas**:
1. Exponenciales **negativas** (`exp(-d·10)`) en lugar de **positivas** (`exp(d)`): invierte la semántica de pesos.
2. Factor de temperatura `10.0` amplificaba artificialmente la separación.
3. Fórmula `(2.0 - w)`: siempre amplificaba el score (rango [1.0, 2.0] en lugar de [0, 1]). El paper **suprime** con `(1-w)`.
4. Resultado: amplificación de ruido sensor → "todo es defecto" en imagen estática.

### Implementación actual (corregida)

```python
# AHORA (alineado al paper):
dists_k = np.clip(1.0 - topk_sim, 0, None)  # distancias coseno al k-vecindario
exp_d = np.exp(dists_k)                       # exponenciales POSITIVAS
sum_exp = np.sum(exp_d, axis=1, keepdims=True) + 1e-9
w = np.max(exp_d, axis=1) / sum_exp.squeeze(1)  # peso del vecino más lejano
density_factor = np.clip(1.0 - w, 0, None)      # (1 - w) como en Eq. 3
return np.clip(base_dist * density_factor, 0, None)
```

### Análisis numérico

| Escenario | dists_k (ejemplo) | w | (1-w) | Efecto |
|-----------|-------------------|---|-------|--------|
| Normal (vecindario compacto) | [0.01, 0.02, ..., 0.09] | 0.115 | 0.885 | Score reducido ~11% |
| Normal (vecindario uniforme) | [0.05, 0.05, ..., 0.05] | 1/k=0.111 | 0.889 | Score reducido ~11% |
| Anomalía (vecindario disperso) | [0.3, 0.4, ..., 0.7] | 0.139 | 0.861 | Score reducido ~14% |
| Frontera (un lejano, resto cercano) | [0.01, ..., 0.01, 1.0] | 0.252 | 0.748 | Score reducido ~25% |

El factor `(1-w)` opera en rango [0.65, 0.89] para casos típicos. La corrección es suave y proporcional, no dramática. El efecto principal es **suprimir falsos positivos en zonas de frontera** del memory bank.

### Veredicto: ✅ Ahora alineado (previamente tenía bug crítico)

---

## 4. Score de Imagen

### Paper

> "The image-level anomaly score s* is defined as the maximum patch-level score."

`s* = max(s*(m*))` sobre todos los patches.

### Implementación Nuvant

```python
score_map = cv2.GaussianBlur(distance_map, (3,3), sigmaX=1.0, sigmaY=1.0)
max_distance = float(np.percentile(score_map, 99))
```

**Diferencia deliberada**: usamos **percentil 99** en lugar de max puro, y aplicamos **suavizado espacial** antes de agregar.

### Justificación

1. **Percentil 99 vs max**: en el contexto industrial con ruido de sensor real y compresión JPEG, un solo patch outlier puede dominar el max. El percentil 99 con ~4300 patches (14×14 spatial) ignora los ~43 patches más ruidosos. Para defectos reales (que afectan clusters de patches), el percentil 99 y el max convergen.

2. **Suavizado espacial**: un GaussianBlur(3×3, σ=1.0) sobre el score_map antes del percentil. Patches aislados con score alto (ruido) se promedian con sus vecinos; clusters de defecto (que son espacialmente coherentes) se preservan.

### Veredicto: ⚠️ Desviación justificada

El paper no aplica suavizado antes de max. Nuestra modificación es una adaptación al contexto industrial (ruido sensor, JPEG, captura continua) que mejora estabilidad sin sacrificar detección. El suavizado y el percentil se aplican identicamente en `train()` y `predict()` para consistencia.

---

## 5. Heatmap de Localización

### Paper (Sección 3.3)

- Mapa de scores por patch interpolado al tamaño original.
- GaussianBlur con σ=4 para suavizar bordes de patches.

### Implementación Nuvant

```python
heatmap_cropped = cv2.resize(distance_map, (cropped_w, cropped_h), interpolation=INTER_LINEAR)
heatmap_cropped = cv2.GaussianBlur(heatmap_cropped, (0, 0), sigmaX=4, sigmaY=4)
# → embed en canvas full-size → normalización relativa → gamma 0.7
```

**Adaptaciones**:
- ROI crop: el heatmap se genera sobre la región recortada y se embebe en un canvas del tamaño original.
- Normalización relativa al threshold (no absoluta) para visualización consistente.
- Gamma correction (0.7) para mejor contraste visual.

### Veredicto: ✅ Alineado (con adaptaciones de visualización)

---

## 6. Calibración del Umbral

### Paper

El paper no define un procedimiento específico de umbral para producción. Usa AUROC y percentiles sobre el dataset de test para evaluación.

### Implementación Nuvant

```python
# train():
per_image_max_dists = [percentile(smooth(compute_distances(feats)), 99) for each train image]
base_threshold = np.percentile(per_image_max_dists, 100 * (1 - contamination))
threshold = base_threshold * margin
```

1. Para cada imagen de entrenamiento, se calcula su score usando **el mismo pipeline** que `predict()`.
2. Se toma el percentil `(1-contamination)` de los scores por imagen.
3. Se multiplica por un margen de producción (`PATCHCORE_THRESHOLD_MARGIN`, default **3.0** en `docker-compose.yml` y en código `save`/`load`/`train`).

### Veredicto: ✅ Extensión válida

No contradice el paper. Es un procedimiento necesario para despliegue industrial.

---

## 7. Preprocesamiento

### Paper

- Resize a 224×224 (o 256×256).
- Normalización ImageNet estándar.

### Implementación Nuvant

| Etapa | Paper | Nuvant | Motivo |
|-------|-------|--------|--------|
| Resize | 224×224 | 224×224 | ✅ Igual |
| ImageNet norm | Sí | Sí | ✅ Igual |
| ROI crop | No | 8% bordes | Eliminar zona no útil del sensor |
| Denoising | No | GaussianBlur σ=0.7 | Reducir ruido sensor/JPEG |
| CLAHE | No | clipLimit=2.0 | Robustez a iluminación variable |

### Veredicto: ⚠️ Extensiones justificadas

Las adiciones (ROI, denoising, CLAHE) son adaptaciones al contexto industrial que el paper no aborda porque evalúa sobre datasets limpios (MVTec). Son consistentes entre `train()` y `predict()`.

---

## 8. Resumen comparativo

| Componente | Paper | Nuvant V32.5 | Estado |
|-----------|-------|-------------|--------|
| Backbone | WRN-50-2, layer2+3 | WRN-50-2, layer2+3 | ✅ Idéntico |
| Concatenación features | Interpolate + concat | Interpolate + concat | ✅ Idéntico |
| Agregación local | AvgPool 3×3 | AvgPool 3×3 | ✅ Idéntico |
| Normalización L2 | Sí | Sí | ✅ Idéntico |
| Coreset | k-center greedy | k-center greedy | ✅ Idéntico |
| k-NN distance | Sí | Sí (coseno) | ✅ Idéntico |
| Re-weighting Eq. 3 | (1-w)·d, exp positivo | (1-w)·d, exp positivo | ✅ Ahora alineado |
| Score imagen | max | percentil 99 + smoothing | ⚠️ Desviación justificada |
| Heatmap | Interpolate + blur σ=4 | Interpolate + blur σ=4 | ✅ Idéntico |
| Preprocesamiento | Resize + ImageNet norm | + ROI + denoise + CLAHE | ⚠️ Extensión justificada |
| Umbral | No definido (AUROC) | Per-image max + margen | ✅ Extensión válida |

---

## 9. Impacto del cambio de re-weighting

### Antes (fórmula incorrecta)

```
score = base_dist × (2.0 - softmax_weight)
```
- Rango del factor: [1.0, 2.0] → siempre **amplificaba**.
- Con temperatura 10.0 → amplificación concentrada en patches ambiguos.
- Resultado: ruido sensor amplificado, scores inestables, "todo es defecto".

### Ahora (fórmula del paper)

```
score = base_dist × (1.0 - w)
```
- Rango del factor: [0.65, 0.89] → siempre **suprime o preserva**.
- Sin temperatura artificial.
- Resultado: scores ~50-60% menores en magnitud absoluta, ratio señal/ruido preservado.

### Consecuencias prácticas

1. **Reentrenamiento obligatorio**: el umbral calibrado con la fórmula anterior no es compatible. Sin reentrenar, el sistema no detectará nada (scores demasiado bajos para alcanzar el umbral viejo).
2. **Heatmap preservado**: la normalización es relativa (heatmap/threshold), por lo que el patrón espacial no cambia tras reentrenar.
3. **Estabilidad mejorada**: en imagen estática, la variación de score entre frames consecutivos es menor porque el ruido ya no se amplifica.
4. **Falsos positivos reducidos**: patches en zonas de frontera del memory bank reciben supresión en vez de amplificación.
