# Vision System: Inteligencia Artificial para la Excelencia en Manufactura

Vision System es una solución de visión artificial de alto rendimiento diseñada para la Manufactura de Cero Defectos (ZDM). El sistema integra algoritmos de detección de anomalías no supervisados (PatchCore V32) para optimizar líneas de producción industrial en tiempo real.

## Objetivo de Negocio

Maximizar la rentabilidad operativa mediante la digitalización del control de calidad bajo dos pilares fundamentales:

1.  **Optimización de Producción**: Permite aumentar la velocidad de las líneas eliminando los cuellos de botella generados por la inspección humana visual, reduciendo la fatiga del operario y garantizando un escrutinio del 100% de la producción 24/7.
2.  **Detección Automática de Errores**: Identifica instantáneamente desviaciones estéticas, estructurales o funcionales (hilos sueltos, contaminaciones, fallos de patrón) sin necesidad de programar reglas manuales, reduciendo drásticamente el desperdicio de materia prima y las devoluciones por calidad.

## Ventajas Estratégicas

*   **Entrenamiento Dinámico**: El sistema aprende el estándar de calidad directamente de la línea en movimiento en menos de 30 segundos.
*   **Filosofía Zero-Storage**: Optimizado para Edge Computing (NVIDIA Jetson / ARM64), procesando todo en RAM para evitar el desgaste del hardware y asegurar latencias mínimas.
*   **Precisión Rigurosa**: Implementa normalización espectral para entregar un puntaje de calidad intuitivo (0-100), donde cualquier valor inferior a 50 alerta una anomalía confirmada.
*   **Agnóstico al Hardware**: Compatible con cámaras industriales GigE/USB (Omron/Sentech) y flujos estáticos de archivos para validaciones de oficina.

## Documentación del Sistema

Para profundizar en el uso y la ingeniería del proyecto:

*   [Operación Servidor Remoto](file:///home/juan-david-valencia/Escritorio/Nuvant_ETL_VA_Fusion/OPERACION_SERVIDOR_REMOTO.md): Guía paso a paso para configurar el equipo como servidor y acceder vía red.
*   [Documentación Técnica](file:///home/juan-david-valencia/Escritorio/Nuvant_ETL_VA_Fusion/DOCUMENTACION_TECNICA.md): Arquitectura de microservicios, stack tecnológico y despliegue.
*   [Teoría y Algoritmos](file:///home/juan-david-valencia/Escritorio/Nuvant_ETL_VA_Fusion/ARQUITECTURA_Y_TEORIA_PHD.md): Fundamentación matemática de PatchCore y normalización de distancias.

## Arranque Rápido

Asegúrese de tener Docker instalado y ejecute la inicialización agnóstica antes de levantar los contenedores:

```bash
# 1. Preparar entorno (Directorios y Permisos)
chmod +x init_deploy.sh
./init_deploy.sh

# 2. Levantar el sistema
# Modo Producción (Cámara en vivo)
CAMERA_MODE=live docker compose up -d

# Modo Simulación (Carga de archivos)
docker compose up -d
```

Acceso a la consola de control: `http://localhost:8000/static/index.html`
