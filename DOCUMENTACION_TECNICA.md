# Documentación Técnica (Estado Operativo Vigente)

Documento canónico del comportamiento real de la solución en producción.

## 1) Topología y responsabilidades

| Componente | Ruta | Responsabilidad |
|---|---|---|
| Orquestación | `docker-compose.yml` | Arranque de backend y bridge, red, volúmenes, variables de entorno. |
| Backend IA | `Nuvant_VA/backend/` | API FastAPI, entrenamiento, inferencia, WebSockets y persistencia. |
| Bridge cámara | `camera_bridge/` | Captura frame BGR de cámara, codifica JPEG y envía por WS al backend. |
| Frontend operativo | `Nuvant_VA/backend/api/static/index.html` | Flujo operativo (referencia, calibración, captura, entrenamiento, inspección, clasificación). |

## 2) Flujo dinámico real

1. `PAUSE` (estado seguro inicial al seleccionar referencia).
2. `CALIBRATE` (video en vivo sin decisión de defecto).
3. `TRAIN` (captura automática de frames hasta límite).
4. `train_from_camera` (submuestreo aleatorio + entrenamiento PatchCore V32).
5. `PAUSE` (post-entrenamiento).
6. `INSPECT` (inferencia continua + score + defect flag + reconocimiento opcional + heatmap + señal PLC si está configurada).

**Inspección por sesión:** Cada "Iniciar Inspección" crea un registro `Inspection`; "Detener" cierra la sesión. Los defectos se asocian a la inspección activa (`inspection_id`). El informe se genera por inspección (solo defectos de esa sesión). Defectos reconocidos (similitud > 95% con clasificados previos) se guardan con tipo; los no reconocidos van a la cola como "Sin clasificar". La cola admite filtro por inspección (`?inspection_id=X`).

Transporte:
- `WS /api/inference/camera_feed`: bridge -> backend (metadata+JPEG, incl. `inspection_id`).
- `WS /api/inference/live/{line_id}/{point_id}`: backend -> UI (broadcast de estado y resultados).
- `POST /api/inference/bridge/set_mode`: comando operativo hacia bridge.

## 3) Frontend: función exacta de cada control

### 3.1 Panel referencia

- `Nombre de Nueva Referencia` + `Crear`: crea entidad de referencia en DB.
- `Referencia Activa`: selecciona referencia para entrenar/inspeccionar.
- `Eliminar`: borra referencia y datos asociados.
- `Detener`: fuerza `PAUSE`.

### 3.2 Botones de cámara

- `Calibrar Cámara`: envía `mode=CALIBRATE`; habilita validación visual de foco/encuadre/iluminación.
- `Iniciar Captura Entrenamiento`: envía `mode=TRAIN` con límites configurados.
- `Entrenar Modelo`: ejecuta `train_from_camera` con `contamination` y `sample_size`.
- `Iniciar Inspección`: envía `mode=INSPECT` con parámetros runtime aplicables.

### 3.3 Parámetros de entrenamiento (Fase 1)

- `Rigor / Contaminación` (`contRange`):
  - etapa: entrenamiento.
  - uso: calibración base del umbral del modelo.
  - se aplica al entrenar; no cambia inferencia ya entrenada hasta nuevo entrenamiento.

- `Sensibilidad (Varianza PCA)` (`pcaRange`):
  - etapa: entrenamiento en flujo legacy V31.
  - en flujo dinámico V32 (`train_from_camera`) no gobierna la detección final; se mantiene por compatibilidad histórica.

- `Captura (frames)` (`captureLimitInput`):
  - etapa: `TRAIN`.
  - uso: límite de frames que se guardan en buffer de entrenamiento.

- `Entrenar (frames)` (`trainSampleSizeInput`):
  - etapa: `train_from_camera`.
  - uso: tamaño de muestra aleatoria tomada desde el buffer capturado.

- `Pausa defecto (s)` (`pauseOnUnknownInput`):
  - etapa: `INSPECT`.
  - uso: al detectar anomalía no reconocida, pasa a `PAUSE` por N segundos y luego reanuda `INSPECT`.

### 3.4 Parámetro de operación en caliente (Fase 2)

- `Ajuste de Umbral en Caliente` (`sensOffset`, rango -1000..1000):
  - etapa: inspección.
  - uso: modificar umbral sin reentrenar.
  - efecto:
    - positivo: más estricto (más detecciones).
    - negativo: más tolerante (menos detecciones).

### 3.5 Métricas en pantalla

- `Puntaje / Velocidad`:
  - puntaje mostrado: calidad (0..100), donde menor valor implica mayor anomalía relativa.
  - fps: velocidad de procesamiento inferencia.

- `Tendencia de Anomalía`:
  - señal graficada: `anomaly_index` (0=normal, 100=crítico), derivado de `100 - score`.
  - actualización por cada mensaje live con score/anomaly index.

### 3.6 Clasificación de defectos

- `Guardar Defecto`: persiste tipo seleccionado + score + embedding para reconocimiento posterior.
- Si la anomalía no tiene coincidencia previa, puede activarse pausa temporal según configuración.
- Tipo "Sin clasificar" existe en el catálogo; defectos nuevos se guardan con ese tipo.

### 3.7 Informe por inspección

- Desplegable **Inspección**: lista sesiones (Iniciar→Detener) de la referencia seleccionada.
- **Informe**: genera HTML con defectos de la inspección elegida; borra solo imágenes de esa inspección.

## 4) Parámetros y dónde se aplican

### 4.1 Variables de entorno backend (`docker-compose.yml`)

- `TRAIN_CAPTURE_LIMIT`: valor por defecto de captura máxima en `TRAIN`.
- `TRAIN_SAMPLE_SIZE`: valor por defecto de muestra usada en entrenamiento dinámico.
- `PATCHCORE_CORESET_RATIO`: fracción de parches retenidos en memory bank.
- `PATCHCORE_NEIGHBORS`: vecinos para cálculo de distancia en PatchCore.
- `PATCHCORE_ROI_CROP`: recorte perimetral para eliminar borde no útil.
- `PATCHCORE_USE_CLAHE`: normalización local de contraste para robustez lumínica.

**PLC S7 (opcional, vía `.env`):**
- `PLC_IP`: IP del PLC Siemens S7. Si no se define, el PLC queda deshabilitado.
- `PLC_DB`, `PLC_BYTE`, `PLC_BIT`: dirección del bit (ej. DB1.DBX0.0).
- `PLC_RACK`, `PLC_SLOT`: rack y slot S7.
- La señal se escribe durante inspección: bit 1 = defecto, bit 0 = sin defecto.
- Detalle completo: `INSTRUCCIONES_OPERATIVAS.md` sección 3.

### 4.2 Variables de entorno bridge

- `CAMERA_MODE`: `live` o `simulate`.
- `CAMERA_FPS`: tasa de captura objetivo.
- `VA_BACKEND_WS_URL`: endpoint WS backend.
- `CAMERA_LINE_ID`, `CAMERA_POINT_ID`, `CAMERA_ID`, `CAMERA_IP`: identificación y selección de dispositivo.

## 5) API de inspección

| Endpoint | Descripción |
|----------|-------------|
| `GET /api/references/{ref_id}/inspections` | Lista inspecciones de una referencia. |
| `GET /api/references/{ref_id}/inspections/{inspection_id}/report` | Informe HTML de una inspección (solo defectos de esa sesión). |
| `GET /api/references/{ref_id}/report` | Informe legacy por referencia (todos los defectos, requiere clasificación completa). |

## 6) Persistencia

Volúmenes activos:
- `./Nuvant_VA/backend/local_storage:/app/local_storage`
- `./Nuvant_VA/backend/db:/app/db`
- `./Nuvant_VA/backend/logs:/app/logs`

Persisten modelos (`model.pkl`), base SQLite y logs al recrear contenedores.

## 7) Comportamiento de detección y control

- Modelo principal para referencias nuevas: PatchCore V32.
- V31 se mantiene solo para compatibilidad con modelos legacy.
- El umbral cargado para inferencia es el guardado en el modelo entrenado.
- `contamination` define umbral base en entrenamiento.
- `sensOffset` modifica el umbral base en caliente durante inspección.
- `pause_on_unknown_sec` añade control operativo para clasificación humana antes de reanudar.

## 8) Salud y diagnóstico operativo

Checks mínimos:
- `docker compose ps`
- `curl -s http://localhost:8000/api/inference/bridge/status`
- `docker compose logs --tail=80 bridge-l1-final`
- `docker compose logs --tail=120 nuvant-backend`

Condición de video en calibración:
- bridge conectado (`count >= 1`),
- modo `CALIBRATE` entregado (`bridge_delivered=true`),
- frames enviados por bridge.

## 9) Riesgos controlados y límites

- Deriva de iluminación/exposición entre entrenamiento e inspección.
- Set de entrenamiento pequeño (alto riesgo de sobreajuste al lote).
- Configuraciones extremas de `sensOffset` pueden sesgar operación (mucho FP o FN).
- Transiciones frecuentes `INSPECT/PAUSE` reducen continuidad visual de la tendencia.

## 10) Documentos relacionados

- `INSTRUCCIONES_OPERATIVAS.md`: comandos Docker, flujo operativo, **configuración y prueba de señal PLC**.
- `OPERACION_SERVIDOR_REMOTO.md`
- `GUIA_AJUSTES_PRODUCCION.md`
- `ARQUITECTURA_Y_TEORIA_PHD.md`
