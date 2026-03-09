# Auditoría del flujo Nuvant Vision System

## Requerimientos originales (chat)

1. **Reporte por lote**: clasificados + sin clasificar, misma tabla
2. **Pausa en inspección**: delay=0 → no pausar, solo almacenar
3. **Señal PLC**: S7 directo (snap7)
4. **Clasificación**: DefectType.name (tabla aparte)
5. **Borrado de imágenes** tras generar reporte

---

## Estado de implementación

### ✅ Reporte por inspección (principal)
- **Endpoint**: `GET /api/references/{ref_id}/inspections/{inspection_id}/report`
- Solo defectos de esa inspección (sesión Iniciar→Detener)
- Borra solo imágenes de esa inspección
- Desplegable de inspecciones + botón "📊 Informe" en UI

### ✅ Reporte por referencia (legacy)
- **Endpoint**: `GET /api/references/{ref_id}/report`
- Requiere TODOS los defectos clasificados
- Parámetros: `date_from`, `date_to`

### ✅ Pausa en inspección
- `pause_on_unknown_sec` en `_runtime_control`
- `pause_sec > 0` → pausa en defecto no reconocido
- `pause_sec = 0` → no pausa, solo almacenar
- Input "Pausa defecto (s)" con placeholder "0=no pausar"

### ✅ Señal PLC S7 (Siemens)
- **Módulo:** `backend/core/plc_s7.py` (snap7)
- **Técnica:** escritura directa de un bit en Data Block del PLC. Dirección: `DB{PLC_DB}.DBX{PLC_BYTE}.{PLC_BIT}`.
- **Valor:** 1 = defecto detectado, 0 = sin defecto. Se envía por cada frame en modo INSPECT.
- **Configuración:** variables en `.env` (raíz del proyecto). Docker Compose las inyecta al contenedor.
- **Variables:** `PLC_IP` (obligatoria para activar), `PLC_DB`, `PLC_BYTE`, `PLC_BIT`, `PLC_RACK`, `PLC_SLOT`.
- **Optimización:** solo escribe si el valor cambió respecto al frame anterior.
- **Ejecución:** en ThreadPoolExecutor (no bloquea el event loop).
- **Opcional:** si `PLC_IP` no está definido, no se intenta conexión.
- **Pasos para activar y probar:** ver `../INSTRUCCIONES_OPERATIVAS.md` sección 3.

### ✅ Guardado de defectos al detectar
- `_save_defect_on_detect()` en inference.py
- Defecto detectado → DefectLog con tipo "Sin clasificar" y `inspection_id`
- Imagen en `local_storage/line_N/point_M/ref_id/defects/`
- `defect_log_id` enviado al frontend para clasificación posterior

### ✅ Clasificación de defectos
- `log_defect` acepta `defect_log_id` opcional
- Con `defect_log_id` → actualiza defecto existente
- Sin `defect_log_id` → crea nuevo (flujo manual/drag-drop)

### ✅ Informe con imágenes embebidas
- **Por inspección**: seleccionar inspección → Informe
- **Documento HTML** con imágenes embebidas (base64) y clasificaciones
- **Tras generar**: borra solo imágenes de defectos de esa inspección
- Fallback: si no hay defectos con `inspection_id`, incluye defectos con `inspection_id=NULL`

---

## Flujo gobernante

| Componente | Rol |
|------------|-----|
| `inference.py` → `camera_feed` | Loop principal: recibe frames del bridge, procesa según modo |
| `_runtime_control` | Parámetros runtime: `pause_on_unknown_sec`, `capture_limit`, `train_sample_size` |
| `_send_to_bridge` | Envía comandos al camera_bridge (set_mode) |
| `ConnectionManager` | Broadcast a frontend vía WebSocket |
| Frontend | Envía `set_mode` con parámetros al iniciar INSPECT/TRAIN |

**Modos**: CALIBRATE → TRAIN → PAUSE → INSPECT

---

## Rutas de almacenamiento

- **Modelo**: `local_storage/line_{N}/point_{M}/{ref_id}/model.pkl`
- **Defectos**: `local_storage/line_{N}/point_{M}/{ref_id}/defects/defect_{ts}_{pid}.jpg`
- **Legacy** (sin point/line): `local_storage/{ref_id}/`

---

## Dependencias

- `python-snap7==1.3` en requirements.txt
- PLC opcional: si `PLC_IP` no está definido, no se intenta conexión
