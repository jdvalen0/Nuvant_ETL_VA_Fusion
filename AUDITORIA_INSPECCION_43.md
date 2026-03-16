# Auditoría — Inspección 43 y reportes

**Fecha:** 2026-03-16

---

## 1. Cambios aplicados

### 1.1 Informe con defectos clasificados Y sin clasificar

**Antes:** `report_by_reference` devolvía **400** si había defectos sin clasificar.  
**Ahora:** Se genera el informe y se muestran **todos** (clasificados y sin clasificar).  
- Banner de aviso: "⚠️ Este informe incluye N defecto(s) sin clasificar"  
- `report_by_inspection` ya incluía ambos; se mantiene igual.

### 1.2 Log al guardar defecto

Se añadió en `inference.py`:
```
[DefectLog] Guardado id=X ref=Y insp=Z score=...
```
Permite comprobar si se guardan defectos y si `inspection_id` llega correctamente.

---

## 2. Posibles causas de "inspección 43 no encuentra errores"

| Causa | Cómo comprobarlo |
|-------|------------------|
| **No se detectan defectos** | `InspectMetrics` en logs: si todos los scores > 50, no hay `is_defect=True` |
| **Umbral demasiado alto** | Subir sensibilidad (slider hacia la derecha) o bajar `PATCHCORE_THRESHOLD_MARGIN` |
| **Velocidad de línea** | Aumentar `CAMERA_FPS` (ej. 10–15) |
| **`inspection_id` no llega** | Buscar en logs `[DefectLog] Guardado id=... insp=None` |
| **Defectos fuera del rango** | Si `inspection_id=None`, el informe usa `started_at`–`stopped_at` de la inspección |

### 2.3 BUG: Extractor bloqueaba PatchCore (2026-03-01)

**Problema:** En `_sync_process_frame`, `extractor.extract(img)` se ejecutaba **antes** de PatchCore. Si el extractor fallaba (ej. filtro de calidad: brightness < 0.2, blur, etc.), se devolvía `is_defect=False` **sin ejecutar PatchCore**. Defectos intencionales en telas oscuras o con características que disparan el filtro nunca se detectaban.

**Solución:** Para PatchCore, ejecutar `detector.predict(image=img)` **primero**. El extractor solo se usa para reconocimiento cuando `is_anomaly`; si falla, se mantiene `is_defect=True` con `recognition=None`.

---

### 2.4 Comando para revisar logs tras inspección

```bash
docker logs nuvant-backend 2>&1 | grep -E "InspectMetrics|DefectLog|Inspection|is_defect"
```

### 2.2 Qué buscar

- **Defectos guardados:** líneas `[DefectLog] Guardado id=...`
- **Sin defectos guardados:** no aparecen esas líneas → el motor no detecta o el debounce no confirma
- **`insp=None`:** el bridge no está enviando `inspection_id` en el `frame_meta`

---

## 3. Cola de clasificación

- **Por clasificar:** `GET /references/{ref_id}/unclassified_defects` → defectos con `tipo=NULL` o `tipo=Sin clasificar`
- **Clasificados:** `GET /references/{ref_id}/classified_defects` → defectos con otro tipo

Si no aparecen clasificados en la cola, es normal: la pestaña "Clasificados" los muestra. El informe incluye ambos.

---

## 4. Rebuild necesario

Sí, hay cambios en Python:
```bash
docker compose build nuvant-backend
docker compose up -d --force-recreate nuvant-backend
```
