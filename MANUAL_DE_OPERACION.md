# Manual de Operación: Nuvant Vision System 🚀

Este manual guía al usuario e ingenieros en el uso diario y despliegue del sistema de inspección de calidad textil.

---

## 1. Guía de Inicio Rápido (Despliegue)

Para desplegar este sistema en un nuevo entorno (ej. Dispositivo IoT en planta):

1.  **Requisitos**: Docker y Docker Compose instalados.
2.  **Clonación**: Copiar la carpeta `Nuvant_ETL_VA_Fusion` al dispositivo.
3.  **Encendido**:
    *   **Modo Simulación (Pruebas)**: `docker compose up -d`
    *   **Modo Real (Producción)**: `CAMERA_MODE=live docker compose up -d`
4.  **Acceso**: Abrir `http://<IP-DEL-IOT>:8000/static/index.html`.

---

## 2. Elementos de la Interfaz Gráfica (GUI)

### Panel de Control de Cámara
Ubicado en la parte superior. Controla el estado del **Bridge**.
- **Iniciar Captura**: Comienza a recibir video de la cámara. Los frames se guardan temporalmente en el servidor para entrenar. La cámara tomará imágenes indefinidamente (alimentando la memoria RAM) mientras este modo esté activo.
- **Entrenar Modelo**: Detiene inmediatamente la captura de imágenes y toma el volumen total de frames acumulados para generar la "huella digital" de la tela. (Recomendado: presionar este botón después de haber capturado entre 30 y 100 imágenes, visible en el contador de la pantalla).
- **Iniciar Inspección**: Activa el motor de IA para buscar defectos en vivo.

### Parámetros de Inteligencia Artificial
Nuvant usa **PatchCore V32**, que califica cada milímetro de la tela.

1.  **Rigor / Contaminación (0.001 - 0.05)**:
    *   Le dice a la IA qué porcentaje de "ruido normal" esperar. 
    *   *Uso*: Aumentar si la tela tiene texturas muy irregulares pero naturales.
2.  **Sensibilidad PCA (0.50 - 0.99)**:
    *   Controla qué tan detallada es la observación del modelo.
    *   *Uso*: 0.95 es el estándar de oro para textiles.
3.  **Ajuste de Umbral en Caliente (Offset)**:
    *   *Nota Técnica (V32.5)*: El motor base es estrictamente riguroso por defecto, anclado a solo el 1.05x de la desviación topológica máxima vista en la sesión de entrenamiento.
    *   **Hacia "ESTRICTO" (+)**: El sistema escala la hipersensibilidad, reportando anomalías geométricas microscópicas.
    *   **Hacia "IGNORAR" (-)**: Incrementa el margen algorítmico de seguridad para que el motor tolere variaciones leves o reflejos parásitos (sin corromper la exactitud del heatmap en tiempo real).

### Métricas y Tendencia
- **Puntaje de Anomalía**: Una calificación de **0 a 100**. 
    *   0-20: Tela Perfecta.
    *   20-50: Variación leve (Alerta).
    *   >50: Defecto confirmado (Rojo).
- **Gráfica de Tendencia**: Muestra cómo ha variado la calidad en los últimos 50 cuadros. Si la línea sube constantemente, hay un problema en la máquina textil.

---

## 3. Calificación y Calibración

### ¿Cómo activar/desactivar la calificación?
La calificación (inferencia) se activa al presionar **Iniciar Inspección**. 
- Para **desactivarla**, simplemente cambia la Referencia seleccionada o presiona el botón de detener (si está disponible según la versión de UI).
- El sistema guarda un log de cada defecto detectado con su puntaje exacto para auditorías posteriores.

---

## 4. Solución de Problemas (Troubleshooting)

| Problema | Causa Probable | Solución |
|---|---|---|
| **Estatus: "SIN CÁMARA"** | El Bridge no pudo conectar con la cámara física o el simulador. | Revisar conexión de red o ejecutar `docker logs bridge-linea1-final`. |
| **Puntaje sube a 100 sin razón** | La referencia seleccionada no corresponde a la tela que está pasando. | Cambiar a la referencia correcta o re-entrenar con la tela actual. |
| **Imagen muy oscura/clara** | Exposición de la cámara incorrecta. | Ajustar iluminación física o parámetros de cámara en el driver. |
| **Error 500 al Entrenar** | Menos de 10 imágenes capturadas. | Captura al menos 20 frames de "tela buena" antes de entrenar. |

---

## 5. Escalabilidad: Cómo agregar más Cámaras y Líneas

Para agregar una cámara nueva, sigue este patrón en tu archivo `docker-compose.yml`:

### Paso 1: Duplicar el bloque de servicio
Copia el bloque de `bridge-l1-final` y cámbiale el nombre (ej. `bridge-l2-inicio`).

### Paso 2: Configurar las Variables de Identidad
Debes asegurar que estos 4 valores sean únicos para la nueva cámara:

| Variable | Valor de Ejemplo | Qué hace |
|---|---|---|
| `CAMERA_IP` | `192.168.0.11` | La dirección física de la nueva cámara en la red. |
| `CAMERA_LINE_ID` | `2` | ID numérico de la nueva línea de producción. |
| `CAMERA_POINT_ID` | `3` | ID numérico único para este punto de inspección. |
| `CAMERA_ID` | `cam-l2-inicio` | Un alias legible (etiqueta) para identificarla. |

### Ejemplo en `docker-compose.yml`:
```yaml
  bridge-l2-inicio:
    <<: *bridge-base
    container_name: bridge-linea2-inicio
    environment:
      <<: *bridge-env-base
      CAMERA_MODE: live
      CAMERA_IP: "192.168.0.11"
      CAMERA_LINE_ID: "2"
      CAMERA_POINT_ID: "3"
      CAMERA_ID: "cam-l2-inicio"
```

### Paso 3: Aplicar Cambios
Ejecuta: `docker compose up -d`. El sistema detectará el nuevo servicio y lo integrará automáticamente al backend sin apagar las cámaras existentes.

---

## 6. Consideraciones Técnicas de Red
*   **Conexión GigE/IP**: Si las cámaras están en una subred distinta, asegúrate de que el IoT tenga una ruta de red hacia ellas.
*   **Ancho de Banda**: Cada cámara enviando 10 FPS consume ~5-10 Mbps. Verifica que tu red planta soporte el tráfico total de N cámaras.

---

## 7. Gestión de Memoria y Disco (Zero-Storage)

Una de las grandes ventajas de Nuvant es que **no necesitas borrar archivos nunca**. El sistema usa una filosofía de "Zero-Storage":
- **Entrenamiento**: Las fotos que tomas se procesan en la memoria RAM y se borran apenas termina el entrenamiento. Solo se queda el "modelo" inteligente.
- **Producción**: El video que ves pasando **no se está guardando**. El sistema lo analiza y lo olvida en milisegundos.
- **Seguridad**: Esto garantiza que el disco del equipo IoT nunca se llene y que el hardware dure muchos años más.

> [!NOTE]
> Si en un futuro necesitas guardar evidencia fotográfica de los defectos, un ingeniero puede activar esta opción, pero por defecto, el sistema es ultra-eficiente.
