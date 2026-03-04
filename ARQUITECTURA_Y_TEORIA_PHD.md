# Arquitectura y Fundamentación Científica

Documento de fundamento técnico-científico alineado al código vigente.

## 1) Arquitectura de ejecución

El sistema está desacoplado en dos procesos:

1. `camera_bridge`
   - captura imagen desde cámara GigE (`stapipy`),
   - codifica JPEG,
   - publica metadata+frame por WebSocket.

2. `nuvant-backend`
   - recibe frames, ejecuta entrenamiento/inferencia,
   - publica resultados live al frontend,
   - persiste referencia/modelo/defectos en SQLite+filesystem.

Motivo del desacople:
- aislar fallos de hardware de la lógica de inferencia,
- permitir evolución del backend sin alterar driver/captura.

## 2) Base científica del detector principal (PatchCore V32)

Referencia: *Towards Total Recall in Industrial Anomaly Detection* (CVPR 2022).

### 2.1 Hipótesis de trabajo

Se modela solo la distribución de normalidad (tela buena).  
Una observación fuera de esa distribución se considera anomalía.

### 2.2 Extracción de representación

- Backbone congelado `WideResNet50_2` preentrenado.
- Uso de capas intermedias (`layer2`, `layer3`) para capturar textura estructural.
- Agregación local (`AvgPool2d`) para robustez espacial.

### 2.3 Coreset

- Los patches normales se reducen mediante k-center greedy.
- Se conserva cobertura geométrica del manifold normal con menor memoria.

### 2.4 Inferencia

- Para cada patch de prueba se calcula distancia al vecino más cercano del memory bank.
- Score de imagen: máximo de distancias de patch.
- Decisión: score vs umbral calibrado en entrenamiento.

## 3) Calibración y puntajes implementados

### 3.1 Umbral base en entrenamiento

El umbral se calcula desde la distribución de distancias del set normal de entrenamiento, con factor de seguridad técnico sobre máximo observado.

### 3.2 Puntaje operativo

El backend expone:
- `score` (calidad relativa, 0..100; menor valor implica mayor anomalía),
- `anomaly_index` (0..100; mayor valor implica mayor anomalía), donde:

`anomaly_index = 100 - score`

### 3.3 Heatmap

Se genera mapa de distancias de patch, se interpola a imagen y se normaliza relativo al umbral ajustado.

## 4) Parámetros de control y su fundamento

### 4.1 `contamination` (rigor en entrenamiento)

Uso:
- define percentil de calibración del umbral base.

Efecto:
- mayor `contamination` -> umbral más bajo -> detector más estricto.
- menor `contamination` -> umbral más alto -> detector más tolerante.

### 4.2 `sensOffset` (rigor en inspección)

Uso:
- ajuste en caliente del umbral sin reentrenar.

Ecuación V32:
- `adjusted_threshold = threshold * (1 - sensitivity_offset/1000)`

Efecto:
- positivo: más estricto.
- negativo: más tolerante.

### 4.3 `pca_variance`

Se mantiene por compatibilidad con rutas legacy V31; en flujo dinámico V32 no es el control principal de decisión.

## 5) Compatibilidad V31

El código mantiene compatibilidad para modelos legacy Mahalanobis V31:
- carga de modelos previos,
- fallback controlado.

No se recomienda entrenar nuevas referencias en V31 cuando V32 está disponible.

## 6) Implementación real en código

Rutas principales:
- `Nuvant_VA/backend/core/anomaly_patchcore.py`
- `Nuvant_VA/backend/api/routers/inference.py`
- `Nuvant_VA/backend/api/static/index.html`
- `camera_bridge/camera_bridge.py`

## 7) Límites y buenas prácticas experimentales

- Entrenamiento con muy pocas imágenes reduce robustez (sobreajuste).
- Cambios de iluminación entre entrenamiento e inspección alteran la distribución.
- Ajustes extremos de `sensOffset` sesgan operación (FP/FN).
- Para estabilidad: fijar setup físico, entrenar con muestra representativa y usar slider como ajuste fino.
