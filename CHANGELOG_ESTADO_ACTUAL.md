# Changelog — Estado actual del sistema

**Última actualización:** 2026-03

---

## Flujo vigente por inspección

1. **Detección:** PatchCore marca anomalía → se guarda con `inspection_id` de la inspección activa.
2. **Reconocimiento:** Si similitud > 95% con defecto ya clasificado → se guarda con ese tipo → va al informe.
3. **Sin reconocer:** Se guarda como "Sin clasificar" → va a la cola para clasificación manual.
4. **Cola:** Filtrable por inspección. Abrir "Cola clasificación" con ref+inspección seleccionados.
5. **Informe:** Solo defectos de esa inspección. Bloqueado si hay defectos sin clasificar.

---

## Correcciones aplicadas (resumen)

| Área | Corrección |
|------|------------|
| `inspection_id` | Se usa `_active_inspection` del backend (no frame_meta del bridge) para evitar NULL. |
| Debounce | `INSPECT_DEBOUNCE_FRAMES=1` — primer frame anómalo guarda. |
| Reconocimiento | `_recognize_defect` solo considera defectos ya clasificados (excluye "Sin clasificar"). |
| Informe | Sin fallback por `inspection_id=NULL`; solo defectos vinculados a la inspección. |
| Cola | `unclassified_defects?inspection_id=X` filtra por inspección. |
| Timestamps | ISO 8601 con Z; conversión a hora local en informe y UI. |
| Extractor | PatchCore se ejecuta antes que el extractor; no bloquea detección. |

---

## Rebuild tras cambios de código

```bash
docker compose build nuvant-backend && docker compose up -d --force-recreate nuvant-backend
```
