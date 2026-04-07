# Changelog — Estado Actual del Sistema

**Última actualización:** 2026-03-18

---

## Versión vigente: PatchCore V32.5

### Motor de detección

- **Re-weighting alineado al paper**: `_compute_distances` usa `(1-w)·d` (Eq. 3 del paper, arXiv:2106.08265) en lugar de la fórmula anterior `(2-w)·d`. Suprime scores de patches normales con match confiable, reduce falsos positivos.
- **Agregación por percentil**: `np.percentile(score_map, 99)` reemplaza `np.max`. Robusto contra patches ruidosos aislados.
- **Suavizado espacial**: GaussianBlur(3x3, σ=1.0) sobre el distance_map antes de calcular score. Preserva clusters de defecto, promedia ruido.
- **Denoising de entrada**: GaussianBlur(3x3, σ=0.7) antes de CLAHE. Reduce ruido de sensor/JPEG sin degradar texturas.
- **Calibración consistente**: `train()` aplica idéntico pipeline (smoothing + percentil) que `predict()`.
- **Margen configurable**: `PATCHCORE_THRESHOLD_MARGIN` default 3.0 en `save()`, configurable vía env.

### Lag prevention

- **`INSPECT_LAG_SKIP_SEC=0.3`**: descarta frames con más de 300ms de antigüedad durante INSPECT. Elimina lag acumulado cuando la inferencia (~220ms) no alcanza los 15 FPS de captura. La cámara sigue a 15 FPS (necesario para TRAIN), pero el backend siempre procesa frames frescos.

### Inspección y defectos

- **Inspección por sesión**: cada Iniciar/Detener crea un registro `Inspection`. Defectos asociados por `inspection_id`.
- **Debounce de entrada**: `INSPECT_DEBOUNCE_FRAMES=1` (confirma en primer frame anómalo).
- **Debounce de salida**: `_defect_active_flag` previene re-guardar el mismo defecto en oscilación. Se resetea tras N frames OK consecutivos.
- **Reconocimiento automático**: defectos con similitud >95% con clasificados previos se guardan con tipo automáticamente.
- **Cola de clasificación**: filtrable por inspección.

### Informes

- **Por inspección** (`.../inspections/{id}/report`): **excluye** generación si queda "Sin clasificar" (HTTP 409). Contenido HTML solo clasificados.
- **Por referencia** (`/references/{id}/report`): puede generar con pendientes y muestra **aviso** en el HTML (uso no estándar; la UI usa el flujo por inspección).
- El botón de informe se **deshabilita** si hay pendientes en la inspección seleccionada.
- HTML con imágenes embebidas (base64), clasificaciones, timestamps en hora local.
- Tras generar, se borran las imágenes de defectos de esa inspección.

### WebSocket y bridge

- **Desconexión del bridge**: se llama `_close_inspection` por `(line_id, point_id)`, se cancela auto-resume y se hace `broadcast` `mode_changed` → `PAUSE` con `reason: bridge_disconnected` (la UI no queda en estado de inspección fantasma).
- `connectWs()` en frontend: handlers `onclose`/`onerror` a null antes de cerrar sockets viejos (evita bucles de reconexión).
- Broadcast con timeout para no bloquear por clientes lentos.
- Inferencia en `ThreadPoolExecutor` (no bloquea el event loop).

### Entrenamiento (captura + UI)

- Reset explícito de `train_buffer` al iniciar `TRAIN` vía REST (`set_bridge_mode`) y señal `_train_session_reset` para convivir con `frame_meta` del bridge.
- Evita segundo reset del buffer por `TRAIN` obsoleto tras auto-pause al límite (`train_limit_notified`).
- `set_mode` desde bridge usa `target_lid` / `target_pid` antes de vaciar el buffer (no mezcla línea/punto).
- Al abrir `WS live`, si ya hay frames en buffer se envía `train_progress` (sincroniza contador tras refresh).
- `trainFromCamera`: manejo de éxito por HTTP + `trainCompleteHandled` para no duplicar alertas con WS; botones de cámara deshabilitados durante entrenamiento.

### Frontend

- Badges: "NUEVO DEFECTO REGISTRADO" (rojo) vs "DEFECTO EN SEGUIMIENTO" (ámbar).
- Guard contra frames `INSPECT` tardíos tras detener inspección.
- `train_capture_complete` no duplica alerta si ya se notificó por `train_progress` al límite.
- Tras clasificar en cola, `checkUnclassified()` refresca el botón Informe.
- `window.focus` para refrescar estado del informe al volver de `classify.html`.

---

## Correcciones aplicadas (resumen acumulado)

| Área | Corrección |
|------|------------|
| Re-weighting | Alineado al paper (Eq. 3): `(1-w)·d` en vez de `(2-w)·d` |
| Score aggregation | Percentil 99 en vez de max |
| Spatial smoothing | GaussianBlur en distance_map para scoring |
| Input denoising | GaussianBlur σ=0.7 antes de CLAHE |
| Lag skip | Frames >0.3s descartados en INSPECT |
| Defect tracking | `defect_log_id` broadcast para UX de seguimiento |
| Report filter | Excluye "Sin clasificar" del informe |
| Report button | Bloqueado si hay pendientes |
| WS reconnect | Sin loop de reconexión |
| Train buffer | Reset al iniciar TRAIN (REST + bridge); sin wipe por meta obsoleta |
| Bridge off | Cierra inspección + PAUSE al frontend |
| Modelo no carga | `broadcast` error a UI (no drop silencioso) |
| Inference thread | `run_in_executor` para no bloquear event loop |
| DB sessions | Localizadas por frame, sin lock de SQLite |

---

## Rebuild

```bash
docker compose build --no-cache nuvant-backend && docker compose up -d
```

**Reentrenar** referencias activas solo si cambian parámetros de entrenamiento / modelo persistido (ver `GUIA_AJUSTES_PRODUCCION.md`, columna «Requiere reentrenar»). Cambios solo de inspección o margen de umbral en env no obligan a reentrenar.
