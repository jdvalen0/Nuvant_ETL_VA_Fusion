# Guía de Pruebas y Validación: Nuvant Vision System 🏭

Este documento describe los pasos exactos para validar el sistema en sus dos modalidades operativas. Ambos escenarios utilizan el núcleo de IA **PatchCore (V32)** y deben entregar resultados consistentes bajo las mismas condiciones ópticas.

---

## Escenario A: Validación Estática (Simulación por Archivos) 📁
*Ideal para pruebas de oficina, desarrollo de lógica y validación de datasets previos sin hardware.*

### Fase 1: Entrenamiento Estático
1.  **Crear Referencia**: En el panel "Fase 1", ingresa un nombre (ej. `Prueba_Estatica_01`) y haz clic en **Crear**.
2.  **Cargar Imágenes**: Haz clic en **"Seleccionar Imágenes para Entrenar"** y elige al menos 10 fotos **totalmente limpias** (sin defectos) de tu disco duro.
3.  **Subir**: Haz clic en el botón azul **"1. Subir al Servidor"**.
4.  **Procesar**: Haz clic en el botón verde **"2. Iniciar Entrenamiento"**.
    - *Resultado*: Al finalizar, la referencia aparecerá con un `✅ Listo`.

### Fase 2: Inferencia (Drag-and-Drop)
1.  **NO** actives el botón de inspección (este modo está reservado exclusivamente para la cámara en vivo).
2.  **Arrastrar**: Selecciona una imagen de tu disco (buena o con defecto) y **suéltala (drop)** directamente sobre la "ventana de video" negra en el panel derecho.
3.  **Análisis Persistente**: El sistema procesará esa imagen instantáneamente y mantendrá el resultado visible en la UI sin desaparecer.
    - Si la imagen es congruente con el entrenamiento: Score > 50, Badge Verde **CALIDAD OK**.
    - Si tiene defecto (superando el estricto umbral 1.05x calibrado dinámicamente): Score < 50, Badge Rojo **DEFECTO DETECTADO** + **Heatmap activado (sincrónicamente coloreado con la métrica al umbral)**.

---

## Escenario B: Validación Dinámica (Cámara en Vivo) 📷
*Escenario real de producción. Requiere cámara Sentech conectada o Webcam configurada en el bridge.*

### Fase 1: Entrenamiento Dinámico (Captura en Caliente)
1.  **Crear Referencia**: Ingresa un nuevo nombre (ej. `Produccion_Linea_01`) y haz clic en **Crear**.
2.  **Iniciar Captura**: Haz clic en el botón naranja **"Iniciar Captura Entrenamiento"**. La cámara comenzará a ingerir fotos en memoria infinitamente.
    - *Parametrización Visual (Cantidad de Imágenes)*: No hay un límite automático. **Tú** controlas el volumen observando el contador de "Frames" en pantalla. Se recomiendan entre **30 y 100 imágenes** que abarquen vibraciones y luces normales de planta (15 a 30 segundos de captura).
3.  **Detener y Generar Modelo**: Para detener la toma fotográfica, simplemente haz clic en el botón verde **"Entrenar Modelo"**. 
    - *Resultado*: Esto aborta instantáneamente la recolección visual de la cámara, acopla todas las imágenes recolectadas en la RAM en ese tiempo y genera la Inteligencia Artificial definitiva.

### Fase 2: Inferencia en Tiempo Real
1.  **Activar**: Haz clic en el botón azul **"Iniciar Inspección"**.
2.  **Monitoreo**: El sistema procesará el flujo de la cámara a los FPS configurados.
3.  **Detección**: Al pasar un defecto físico bajo la cámara, el sistema activará la alerta y el Heatmap en tiempo real.

---

## Diferencias y Recomendaciones Críticas ⚠️

| Característica | Escenario Estático | Escenario Dinámico |
| :--- | :--- | :--- |
| **Origen del Dato** | JPEG/PNG de Disco | Stream RAW de Cámara |
| **Tiempo de Entrenamiento** | Inmediato (según CPU) | 20-30 segundos de captura |
| **Resiliencia** | Alta (datos perfectos) | Media (sensible a cambios de luz) |
| **Uso de Memoria** | Bajo | Alto (Buffer de RAM) |

> [!IMPORTANT]
> **Consistencia Óptica**: Si entrenas de forma **Estática** (subiendo fotos), **NO** pruebes con la cámara en vivo, ya que la diferencia de lente y luz causará falsos positivos. Si vas a usar cámara, entrena con cámara. Si vas a usar fotos, prueba arrastrando fotos.

## Conclusión de Clasificación
En ambos escenarios, una vez detectado el error (Badge Rojo), puedes usar el panel de **"Clasificación de Defectos"** para etiquetar la causa raíz (ej. Hilo Suelto, Contaminación) y alimentar la base de datos de aprendizaje estadístico.
