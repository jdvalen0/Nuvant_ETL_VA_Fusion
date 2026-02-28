# Guía Maestra: Configuración de Servidor de Visión (Despliegue Total e IP Fija) 

Esta guía proporciona los pasos exactos para transformar tu equipo Ubuntu en un **Servidor de Inspección Industrial** accesible desde cualquier otro dispositivo de la red local.

---

## FASE 1: Preparación del Hardware (Headless)

El servidor debe estar encendido y procesando 24/7 sin interrumpirse.

### 1. Desactivar Hibernación y Suspensión (Crítico)
Ejecuta este comando para asegurar que el servidor NUNCA se "duerma", incluso si cierras la tapa o dejas de usarlo:
```bash
sudo systemctl mask sleep.target suspend.target hibernate.target hybrid-sleep.target
```

### 2. Configurar IP Fija (Infalible para Conectividad)
Para que siempre puedas entrar desde otro equipo con el mismo número, configuraremos una IP estática en Ubuntu:

1.  Abre **Configuración -> Red** (Network).
2.  Haz clic en el engranaje (⚙️) de tu conexión actual (Cableada o Wi-Fi).
3.  Ve a la pestaña **IPv4**.
4.  Cambia de **Automático (DHCP)** a **Manual**.
5.  **Dirección**: Ingresa `192.168.1.100` (o la que decidas).
6.  **Máscara de red**: `255.255.255.0`
7.  **Puerta de enlace**: `192.168.1.1` (generalmente es la IP de tu router).
8.  Haz clic en **Aplicar**.

---

## FASE 2: Despliegue Total del Sistema (Docker & App)

Ejecuta estos comandos en la terminal desde la carpeta del proyecto para levantar **TODO** el ecosistema:

### 1. Inicializar Estructura y Permisos
Prepara los directorios persistentes y asegura que Git haya bajado las carpetas necesarias:
```bash
chmod +x init_deploy.sh
./init_deploy.sh
```

### 2. Construir y Levantar Contenedores (Despliegue Total)
Este comando descarga las imágenes, construye el software y levanta los servicios en segundo plano (`-d`):
```bash
# Para producción con cámara real (Levanta Backend + Bridge):
CAMERA_MODE=live docker compose up --build -d
```
*Si solo quieres probar con imágenes simuladas, usa:* `docker compose up --build -d`

### 3. Verificar que TODO esté "VIVO":
```bash
# Ver el estado de salud de todos los servicios
docker compose ps
```
*Deberías ver `nuvant-backend` como `Up (healthy)` y `bridge-linea1-final` como `Up`.*

---

## FASE 3: Acceso Remoto (Desde otro equipo)

Ve a tu laptop, tablet u otra PC conectada a la misma red:

1.  Abre un navegador (Chrome o Firefox).
2.  Ingresa la dirección IP fija que configuraste en la Fase 1:
    `http://192.168.1.100:8000/static/index.html`

---

## FASE 4: Blindaje (Seguridad del Know-How)

Una vez que el sistema esté corriendo y verificado:
1.  En el servidor físico, presiona las teclas `Super (Windows) + L`.
2.  La pantalla se bloqueará pidiendo tu contraseña de Administrador.


---
*Vision System V33.7 - Configuración de Alto Nivel para Planta Industrial.*
