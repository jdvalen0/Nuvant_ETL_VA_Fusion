# Captura de logs durante pruebas

Guía para capturar y guardar los logs del sistema mientras realizas pruebas.

---

## 1. Ver logs en tiempo real

### Todos los servicios
```bash
cd ~/Escritorio/Nuvant_ETL_VA_Fusion
docker compose logs -f
```
Muestra backend + bridge mezclados. Ctrl+C para salir.

### Solo backend
```bash
docker compose logs -f nuvant-backend
```
Incluye: inferencia, PLC, entrenamiento, errores de API.

### Solo bridge (cámara)
```bash
docker compose logs -f bridge-l1-final
```
Incluye: conexión cámara, Force IP, frames enviados, errores de captura.

---

## 2. Guardar logs para análisis posterior

### Script automático (recomendado)
```bash
cd ~/Escritorio/Nuvant_ETL_VA_Fusion
./save_test_logs.sh
```

**Salida:**
- `logs_pruebas/YYYY-MM-DD_HH-MM-SS.log` — todos los servicios
- `logs_pruebas/YYYY-MM-DD_HH-MM-SS_nuvant-backend.log` — solo backend
- `logs_pruebas/YYYY-MM-DD_HH-MM-SS_bridge-linea1-final.log` — solo bridge

**Con sufijo** (para identificar la prueba):
```bash
./save_test_logs.sh prueba_plc
./save_test_logs.sh inspeccion_lote_001
./save_test_logs.sh error_conexion_camara
```
Genera: `logs_pruebas/2026-03-01_14-30-00_prueba_plc.log`, etc.

---

## 3. Cuándo capturar logs

| Momento | Comando | Motivo |
|---------|---------|--------|
| Antes de iniciar prueba | `./save_test_logs.sh pre_prueba` | Estado limpio |
| Durante error | `./save_test_logs.sh error_<desc>` | Capturar traza del fallo |
| Al finalizar prueba | `./save_test_logs.sh post_prueba` | Log completo de la sesión |
| Tras cambiar IP cámara | `./save_test_logs.sh post_cambio_ip` | Verificar conexión |

---

## 4. Logs por número de líneas

```bash
# Últimas 100 líneas del backend
docker compose logs --tail=100 nuvant-backend

# Últimas 200 líneas del bridge
docker compose logs --tail=200 bridge-l1-final

# Guardar últimas 500 líneas
docker compose logs --tail=500 --no-color > logs_pruebas/ultimos_500.log
```

---

## 5. Ubicación de archivos

| Contenido | Ruta |
|-----------|------|
| Logs guardados por script | `logs_pruebas/` |
| Logs internos del backend | `Nuvant_VA/backend/logs/` |

`logs_pruebas/` está en `.gitignore`; no se sube al repositorio.

---

## 6. Errores frecuentes y qué buscar en logs

| Síntoma | Servicio | Buscar en logs |
|---------|----------|----------------|
| No hay video en calibración | bridge | "Conectado a:", "Cámara con IP ... no encontrada" |
| Error PLC | backend | `[PLC] Conexión fallida`, `[PLC] Error escribiendo` |
| Inspección no detecta | backend | `[InspectMetrics]`, `score`, `is_defect` |
| Bridge desconectado | backend | `mode_changed` / `bridge_disconnected`, cierre de WS cámara; al enviar comando sin bridge: `No hay conexión para L1P1` |
| Cámara no encontrada | bridge | "Cámaras detectadas:", "No se encontraron cámaras" |
