# Auditoría pre-pruebas — Checklist y verificación

Documento de auditoría y checklist antes de ejecutar pruebas. **Para cambios recientes (inspección por sesión, informe por inspección, BUG-1 a BUG-6):** ver `AUDITORIA_CAMBIOS_INSPECCION.md`.

---

## 0. Impacto en algoritmo y funcionalidad existente

**Conclusión: los cambios NO afectan el algoritmo de detección ni las funcionalidades que ya funcionaban.**

| Componente | ¿Modificado? | Impacto |
|------------|--------------|---------|
| `_sync_process_frame` | No | Algoritmo PatchCore/V31 intacto |
| `detector.predict` | No | Lógica de anomalía sin cambios |
| `FeatureExtractor`, `AnomalyDetector` | No | Extracción y predicción igual |
| `_recognize_defect` | Sí (limit) | `.limit(500)` para evitar OOM; lógica igual |
| `train_from_camera` | No | Entrenamiento igual |
| `load_model_for_point` | No | Carga de modelo igual |
| Modos CALIBRATE, TRAIN, INSPECT, PAUSE | No | Flujo de modos igual |
| `pause_on_unknown_sec`, auto-resume | No | Pausa por defecto igual |
| Broadcast a frontend | No | Mismo `result`; solo se añade `defect_log_id` cuando hay defecto guardado |
| PLC lambda | Sí (fix) | Solo corrige qué valor se escribe; no altera `result` ni broadcast |
| `_save_defect_on_detect` | Nuevo | Solo guarda; no modifica `result` salvo añadir `defect_log_id` |
| `delete_reference` | Sí | Solo amplía borrado de carpetas; no toca lógica de refs |
| `camera_bridge` CAMERA_FORCE_IP | Sí | Mismo valor por defecto (169.254.75.178); solo hace configurable |

**Flujo de inferencia (sin cambios en la lógica):**
1. Frame → `_sync_process_frame` → `result` (is_defect, score, etc.)
2. Si `is_defect`: guardar defecto (añade defect_log_id a result)
3. PLC: escribir bit (fire-and-forget, no bloquea)
4. Broadcast `result` al frontend

---

## 1. ¿Cuándo reconstruir el contenedor?

| Tipo de cambio | Reconstruir | Solo reiniciar |
|----------------|-------------|-----------------|
| Código Python (backend, inference, references, plc_s7) | ✅ | |
| Código camera_bridge | ✅ (bridge) | |
| Código frontend (HTML, JS) | ✅ | |
| Dockerfile | ✅ | |
| `.env` (PLC_IP, CAMERA_IP, etc.) | | ✅ |
| `docker-compose.yml` (env, volúmenes) | | ✅ |

**Regla:** Si modificaste archivos que están **copiados en el build** (código fuente), reconstruye. Si solo cambiaste variables de entorno o configuración externa, reinicia.

---

## 2. Captura de defectos y clasificación en segundo plano

### Flujo implementado
1. **Detección:** En modo INSPECT, cada frame con `is_defect=True` → `_save_defect_on_detect()` con `inspection_id`.
2. **Guardado:** DefectLog con tipo "Sin clasificar", imagen en `local_storage/line_1/point_1/{ref_id}/defects/`.
3. **Cola:** `GET /api/references/{ref_id}/unclassified_defects` lista defectos sin clasificar (NULL o tipo "Sin clasificar").
4. **Clasificación:** `POST /api/inference/log_defect` con `defect_log_id` actualiza el defecto existente.
5. **Informe:** Por inspección. Seleccionar inspección → Informe. Borra solo imágenes de esa inspección.

### Verificación
- [x] `_save_defect_on_detect` usa `get_storage_path(ref_id, point_id, line_id)` — ruta modular correcta.
- [x] `image_path` se guarda como ruta absoluta/relativa al storage.
- [x] `unclassified_defects` filtra `defect_type_id IS NULL` o tipo "Sin clasificar".
- [x] `log_defect` con `defect_log_id` actualiza en lugar de crear.
- [x] Report por inspección: `GET /api/references/{ref_id}/inspections/{inspection_id}/report`.

### Posibles fallos silenciosos
- **Imagen no encontrada:** Si `image_path` es incorrecto (p. ej. ruta host vs contenedor), `get_defect_image` devuelve 404. El frontend muestra "Sin imagen" y permite clasificar igual.
- **DefectLog sin timestamp:** DefectLog tiene `timestamp` con default `datetime.utcnow`. Al crear en `_save_defect_on_detect` no se pasa; SQLAlchemy usa default. Verificado en modelo.

---

## 3. Señal PLC S7

### Implementación
- `backend/core/plc_s7.py`: snap7, `write_defect_signal(value)`.
- Llamada desde `inference.py` en modo INSPECT, por frame.
- **Corrección aplicada:** Lambda de PLC capturaba variables por referencia; al ejecutarse en executor podía usar valores de un frame posterior. Corregido con argumentos por defecto: `lambda l=_lid, p=_pid, v=_val: _plc_write_defect_signal(l, p, v)`.

### Verificación
- [x] Solo escribe si el valor cambió (`_last_plc_defect`).
- [x] Ejecución en executor (no bloquea).
- [x] Si `PLC_IP` vacío, no intenta conexión.
- [x] Variables desde `.env` inyectadas por Docker Compose.

---

## 4. IP de cámara (CAMERA_IP, CAMERA_FORCE_IP)

### Implementación
- `camera_bridge.py`: `CAMERA_IP` filtra dispositivo; `CAMERA_FORCE_IP` asigna IP a la cámara al conectar.
- Si `CAMERA_FORCE_IP` vacío, no ejecuta Force IP.
- `.env` con valores actuales (169.254.75.178).

### Verificación
- [x] `CAMERA_FORCE_IP` configurable; vacío = no forzar.
- [x] Orden de filtrado: `CAMERA_IP in dev_info.display_name` (GigE suele incluir IP en display_name).
- [x] Docker Compose usa `${CAMERA_IP:-}` y `${CAMERA_FORCE_IP:-169.254.75.178}`.

---

## 5. Eliminación de referencias (delete_reference)

### Corrección aplicada
- Borra DefectLog, Inspection y Reference.
- Borra `local_storage/{ref_id}/` (legacy) y `local_storage/line_1/point_1/{ref_id}/` (modular).
- Evita carpetas huérfanas al eliminar referencias entrenadas por cámara.

---

## 6. Resumen de correcciones en esta auditoría

| Archivo | Cambio |
|---------|--------|
| `inference.py` | Lambda PLC: captura de valores por defecto para evitar closure bug |
| `references.py` | `delete_reference`: borrar también ruta modular `line_1/point_1/ref_id` |
| `INSTRUCCIONES_OPERATIVAS.md` | Tabla "¿Cuándo reconstruir vs reiniciar?" |

---

## 7. Verificación de rutas de almacenamiento

| Flujo | Ruta | get_storage_path | Consistencia |
|-------|------|------------------|--------------|
| Crear referencia | `local_storage/{ref_id}/` | `(ref_id)` | Legacy |
| Entrenar (upload) | `local_storage/{ref_id}/model.pkl` | `(ref_id)` | Legacy |
| Entrenar (cámara) | `local_storage/line_1/point_1/{ref_id}/model.pkl` | `(ref_id, point_id, line_id)` | Modular |
| Guardar defecto | `local_storage/line_1/point_1/{ref_id}/defects/` | `(ref_id, point_id, line_id)` | Modular |
| Eliminar referencia | Ambas rutas | legacy + `STORAGE_DIR/line_1/point_1/ref_id` | Correcto |

`_save_defect_on_detect(ref_id, line_id, point_id)` llama `get_storage_path(ref_id, point_id, line_id)` → `line_{line_id}/point_{point_id}/ref_id`. Correcto.

---

## 8. Checklist pre-pruebas

- [ ] `.env` configurado (PLC si aplica, cámara).
- [ ] Contenedores reconstruidos si hubo cambios de código.
- [ ] `docker compose ps` muestra ambos servicios up.
- [ ] `docker compose logs -f bridge-l1-final` muestra "Conectado a:".
- [ ] Referencia creada, calibrada, entrenada.
- [ ] Inspección probada (Iniciar → Detener); defectos guardados.
- [ ] Cola de clasificación probada; todos clasificados.
- [ ] Informe: seleccionar inspección → Informe; verificar imágenes y clasificaciones.
- [ ] Si PLC: verificar bit en DB.
