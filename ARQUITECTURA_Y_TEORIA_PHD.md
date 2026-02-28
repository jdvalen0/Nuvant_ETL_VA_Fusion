# Arquitectura Profunda y Fundamentos Teóricos

Este documento expone la fundamentación teórica, matemática y arquitectónica del **Nuvant Vision System**, operando de facto como un documento de diseño de nivel de ingeniería avanzada (PhD level).

El objetivo supremo de este sistema es habilitar la **Manufactura de Cero Defectos (Zero-Defect Manufacturing - ZDM)** mediante el paradigma de **Edge Computing** e **Inteligencia Artificial No Supervisada**, procesando flujos de datos topológicos en tiempo real directamente en la línea de producción (Hardware IoT - ARM64/x86).

---

## 1. Topología de Microservicios (Separation of Concerns)

La arquitectura resuelve un problema clásico de instrumentación industrial: la incompatibilidad entrópica entre los drivers de bajo nivel de hardware propietario (cámaras) y los frameworks de IA de alto nivel.

El sistema emplea un pipeline **ETL Espacial (Extract, Transform, Load)** implementado en dos contenedores Docker ortogonales:

1.  **Camera Bridge (El Sensor Ciberfísico)**: Contenedor efímero y altamente acoplado al hardware.
2.  **Backend VA (El Motor Cognitivo)**: Contenedor persistente, agnóstico al hardware físico y dedicado puramente al álgebra tensorial y almacenamiento.

Esta separación ("Air-gapping" a nivel lógico) garantiza que una falla en el hardware óptico no corrompa el estado del motor de inferencia, y permite que la IA se actualice independientemente de los drivers físicos.

---

## 2. Contenedores y Comportamiento

### A. Contenedor: `camera_bridge` (Adquisición Asíncrona)
*   **Tecnología Base**: Python 3.7 (Restricción dictada por la ABI de `stapipy` de Sentech/Omron).
*   **Comportamiento Dinámico**: Actúa como un *productor infinito* en un modelo Productor-Consumidor. Utiliza el protocolo GenICam sobre GigE Vision para solicitar arreglos de píxeles puros a la cámara.
*   **Función de Transformación**: El bridge no solo lee; realiza una reducción de dimensionalidad entrópica al comprimir el arreglo de Numpy crudo (RGB/Grayscale) en un buffer JPEG en memoria, minimizando la latencia de red en el bus de comunicación interno (localhost/docker-network).
*   **Manejo de Errores (Backoff Exponencial)**: Implementa un ciclo de reconexión topológica recursiva. Si el Backend o la cámara caen, el Bridge no aborta (Exit 1 fatal), sino que ralentiza sus latidos (heartbeats) esperando el restablecimiento del canal de sockets, crucial para operaciones 24/7 sin intervención humana.

### B. Contenedor: `nuvant_backend_va` (Inferencia y Estado)
*   **Tecnología Base**: Python 3.11, FastAPI, SQLAlchemy, PyTorch/Anomalib.
*   **Comportamiento Dinámico**: Mantiene un hilo principal asíncrono (ASGI) para ingestar frames del Bridge vía WebSocket. Posee una memoria estocástica de los modelos entrenados cargados en Caché RAM (para lograr inferencias de ~30-50ms).
*   **Filosofía Zero-Storage**: Para proteger la memoria flash (eMMC/SD) en dispositivos IoT, este contenedor *nunca* escribe imágenes a disco. Todo el procesamiento tensorial y la evaluación de anomalías ocurren puramente en memoria volátil (RAM/VRAM). Sólo se persisten los metadatos numéricos en SQLite.

---

## 3. Fundamentación Teórica de los Algoritmos de IA

El problema central de la visión industrial moderna es la **ausencia empírica de defectos** durante la fase de despliegue. Entrenar redes neuronales convolucionales (CNN) tradicionales requiere miles de imágenes de cada tipo de fallo posible, lo cual es inviable en entornos de alta calidad.

Por ende, el sistema utiliza **Detección de Anomalías No Supervisada (Unsupervised Anomaly Detection - UAD)**: se modela exclusivamente la "distribución de la normalidad" (Golden Run). Cualquier desviación topográfica de esta distribución es, por definición matemática, una anomalía.

### A. Motor Principal: Algoritmo PatchCore (V32)
*El estado del arte en representación jerárquica de características.*

*   **Teoría (Feature Extraction)**: Se inyecta la imagen en un a priori congelado (Backbone pre-entrenado en ImageNet, típicamente un ResNet). En lugar de mirar la imagen completa, se extraen activaciones de capas intermedias (features jerárquicos). Esto captura tanto textura local de bajo nivel (hilos) como semántica estructural de alto nivel (patrones de diseño).
*   **Teoría (Coreset Subsampling)**: Si guardamos todos los parches (patches) de todas las imágenes buenas, la memoria explotará (O(N)). PatchCore resuelve formalmente esto como un problema de **Minimax Facility Location**. Emplea un algoritmo de aproximación voraz (Greedy Approximation) para encontrar un subconjunto ínfimo de parches (el Coreset) que minimice geométricamente la distancia máxima a cualquier parche del conjunto original. Logra retener la "esencia" topológica de la tela desechando el 90% a 99% de la redundancia espacial.
*   **Inferencia (Nearest Neighbor Distance)**: Al recibir una nueva imagen, se convierte en tensores, espacialmente alineados. Para cada parche de prueba, se mide la métrica $L_2$ (Distancia Euclidiana) hasta el vecino más cercano en el Banco de Memoria (Coreset).
*   **Salida (Heatmap)**: Se interpola bilateralmente la matriz de distancias para generar un Mapa de Calor topológico, permitiendo la localización espacial del defecto con precisión de pixel.

### B. Motor Secundario: Mahalanobis Espectral (V31 - Fallback/Edge)
*El estándar de oro estadístico multivariado industrial.*

*   **Teoría**: En arquitecturas ARM donde PyTorch pueda fallar o los recursos sean extremadamente escasos, V31 abstrae el problema a pura estadística paramétrica.
*   **Transformación**: Divide la imagen en teselaciones cuadradas (Tiles) y extrae características de textura aplanadas. Utiliza Análisis de Componentes Principales (PCA) para colapsar la covarianza a los vectores propios con mayor varianza espectral.
*   **Distancia de Mahalanobis**: Calcula la distancia del punto central de masa de la distribución. Matemáticamente, aísla si un defecto cambia las *correlaciones* direccionales de la tela, usando la matriz de covarianza encogida (Shrinkage de Ledoit-Wolf para máxima robustez ante tamaño muestral ínfimo). A diferencia de Euclides, Mahalanobis entiende la "forma" de los datos normales.

---

## 4. Normalización Métrica Espacial (Axioma "100 = Perfecto")

La arquitectura dictaminó un estándar absoluto de UX y matemáticas de decisión:

*   **Problema Histórico**: V31 y primeras V32 devolvían magnitudes vectoriales puras (distancias al infinito), imposibilitando un umbral de decisión lógico para el operario o un gráfico probabilístico.
*   **Teoría de Normalización Estricta (V32.5)**: Mapear la distancia absoluta $D$ respecto a un hiperplano de decisión topológica $T$ (el Umbral). Este umbral se ancla rígidamente a la varianza real de la tela, establecido como estrictamente el 1.05x de la desviación máxima observada en el entrenamiento, eliminando falsos positivos por inflados de ruido mientras garantiza hipersensibilidad.
*   **Ecuación de Calidad**:
    Acotamos el error a $S = \min(100, (\frac{D} {T + \epsilon}) \times 50)$
    Luego lo invertimos para medir "Calidad": $Q = \max(0, 100 - S)$
*   **Consecuencia Axiomática**: 
    - Si la imagen empata exactamente la radiometría del umbral ($D = T$), su puntaje será rigurosamente **50**.
    - Por ende, el axioma unificado dicta: **Todo puntaje $Q < 50$ es un hiper-vector fuera de la distribución normal y se clasifica, sin incertidumbre, como DEFECTO.**
    - Un puntaje de **100** implica $D = 0$ (Cero desviación del centro manifold de la distribución de entrenamiento).
    - **Sincronización Cromática**: El Heatmap V32.5 renderiza saturaciones rojas de alerta únicamente cuando el hiper-vector $D$ traspasa el hiperplano $T$, asegurando concordancia visual absoluta con la ecuación y los widgets del Frontend.

## Conclusión de Auditoría

La arquitectura híbrida Bridge-Backend, acoplada a la reducción tensorial por Coreset Subsampling (PatchCore) y la normalización matemática de hiper-vectores, se complementa en la versión **V33.1** con un saneamiento estructural profundo. La consolidación de la persistencia mediante Bind Mounts y la automatización de inicialización aseguran que el Sistema Vision System sea una solución resiliente, matemáticamente trazable y profesionalmente transportable entre entornos Linux/Ubuntu sin degradación operativa.
