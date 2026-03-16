# Nuvant Vision System — Instrucciones Operativas

## 1. Docker — Comandos operativos

**Directorio base:**
```bash
cd ~/Escritorio/Nuvant_ETL_VA_Fusion
```

| Acción | Comando |
|--------|---------|
| **Detener** (tumbar contenedores) | `docker compose down` |
| **Iniciar** (levantar) | `docker compose up -d` |
| **Ver estado** | `docker compose ps` |
| **Ver logs** | `docker compose logs -f` |
| **Guardar logs de pruebas** | `./save_test_logs.sh [sufijo]` — ver `CAPTURA_LOGS_PRUEBAS.md` |
| **Reconstruir** (tras cambios de código) | `docker compose build --no-cache nuvant-backend` |
| **Reconstruir y levantar** | `docker compose build --no-cache nuvant-backend && docker compose up -d` |

### Secuencia tras modificar código

```bash
cd ~/Escritorio/Nuvant_ETL_VA_Fusion
docker compose down
docker compose build --no-cache nuvant-backend
docker compose up -d
docker compose ps
```

### Solo reiniciar (sin reconstruir)

```bash
docker compose down
docker compose up -d
```

### ¿Cuándo reconstruir vs solo reiniciar?

| Cambio | Acción |
|--------|--------|
| **Código** (Python, JS, HTML, Dockerfile) | `docker compose build --no-cache nuvant-backend` (o bridge si cambiaste camera_bridge) + `docker compose up -d` |
| **`.env`** (PLC_IP, CAMERA_IP, etc.) | Solo `docker compose down` + `docker compose up -d` |
| **`docker-compose.yml`** (env, volúmenes) | Solo reiniciar |

**Acceso:** `http://<IP_SERVIDOR>:8000/` (ej. `http://169.254.75.169:8000/`)

---

## 2. Flujo operativo completo

### Fase 1: Configuración inicial (una vez por referencia)

1. **Crear referencia**  
   - Nombre (ej. "Mezclilla-Lote-001") → Crear.

2. **Calibrar cámara**  
   - Seleccionar referencia → **Calibrar Cámara**.

3. **Capturar entrenamiento**  
   - **Iniciar Captura Entrenamiento** (captura ~200 frames).

4. **Entrenar modelo**  
   - **Entrenar Modelo** (esperar a que termine).

---

### Fase 2: Inspección

5. **Configurar pausa por defecto**
   - **Pausa defecto (s):**
     - `0` = no pausar, solo guardar (inspección continua).
     - `> 0` (ej. 10) = pausar X segundos cuando hay defecto no reconocido.

6. **Iniciar inspección**  
   - **Iniciar Inspección**.

7. **Durante la inspección**
   - Defectos reconocidos (similitud > 95% con defectos ya clasificados): se guardan con tipo y van al informe.
   - Defectos no reconocidos: se guardan como "Sin clasificar" y pasan a la cola.
   - Si pausa > 0: se pausa en defectos no reconocidos.
   - Si pausa = 0: inspección continua.

8. **Detener inspección**  
   - **Detener** cuando termine el lote.

---

### Fase 3: Clasificación (obligatoria antes del informe)

9. **Abrir cola de clasificación**  
   - Seleccionar **inspección** en el desplegable.
   - **Cola clasificación** (abre pestaña filtrada por esa inspección).
   - Si no selecciona inspección antes, la cola muestra todos los defectos sin clasificar de la referencia.

10. **Clasificar defectos no reconocidos**
    - Los defectos que el sistema reconoce (similitud > 95% con defectos ya clasificados) se guardan con tipo y van directo al informe.
    - Los no reconocidos aparecen en la cola como "Sin clasificar".
    - Para cada uno: elegir tipo → **Clasificar**.
    - Repetir hasta que la cola de esa inspección esté vacía.

11. **Cerrar la pestaña** cuando aparezca:  
    "✓ Todos los defectos clasificados".

---

### Fase 4: Informe

12. **Generar informe**
    - En la pantalla principal: seleccionar **inspección** en el desplegable (junto al botón Informe).
    - Si hay defectos sin clasificar en esa inspección, el botón Informe se deshabilita y muestra "⚠ N sin clasificar".
    - Clasificar todos en la cola antes de poder generar.
    - Pulsar **Informe**.

13. **Resultado**
    - Se descarga un HTML con imágenes embebidas, clasificaciones y timestamps en hora local.
    - Solo incluye defectos de **esa inspección** (reconocidos + clasificados manualmente).
    - Tras generar, se borran las imágenes de defectos de esa inspección.
    - El informe se guarda en `Nuvant_VA/backend/local_storage/reports/`.

**Nota:** El desplegable de inspecciones se actualiza al cambiar de referencia y al detener una inspección. Si no aparece ninguna inspección, asegúrese de haber pulsado **Detener** tras una sesión de inspección.

---

## 3. Señal PLC S7 (Siemens)

### Técnica utilizada
Comunicación directa con PLC Siemens S7 mediante **snap7** (protocolo S7). El backend escribe un único bit en un Data Block del PLC. No se usa OPC-UA ni otros middleware.

### Qué es
Un **bit** en el PLC que indica si hay defecto detectado en el frame actual:
- **1 (True)** = defecto detectado
- **0 (False)** = sin defecto

### Dónde se escribe
`DB{PLC_DB}.DBX{PLC_BYTE}.{PLC_BIT}` — p. ej. DB1.DBX0.0

### Cuándo se envía
- Durante **inspección** (modo INSPECT), por cada frame procesado.
- Solo se escribe si el valor cambió respecto al frame anterior (evita escrituras innecesarias).
- Si `PLC_IP` no está definido → no se intenta conexión (sistema funciona sin PLC).

### Variables de entorno (opcionales)

| Variable | Default | Descripción |
|----------|---------|-------------|
| `PLC_IP` | — | IP del PLC (si no se define, PLC deshabilitado) |
| `PLC_DB` | 1 | Número de Data Block |
| `PLC_BYTE` | 0 | Offset del byte |
| `PLC_BIT` | 0 | Bit dentro del byte (0–7) |
| `PLC_RACK` | 0 | Rack S7 |
| `PLC_SLOT` | 1 | Slot S7 |

### Por qué usar `.env`

- **Docker Compose** lee el archivo `.env` en la raíz del proyecto y sustituye `${PLC_IP}`, `${PLC_DB}`, etc. en el `docker-compose.yml`.
- El backend necesita esas variables **dentro del contenedor** para conectar al PLC; Docker las inyecta como variables de entorno.
- Si no creas `.env`, `PLC_IP` queda vacío y el PLC queda deshabilitado (el sistema funciona igual, pero sin señal).
- **Ventaja**: la IP del PLC no va en el `docker-compose.yml` (que suele estar en git). Cada instalación usa su propio `.env` con la IP de su PLC. El archivo `.env` suele estar en `.gitignore`, así que no se sube al repositorio.

---

### Paso a paso: activar y probar la señal PLC

#### Paso 1 — Ir al directorio del proyecto

```bash
cd ~/Escritorio/Nuvant_ETL_VA_Fusion
```

**Salida esperada:** Ninguna (solo cambia el directorio actual).

**Motivo:** Todos los comandos siguientes deben ejecutarse desde la raíz del proyecto, donde está `docker-compose.yml` y donde se creará `.env`.

---

#### Paso 2 — Crear o editar el archivo `.env`

Si no existe, créalo. Si ya existe (p. ej. con cámara), añade las variables PLC. Ejemplo mínimo para PLC:
```
PLC_IP=192.168.1.10
PLC_DB=1
PLC_BYTE=0
PLC_BIT=0
PLC_RACK=0
PLC_SLOT=1
```
Sustituye `192.168.1.10` por la IP real del PLC. La cámara usa `CAMERA_IP` y `CAMERA_FORCE_IP` (ver sección 5).

**Verificar que se creó:**
```bash
cat .env
```
**Salida esperada:**
```
PLC_IP=192.168.1.10
PLC_DB=1
...
```

---

#### Paso 3 — Detener los contenedores

```bash
docker compose down
```

**Salida esperada:**
```
[+] Running 2/2
 ✔ Container bridge-linea1-final  Removed
 ✔ Container nuvant-backend       Removed
 ✔ Network nuvant_etl_va_fusion_nuvant-net  Removed
```

**Motivo:** Hay que reiniciar para que Docker Compose lea `.env` y pase las variables al contenedor. Los contenedores actuales no tienen `PLC_IP` cargada.

---

#### Paso 4 — Levantar los contenedores

```bash
docker compose up -d
```

**Salida esperada:**
```
[+] Running 3/3
 ✔ Network nuvant_etl_va_fusion_nuvant-net  Created
 ✔ Container nuvant-backend       Started
 ✔ Container bridge-linea1-final Started
```

**Motivo:** Crea los contenedores con las variables de `.env` inyectadas. El backend ya tiene acceso a `PLC_IP`.

---

#### Paso 5 — Comprobar que las variables llegaron al contenedor

```bash
docker compose exec nuvant-backend env | grep PLC
```

**Salida esperada (si `.env` está bien):**
```
PLC_IP=192.168.1.10
PLC_DB=1
PLC_BYTE=0
PLC_BIT=0
PLC_RACK=0
PLC_SLOT=1
```

**Motivo:** Confirma que el contenedor tiene las variables. Si no aparece `PLC_IP` o está vacía, el PLC no se activará.

---

#### Paso 6 — Iniciar inspección y observar logs

En una terminal, seguir los logs:
```bash
docker compose logs -f nuvant-backend
```

En el navegador: seleccionar referencia entrenada → **Iniciar Inspección**.

**Salida esperada en logs:**
- Sin PLC o sin conexión: `[PLC] Conexión fallida: ...` o `[PLC] Error escribiendo: ...`
- Con PLC conectado: no suele haber mensajes de éxito (solo errores). La señal se escribe en silencio.

**Motivo:** La señal se envía en cada frame durante la inspección. Si hay defecto → bit 1; si no → bit 0. Los errores de conexión se ven aquí.

---

#### Paso 7 — Verificar en el PLC

En el PLC (o PLCSIM), revisar el bit configurado:
- Por defecto: `DB1.DBX0.0`
- Debe cambiar entre 0 y 1 según haya defecto o no en el frame actual.

**Motivo:** Es la comprobación final de que la señal llega correctamente al PLC.

---

## 4. Ubicación de archivos

| Contenido | Ruta en el host |
|-----------|------------------|
| Imágenes de defectos | `Nuvant_VA/backend/local_storage/line_1/point_1/{ref_id}/defects/` |
| Informes generados | `Nuvant_VA/backend/local_storage/reports/` |
| Base de datos | `Nuvant_VA/backend/db/nuvant.db` |

---

## 5. Cámara GigE — IP actual y cambio futuro

### Estado actual (por defecto)
Con `CAMERA_IP` vacío o no definido, el bridge toma el **primer dispositivo** encontrado. Es el comportamiento que funcionaba antes. No definir `CAMERA_IP` en `.env` salvo que necesites filtrar por IP concreta.

### A futuro: cambiar IP de la cámara
Si cambias la IP de la cámara (por hardware, software o red):

1. **Editar `.env`** y definir:
```
CAMERA_IP=192.168.1.50
CAMERA_FORCE_IP=192.168.1.50
```
   Sustituir por la IP real. El bridge filtra por `GevDeviceIPAddress` (IP del dispositivo) o por `display_name`. `CAMERA_FORCE_IP` asigna esa IP a la cámara al conectar (si hay varias cámaras, usa la que coincida).

2. **Una sola cámara:** Si solo hay una, puedes dejar `CAMERA_IP` vacío y solo definir `CAMERA_FORCE_IP` para configurar la IP al conectar.

3. **Reiniciar contenedores**:
```bash
docker compose down
docker compose up -d
```

4. **Verificar**:
```bash
docker compose logs -f bridge-l1-final
```
   Debe mostrar "Conectado a: ..." con la cámara.

### Velocidad de captura (FPS) — defectos que pasan por velocidad

A mayor velocidad de línea, el defecto cruza el campo de visión más rápido. Si capturas a 5 FPS (200 ms entre frames), un defecto que pasa en 150 ms puede no aparecer en ningún frame.

**Solución:** Aumentar `CAMERA_FPS` para capturar más frames por segundo.

| Variable | Default | Efecto |
|----------|---------|--------|
| `CAMERA_FPS` | 10.0 | Frames/seg. 10 = 100 ms entre frames; 20 = 50 ms. |

**Dónde cambiar:** En `.env`:
```
CAMERA_FPS=15
```
O en `docker-compose.yml` (bridge-l1-final, environment).

**Límite:** El backend procesa ~5–10 frames/seg (PatchCore). Si `CAMERA_FPS` > capacidad de inferencia, se acumulan frames. Probar 10 primero; subir a 15–20 si la cámara y la red GigE aguantan.

**Reiniciar:** `docker compose down` + `docker compose up -d` (no requiere rebuild).

---

## 6. Errores frecuentes

| Mensaje | Acción |
|---------|--------|
| "Seleccione una inspección para generar el informe" | Elegir una inspección en el desplegable antes de **Informe**. |
| "Hay N defecto(s) sin clasificar" | Abrir **Cola clasificación** (con inspección seleccionada) y clasificar todos. |
| "Seleccione un tipo de defecto" | Elegir un tipo en el desplegable antes de **Clasificar**. |
| "Error de conexión" | Comprobar que el backend esté en marcha (`docker compose ps`). |
| "Imagen no disponible" | El defecto se guardó sin imagen; se puede clasificar igual. |
| Informe en blanco | Verificar que la inspección tenga defectos detectados; clasificar los pendientes. |
| "Timeout captura" / RetrieveBuffer | La cámara no entrega frames. Verificar: (1) host y cámara en misma subred; (2) si usas Force IP, la interfaz del host debe estar en 169.254.x.x; (3) probar sin Force IP: `CAMERA_FORCE_IP=` en .env. |
