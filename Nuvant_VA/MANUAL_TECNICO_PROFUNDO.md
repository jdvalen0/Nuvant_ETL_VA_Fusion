# Manual Técnico Profundo (Vigente)

Documento técnico consolidado para el estado real del sistema.

## 1) Alcance y estado

- Motor principal para referencias nuevas: PatchCore V32.
- Flujo operativo dinámico: `CALIBRATE -> TRAIN -> PAUSE -> INSPECT`.
- Ajustes operativos en UI sin alterar algoritmo base.
- Compatibilidad V31 mantenida solo para referencias legacy.

## 2) Arquitectura funcional

### 2.1 `camera_bridge`

- captura imagen desde cámara GigE (`stapipy`),
- codifica JPEG en memoria,
- envía metadata+frame a backend por WebSocket.

### 2.2 `nuvant-backend`

- controla modos del bridge (`set_mode`),
- entrena modelo con frames de cámara (`train_from_camera`),
- ejecuta inferencia continua en `INSPECT`,
- publica resultados live al frontend,
- persiste estado/modelos/defectos.

## 3) Flujo por etapas

### 3.1 `CALIBRATE`

Propósito:
- ver imagen live para ajustar foco, exposición y encuadre.

### 3.2 `TRAIN`

Propósito:
- capturar frames de tela normal para crear buffer de entrenamiento.

Control:
- limitado por `capture_limit`.

### 3.3 `train_from_camera`

Propósito:
- seleccionar muestra aleatoria (`train_sample_size`) del buffer y entrenar.

Salida:
- `model.pkl` guardado en `local_storage`.

### 3.4 `INSPECT`

Propósito:
- evaluar cada frame y devolver:
  - `score` (calidad),
  - `anomaly_index` (100 - score),
  - `is_defect`,
  - `recognition`,
  - `heatmap`.

Control operativo:
- `pause_on_unknown_sec` puede pausar cuando hay anomalía sin reconocimiento.

## 4) Parámetros críticos

### 4.1 `contamination` (rigor de entrenamiento)

- etapa: entrenamiento.
- efecto:
  - mayor valor -> detector más estricto.
  - menor valor -> detector más tolerante.

### 4.2 `sensOffset` (sensibilidad en caliente)

- etapa: inspección.
- objetivo: mover umbral sin reentrenar.
- ecuación V32:
  - `adjusted_threshold = threshold * (1 - sensitivity_offset / 1000)`
- interpretación:
  - positivo -> más estricto.
  - negativo -> más tolerante.

### 4.3 `pca_variance`

- conservado por compatibilidad de rutas legacy V31.
- en flujo dinámico V32 no gobierna la decisión principal.

## 5) Frontend: elementos operativos

### 5.1 Referencias

- crear, seleccionar y eliminar referencia.
- cambio de referencia fuerza modo seguro (`PAUSE`).

### 5.2 Entrenamiento

- `Captura (frames)`: tope de captura en `TRAIN`.
- `Entrenar (frames)`: tamaño de muestra para entrenamiento.
- `Rigor / Contaminación`: calibración base del modelo.
- `Pausa defecto (s)`: hold operativo para clasificar anomalías no reconocidas.

### 5.3 Inspección

- `Ajuste de Umbral en Caliente`: control live de umbral.
- `Tendencia de Anomalía`: serie de `anomaly_index`.
- clasificación de defectos: persistencia supervisada para reconocimiento posterior.

## 6) Persistencia y observabilidad

- DB: `backend/db/nuvant.db`.
- Modelos: `backend/local_storage/.../model.pkl`.
- Logs: `backend/logs`.
- Métricas de inspección en backend: trazas periódicas `InspectMetrics`.

## 7) Riesgos y mitigación

- entrenamiento con pocas imágenes: alta varianza y sobreajuste.
- cambios de iluminación entre entrenamiento e inspección: incremento de falsos positivos.
- uso extremo de `sensOffset`: sesgo operativo (FP/FN).

Mitigación:
- entrenar con muestra representativa,
- mantener setup físico estable,
- usar `sensOffset` para ajuste fino y `contamination` para recalibración estructural.

## 8) Referencias documentales

- `../DOCUMENTACION_TECNICA.md`
- `../GUIA_AJUSTES_PRODUCCION.md`
- `../OPERACION_SERVIDOR_REMOTO.md`
- `../ARQUITECTURA_Y_TEORIA_PHD.md`
