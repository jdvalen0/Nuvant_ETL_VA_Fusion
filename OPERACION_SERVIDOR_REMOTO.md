# Operación de Servidor Remoto (Producción)

Guía operativa para desplegar y operar el sistema desde red local.

## 1) Preparación del host

### 1.1 Evitar suspensión
```bash
sudo systemctl mask sleep.target suspend.target hibernate.target hybrid-sleep.target
```

### 1.2 Verificar IP operativa
Ejemplo de IP fija usada en planta:
- `169.254.75.179/24`

Validación:
```bash
ip -4 addr show
```

## 2) Despliegue de servicios

Desde la raíz del repositorio:

```bash
chmod +x init_deploy.sh
./init_deploy.sh
docker compose up -d --build
```

Servicios esperados:
- `nuvant-backend` (`healthy`)
- `bridge-linea1-final` (`up`)

Validación:
```bash
docker compose ps
docker logs --tail=100 nuvant-backend
docker logs --tail=100 bridge-linea1-final
```

## 3) Acceso desde otro equipo

Pruebas de conectividad:
```bash
curl http://<IP_SERVIDOR>:8000/
curl http://<IP_SERVIDOR>:8000/static/
```

UI:
- `http://<IP_SERVIDOR>:8000/static/`

## 4) Flujo operativo recomendado

1. Crear/seleccionar referencia.
2. `CALIBRATE` (comprobar imagen en vivo).
3. `TRAIN` (captura automática hasta límite configurado).
4. `Entrenar Modelo`.
5. `INSPECT`.
6. `PAUSE` para detener inspección.

## 5) Recuperación de fallos frecuentes

### 5.1 Error de build Docker por snapshots/caché
```bash
docker builder prune -af
docker buildx prune -af
sudo systemctl restart docker
docker compose build --no-cache nuvant-backend bridge-l1-final
docker compose up -d nuvant-backend bridge-l1-final
```

### 5.2 Bridge sin cámara
- revisar cableado/alimentación/cámara.
- reiniciar bridge:
```bash
docker compose restart bridge-l1-final
```

### 5.3 Warning de `version` en compose
Ya eliminado del `docker-compose.yml` principal.

## 6) Seguridad operativa mínima

- restringir acceso de red al puerto `8000` en entorno productivo.
- mantener host bloqueado físicamente cuando no esté en operación.
- respaldar periódicamente:
  - `Nuvant_VA/backend/db/`
  - `Nuvant_VA/backend/local_storage/`
