# Auditoría de cambios — Sesión actual (defectos no guardados / informe sin imágenes)

**Fecha:** 2026-03-16  
**Objetivo:** Verificar que los problemas reportados por el usuario están resueltos sin afectar el modelo ni requerir reentrenar.

---

## 1. Problemas reportados por el usuario (resumen del chat anterior)

| # | Síntoma | Causa raíz identificada |
|---|---------|-------------------------|
| 1 | "Detectaba defectos pero no los veía" | El motor SÍ detectaba (`is_defect=True` en logs), pero no se guardaban en DB |
| 2 | "Defectos por clasificar no se guardaban" | Ningún defecto llegaba a la cola porque `_save_defect_on_detect` nunca se ejecutaba |
| 3 | "Informes generaron sin defectos pero tenía defectos por clasificar" | Validación del informe solo revisaba `tipo IS NULL`, ignoraba `tipo=14 (Sin clasificar)` |
| 4 | "Solo una imagen en el informe" | Directorio `defects/` vacío (0 archivos) — mismo origen que #1 y #2 |

---

## 2. Causa raíz unificada: Debounce N=3 incompatible con tela en movimiento

```
Cámara: 5 FPS → 200ms por frame
Debounce N=3 → requiere 3 frames consecutivos = 600ms mínimo de defecto visible

Evidencia en logs (inspección 39):
  Frame N:   is_defect=True  → count=1
  Frame N+1: is_defect=False → count RESET a 0  (tela pasó, defecto transitorio)
  → NUNCA llegó a count=3
  → _save_defect_on_detect() NUNCA ejecutado
  → 0 defectos en DB, 0 imágenes, cola vacía, informe sin contenido real
```

---

## 3. Cambios aplicados y verificación

### 3.1 INSPECT_DEBOUNCE_FRAMES: 3 → 1

| Archivo | Cambio | Estado |
|---------|--------|--------|
| `docker-compose.yml` | `INSPECT_DEBOUNCE_FRAMES=1` | ✅ Verificado L56 |

**Efecto:** Primer frame anómalo guarda inmediatamente. `_defect_active_flag` evita duplicados en la misma ráfaga.

**Reentrenar:** NO. Es variable de entorno en runtime.

---

### 3.2 Validación informe por referencia (tipo "Sin clasificar")

| Archivo | Cambio | Estado |
|---------|--------|--------|
| `references.py` L588-595 | Contar `defect_type_id IS NULL` **o** `defect_type_id == sin_clasificar.id` | ✅ Verificado |

**Antes:** Solo `tipo IS NULL` → defectos con tipo=14 pasaban → informe se generaba sin bloquear.  
**Después:** Bloquea si hay defectos sin clasificar (NULL o tipo 14).

**Reentrenar:** NO.

---

### 3.3 Botón "Guardar" y saveDefect() — evitar entradas fantasma

| Archivo | Cambio | Estado |
|---------|--------|--------|
| `index.html` L1043 | `isConfirmed = data.is_defect && data.debounce_confirmed && data.defect_log_id` | ✅ Verificado |
| `index.html` L1066-1068 | Guardia: si no hay `defect_log_id`, alert y no crear entrada | ✅ Verificado |

**Antes:** Usuario podía clicar "Guardar" antes de confirmación → `/log_defect` creaba entrada con `image_path=""`, `tipo=Otro` → no aparecía en cola "Sin clasificar".  
**Después:** Botón solo habilitado cuando defecto confirmado + guardado. Si intenta guardar sin confirmar, alert explícito.

**Reentrenar:** NO.

---

### 3.4 Fallback informe por inspección (inspection_id=NULL)

| Archivo | Cambio | Estado |
|---------|--------|--------|
| `references.py` L668-682 | Fallback acotado por `timestamp >= started_at` y `<= stopped_at` | ✅ Verificado |

**Antes:** Incluía TODOS los defectos con `inspection_id=NULL` de la ref, mezclando sesiones.  
**Después:** Solo defectos en el rango temporal de esa inspección.

**Reentrenar:** NO.

---

### 3.5 Reset debounce al iniciar nueva inspección

| Archivo | Cambio | Estado |
|---------|--------|--------|
| `inference.py` L944-947 | En `set_bridge_mode(INSPECT)`: `_defect_consec_count[key]=0`, `_defect_active_flag[key]=False` | ✅ Verificado |

**Efecto:** Evita que el estado de la sesión anterior contamine la nueva (ej. count=2 → confirmaría en 1 frame).

**Reentrenar:** NO.

---

### 3.6 Badge UI: "POSIBLE DEFECTO" vs "DEFECTO CONFIRMADO"

| Archivo | Cambio | Estado |
|---------|--------|--------|
| `index.html` L974-989 | `is_defect && debounce_confirmed` → rojo; `is_defect && !debounce_confirmed` → ámbar | ✅ Verificado |

**Reentrenar:** NO.

---

## 4. Flujo verificado (sin reentrenar)

```
[Usuario] Iniciar Inspección (ref=7, modelo ya entrenado)
    → set_bridge_mode(INSPECT)
    → _defect_consec_count[(1,1)] = 0, _defect_active_flag[(1,1)] = False  ← NUEVO
    → Bridge envía frames con inspection_id

[Frame anómalo] PatchCore detecta (score < 50)
    → is_defect=True
    → debounce_n=1 (env) → confirmed=True en el PRIMER frame
    → _save_defect_on_detect() EJECUTADO
    → Guarda JPEG + heatmap PNG en defects/
    → Crea DefectLog con defect_type_id=14 (Sin clasificar), image_path, inspection_id
    → result["defect_log_id"] = id

[Cola de clasificación] GET /references/7/unclassified_defects
    → Filtra tipo=NULL o tipo=14
    → Retorna defectos con has_image, has_heatmap

[Informe] GET /references/7/report
    → Cuenta defectos con tipo=NULL o tipo=14
    → Si sin_clasificar > 0 → HTTP 400 "Debe clasificar TODOS..."
    → Solo genera si todos clasificados
```

---

## 5. Checklist de verificación post-build

Tras `docker compose build nuvant-backend && docker compose up -d --force-recreate nuvant-backend`:

| Verificación | Comando / Acción |
|--------------|------------------|
| INSPECT_DEBOUNCE_FRAMES=1 | `docker exec nuvant-backend sh -c 'echo $INSPECT_DEBOUNCE_FRAMES'` → debe ser `1` |
| Modelo ref=7 intacto | `ls -la Nuvant_VA/backend/local_storage/line_1/point_1/7/model.pkl` → existe |
| Cola unclassified | Iniciar inspección, pasar defecto → revisar `/static/classify.html` con ref=7 |
| Informe bloquea si sin clasificar | Clasificar solo algunos → intentar generar informe → debe dar error 400 |

---

## 6. Resumen ejecutivo

- **Reentrenar:** NO. El modelo (ref=7) permanece en el volumen.
- **Cambios que requieren rebuild:** Código Python/HTML (references.py, inference.py, index.html).
- **Cambios que requieren recreate (no rebuild):** docker-compose.yml (INSPECT_DEBOUNCE_FRAMES).
- **Problemas resueltos:** Debounce N=1 permite guardar defectos transitorios; validación de informe; botón Guardar; fallback de informe por inspección.
