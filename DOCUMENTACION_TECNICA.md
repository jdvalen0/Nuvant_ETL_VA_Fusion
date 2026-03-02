# Documentación Técnica (Estado Operativo Actual)

Documento de arquitectura y operación técnica alineado con el estado actual del repositorio.

## 1) Topología real del sistema

| Componente | Ruta | Función |
|---|---|---|
| Orquestación | `docker-compose.yml` | Levanta backend + bridge de cámara. |
| Backend IA | `Nuvant_VA/backend` | API FastAPI, entrenamiento/inferencia, WS y persistencia. |
| Bridge cámara | `camera_bridge/` | Captura con `stapipy`, empaqueta JPEG+meta y envía por WS. |
| UI operativa | `Nuvant_VA/backend/api/static/index.html` | Operación en línea (calibrar/capturar/entrenar/inspeccionar). |

## 2) Flujo operativo vigente

Flujo recomendado en planta:

1. `CALIBRATE` (ajuste visual sin inferencia).
2. `TRAIN` (captura limitada de frames normales).
3. entrenamiento (`train_from_camera`) con submuestreo aleatorio.
4. `PAUSE`.
5. `INSPECT`.

Endpoints y sockets clave:

- `POST /api/inference/bridge/set_mode`
- `WS /api/inference/camera_feed` (bridge -> backend)
- `WS /api/inference/live/{line_id}/{point_id}` (backend -> UI)

## 3) Parametrización productiva activa

Configurada en `docker-compose.yml` (servicio `nuvant-backend`):

- `PATCHCORE_USE_CLAHE=true`
- `TRAIN_CAPTURE_LIMIT=200`
- `TRAIN_SAMPLE_SIZE=50`
- `PATCHCORE_CORESET_RATIO=0.1`
- `PATCHCORE_NEIGHBORS=9`
- `PATCHCORE_ROI_CROP=0.08`

Bridge (`bridge-l1-final`):

- `CAMERA_MODE=live`
- `CAMERA_FPS=${CAMERA_FPS:-5.0}`
- `VA_BACKEND_WS_URL=ws://localhost:8000/api/inference/camera_feed`

## 4) Persistencia

Bind mounts activos:

- `./Nuvant_VA/backend/local_storage:/app/local_storage`
- `./Nuvant_VA/backend/db:/app/db`
- `./Nuvant_VA/backend/logs:/app/logs`

Esto conserva modelos y base SQLite entre recreaciones de contenedor.

## 5) Salud, red y acceso remoto

- backend expuesto en `0.0.0.0:8000`
- acceso local: `http://localhost:8000/static/`
- acceso remoto: `http://<IP_SERVIDOR>:8000/static/`

## 6) Donde ajustar comportamiento (mapa rapido)

- Captura de entrenamiento:
  - `TRAIN_CAPTURE_LIMIT` en `docker-compose.yml`
  - consumo en `Nuvant_VA/backend/api/routers/inference.py`
- Muestra de entrenamiento (aleatoria):
  - `TRAIN_SAMPLE_SIZE` en `docker-compose.yml`
  - aplicado en `train_from_camera` de `inference.py`
- Rigidez del modelo:
  - `contamination` en UI (`index.html`, slider `contRange`)
  - default API en `TrainFromCameraRequest` (`inference.py`)
  - sensibilidad en caliente `sensOffset` (`index.html`)
- Normalización fotométrica:
  - `PATCHCORE_USE_CLAHE` en `docker-compose.yml`

## 7) Riesgos operativos observados y control

- Deriva de iluminación/exposición puede producir falsos positivos.
- Mantener setup físico estable entre entrenamiento e inspección.
- Usar `CALIBRATE` antes de `TRAIN` e `INSPECT`.
- Evitar mezclar referencias antiguas con condiciones de cámara distintas.
- La carga de PatchCore usa el umbral exacto guardado en el modelo. Si falta ese campo en un modelo legado, se requiere reentrenar la referencia.

## 8) Referencias documentales

- Operación de despliegue: `OPERACION_SERVIDOR_REMOTO.md`
- Ajustes finos y tuning: `GUIA_AJUSTES_PRODUCCION.md`
- Teoría avanzada: `ARQUITECTURA_Y_TEORIA_PHD.md`
