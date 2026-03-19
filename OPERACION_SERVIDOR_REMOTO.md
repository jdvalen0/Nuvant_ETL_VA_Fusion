# Operación de Servidor Remoto

## 1. Preparación del host

### Evitar suspensión
```bash
sudo systemctl mask sleep.target suspend.target hibernate.target hybrid-sleep.target
```

### Verificar red
```bash
ip -4 addr show
```

## 2. Despliegue

```bash
cd ~/Escritorio/Nuvant_ETL_VA_Fusion
docker compose up -d --build
```

Si se usa PLC: crear `.env` con `PLC_IP` antes del `up` (ver `INSTRUCCIONES_OPERATIVAS.md`).

Servicios esperados:
- `nuvant-backend` (healthy)
- `bridge-l1-final` (up)

### Validación
```bash
docker compose ps
curl -s http://localhost:8000/api/inference/bridge/status
docker compose logs --tail=50 nuvant-backend
docker compose logs --tail=50 bridge-l1-final
```

## 3. Arranque/parada

```bash
docker compose down       # parar
docker compose up -d      # arrancar
```

Los datos en `db/`, `local_storage/` y `logs/` se conservan por volúmenes bind.

## 4. Acceso remoto

```
http://<IP_SERVIDOR>:8000/static/
```

## 5. Flujo operativo

1. Crear/seleccionar referencia.
2. CALIBRATE → verificar imagen.
3. TRAIN → capturar frames normales.
4. Entrenar Modelo.
5. INSPECT → producción.
6. Detener → cerrar inspección.
7. Cola clasificación → clasificar pendientes.
8. Informe → generar y descargar.

## 6. Recuperación de fallos

### Build/cache Docker corrupto
```bash
docker builder prune -af
docker compose build --no-cache nuvant-backend bridge-l1-final
docker compose up -d
```

### Sin video en calibración
```bash
curl -s http://localhost:8000/api/inference/bridge/status   # count debe ser ≥1
docker compose logs --tail=50 bridge-l1-final               # buscar errores de cámara
docker compose restart bridge-l1-final                      # reiniciar bridge
```

### Modo simulación (sin cámara física)
En `docker-compose.yml`, cambiar `CAMERA_MODE: "simulate"` en el bridge y recrear:
```bash
docker compose up -d --force-recreate bridge-l1-final
```

## 7. Seguridad

- Restringir acceso de red al puerto 8000.
- Respaldar periódicamente `Nuvant_VA/backend/db/` y `Nuvant_VA/backend/local_storage/`.
