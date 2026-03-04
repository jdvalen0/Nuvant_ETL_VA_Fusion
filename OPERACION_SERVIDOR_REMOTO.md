# Operación de Servidor Remoto (Producción)

Procedimiento operativo actualizado para despliegue, validación y recuperación.

## 1) Preparación del host

### 1.1 Evitar suspensión

```bash
sudo systemctl mask sleep.target suspend.target hibernate.target hybrid-sleep.target
```

### 1.2 Verificar red/IP

```bash
ip -4 addr show
```

## 2) Despliegue estándar

Desde la raíz del repositorio:

```bash
chmod +x init_deploy.sh
./init_deploy.sh
docker compose up -d --build
```

Servicios esperados:
- `nuvant-backend` (`healthy`)
- `bridge-l1-final` (`up`)

Validación:

```bash
docker compose ps
curl -s http://localhost:8000/api/inference/bridge/status
docker compose logs --tail=100 nuvant-backend
docker compose logs --tail=100 bridge-l1-final
```

## 3) Arranque/parada operativa

Parada:

```bash
docker compose down
```

Arranque:

```bash
docker compose up -d
```

Los datos en `db`, `local_storage` y `logs` se conservan por volúmenes bind.

## 4) Captura de logs de pruebas

```bash
./save_test_logs.sh
./save_test_logs.sh <sufijo>
```

Salida en `logs_pruebas/`:
- `...log` (completo)
- `..._nuvant-backend.log`
- `..._bridge-linea1-final.log`

## 5) Acceso remoto

```bash
curl http://<IP_SERVIDOR>:8000/
curl http://<IP_SERVIDOR>:8000/static/
```

UI:
- `http://<IP_SERVIDOR>:8000/static/`

## 6) Flujo operativo recomendado

1. Crear o seleccionar referencia.
2. `CALIBRATE` para validar imagen en vivo.
3. `TRAIN` para capturar frames de tela normal.
4. `Entrenar Modelo` (`train_from_camera`).
5. `INSPECT` para producción.
6. `PAUSE` para detención controlada.

## 7) Recuperación de fallos

### 7.1 Error de build/cache Docker

```bash
docker builder prune -af
docker buildx prune -af
sudo systemctl restart docker
docker compose build --no-cache nuvant-backend bridge-l1-final
docker compose up -d nuvant-backend bridge-l1-final
```

### 7.2 No hay video en calibración

1. Verificar conexión bridge-backend:

```bash
curl -s http://localhost:8000/api/inference/bridge/status
```

Si `count` es `0`, backend no tiene bridge activo.

2. Ver logs bridge:

```bash
docker compose logs --tail=120 bridge-l1-final
```

Casos comunes:
- `No se encontraron cámaras` / `ERROR conectando cámara`: problema físico/red GigE o cámara no accesible.
- reinicio en bucle del contenedor: falla en apertura de cámara o configuración inválida.

3. Reiniciar bridge:

```bash
docker compose restart bridge-l1-final
```

4. Revalidar:
- `bridge/status` con `count >= 1`
- en logs bridge: `WebSocket conectado al backend VA` y frames enviados en `CALIBRATE`.

### 7.3 Modo simulación (sin cámara física)

Editar `docker-compose.yml` en servicio `bridge-l1-final`:

```yaml
CAMERA_MODE: "simulate"
```

Recrear bridge:

```bash
docker compose up -d --force-recreate bridge-l1-final
```

## 8) Seguridad operativa mínima

- Restringir acceso de red al puerto `8000`.
- Respaldar periódicamente:
  - `Nuvant_VA/backend/db/`
  - `Nuvant_VA/backend/local_storage/`
