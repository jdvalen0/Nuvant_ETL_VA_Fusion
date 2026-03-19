# Nuvant Vision System — Instrucciones Operativas

## 1. Docker — Comandos

**Directorio base:**
```bash
cd ~/Escritorio/Nuvant_ETL_VA_Fusion
```

| Acción | Comando |
|--------|---------|
| Detener | `docker compose down` |
| Iniciar | `docker compose up -d` |
| Estado | `docker compose ps` |
| Logs tiempo real | `docker compose logs -f` |
| Logs backend | `docker compose logs -f nuvant-backend` |
| Logs bridge | `docker compose logs -f bridge-l1-final` |
| Rebuild (tras cambios de código) | `docker compose build --no-cache nuvant-backend && docker compose up -d` |
| Guardar logs pruebas | `./save_test_logs.sh [sufijo]` |

### Secuencia tras modificar código

```bash
docker compose down
docker compose build --no-cache nuvant-backend
docker compose up -d
docker compose ps
```

**Importante**: si los cambios afectan el pipeline de detección (anomaly_patchcore.py, preprocesamiento, scoring), es **obligatorio reentrenar** cada referencia activa después del rebuild.

### ¿Cuándo rebuild vs restart?

| Cambio | Acción |
|--------|--------|
| Código Python/JS/HTML | Rebuild + up |
| `.env` (PLC_IP, CAMERA_IP) | Solo restart |
| `docker-compose.yml` (env vars) | Solo restart |
| Variables que afectan pipeline (CORESET_RATIO, CLAHE, etc.) | Restart + reentrenar |

**Acceso:** `http://<IP_SERVIDOR>:8000/static/`

---

## 2. Flujo operativo completo

### Fase 1: Configuración (una vez por referencia)

1. **Crear referencia**: nombre descriptivo (ej. "Mezclilla-Lote-001") → Crear.
2. **Calibrar cámara**: seleccionar referencia → Calibrar Cámara. Verificar foco, encuadre, iluminación.
3. **Capturar entrenamiento**: Iniciar Captura Entrenamiento (captura hasta `capture_limit` frames).
4. **Entrenar modelo**: Entrenar Modelo (esperar confirmación).

### Fase 2: Inspección

5. **Configurar pausa**: Pausa defecto (s) = 0 para inspección continua, >0 para pausa ante defecto no reconocido.
6. **Iniciar inspección**: Iniciar Inspección.
7. **Durante inspección**:
   - Defectos reconocidos (similitud >95% con clasificados previos): se guardan con tipo automáticamente.
   - Defectos no reconocidos: se guardan como "Sin clasificar" → cola de clasificación.
   - Badge rojo: "NUEVO DEFECTO REGISTRADO #N" (primera detección).
   - Badge ámbar: "DEFECTO #N EN SEGUIMIENTO" (mismo evento activo).
8. **Detener inspección**: Detener cuando termine el lote.

### Fase 3: Clasificación

9. **Abrir cola**: seleccionar inspección en el desplegable → Cola clasificación.
10. **Clasificar**: para cada defecto "Sin clasificar", elegir tipo → Clasificar.
11. **Cerrar** cuando aparezca "✓ Todos los defectos clasificados".

### Fase 4: Informe

12. **Verificar**: el botón Informe se habilita solo cuando todos los defectos de la inspección están clasificados.
13. **Generar**: seleccionar inspección → Informe.
14. **Resultado**: HTML con imágenes embebidas, solo defectos clasificados (reconocidos + manuales). Excluye "Sin clasificar".
15. **Post-informe**: las imágenes de defectos de esa inspección se borran automáticamente.

---

## 3. Señal PLC S7 (Siemens)

### Configuración

Crear archivo `.env` en la raíz del proyecto:
```
PLC_IP=192.168.1.10
PLC_DB=1
PLC_BYTE=0
PLC_BIT=0
PLC_RACK=0
PLC_SLOT=1
```

### Activación

```bash
docker compose down
docker compose up -d
docker compose exec nuvant-backend env | grep PLC
```

### Comportamiento

- Escribe un bit por cada frame durante INSPECT: 1 = defecto, 0 = normal.
- Solo escribe si el valor cambió respecto al frame anterior.
- Si `PLC_IP` no está definido → PLC deshabilitado.

### Verificación

- Logs: `docker compose logs -f nuvant-backend | grep PLC`
- En el PLC: verificar bit `DB{N}.DBX{B}.{b}` cambia durante inspección.

---

## 4. Cámara GigE Vision

### Estado actual

Con `CAMERA_IP` vacío, el bridge toma el primer dispositivo GigE encontrado.

### Cambiar IP de cámara

Editar `.env`:
```
CAMERA_IP=192.168.1.50
CAMERA_FORCE_IP=192.168.1.50
```

Reiniciar: `docker compose down && docker compose up -d`

### FPS y velocidad del rollo

- `CAMERA_FPS=15` (default): captura 15 frames/seg.
- La inferencia procesa ~4.5 FPS (limitada por CPU, ~220ms/frame).
- `INSPECT_LAG_SKIP_SEC=0.3` descarta frames obsoletos → siempre procesa frames frescos.
- **Cobertura**: `V_max = FOV × FPS_efectivo`. Con FOV de 20cm y 4.5 FPS: V_max ≈ 0.9 m/s.

---

## 5. Ubicación de archivos

| Contenido | Ruta en host |
|-----------|-------------|
| Base de datos | `Nuvant_VA/backend/db/nuvant.db` |
| Modelos | `Nuvant_VA/backend/local_storage/line_N/point_M/{ref_id}/model.pkl` |
| Imágenes defectos | `Nuvant_VA/backend/local_storage/line_N/point_M/{ref_id}/defects/` |
| Reportes | `Nuvant_VA/backend/local_storage/reports/` |
| Logs guardados | `logs_pruebas/` |

---

## 6. Errores frecuentes

| Síntoma | Causa probable | Acción |
|---------|---------------|--------|
| UI dice "Desconectado" | Backend no arrancó o bridge no conectado | `docker compose ps`, verificar logs |
| "Inspección Detenida" tras iniciar | WebSocket reconexión o inspección no creada | Verificar logs backend, re-intentar |
| Score oscila en imagen estática | Normal: ruido sensor amplificado. No afecta detección real | Debounce de salida previene duplicados |
| Botón Informe deshabilitado | Hay defectos sin clasificar | Abrir Cola clasificación y clasificar todos |
| "Solo N frames. Necesita ≥5" | Buffer de entrenamiento no se llenó | Verificar que la cámara envía frames (logs bridge) |
| Timeout captura / RetrieveBuffer | Cámara no entrega frames | Verificar red GigE, subred, Force IP |
| Build error "parent snapshot" | Cache Docker corrupto | `docker builder prune -f` y re-build |
