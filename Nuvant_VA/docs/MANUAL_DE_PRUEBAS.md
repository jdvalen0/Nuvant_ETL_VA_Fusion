# 🧪 Manual de Pruebas Industrial (V10 - Atomic Gold Standard)

> [!WARNING]
> Documento historico de suite de pruebas offline/dataset.
> No representa el flujo operativo dinamico actual de camara (`CALIBRATE -> TRAIN -> PAUSE -> INSPECT`).
> Para operacion productiva usar `GUIA_AJUSTES_PRODUCCION.md` y `OPERACION_SERVIDOR_REMOTO.md`.

## 🏆 Certificado de Pureza Atómica

Esta suite representa la verdad absoluta del dataset. Se ha abandonado el uso de "rangos de tiempo" (que causaron errores por saltos no lineales en el video) en favor de una **Lista Atómica** de archivos verificados visualmente uno por uno.

### 🚫 Correcciones Finales (V10 vs V9)
1.  **Piel Intermedia**: Se detectó que el rango 06:xx estaba contaminado con Radial.
    *   *Solución V10*: Se seleccionaron 5 frames específicos del bloque `05:51-05:59` (Textura oscura correcta).
2.  **Radial**: Se detectó que el rango 17:59 estaba contaminado con Geométrica/Negro.
    *   *Solución V10*: Se seleccionaron 5 frames específicos del bloque `17:41-17:49`.

---

## 📂 Organización del Master Suite (V10)

Ubicación: `/home/juan-david-valencia/Escritorio/Nuvant_VA/INDUSTRIAL_TEST_SUITE_V10/`

Esta suite contiene ÚNICAMENTE los siguientes archivos fuente:

### 🧵 Referencias Sintéticas (Imágenes):
*   **`REF_01_Anillos`** (9 Archivos): `IMG_2385` a `IMG_2392`, `IMG_2394`.
*   **`REF_02_Trama`** (13 Archivos): `IMG_2402-2409` y `IMG_2411-2415`.

### 🎥 Referencias Frames (Atomic 5-Pack):
*   **`REF_03_Piel_Rugosa`**: 5 frames del bloque `05:31`.
*   **`REF_04_Piel_Suave`**: 5 frames del bloque `06:31`.
*   **`REF_05_Piel_Intermedia`**: 5 frames del bloque `05:51` (Corregido).
*   **`REF_06_Geometrica`**: 5 frames del bloque `13:31`.
*   **`REF_07_Radial`**: 5 frames del bloque `17:41` (Corregido).

---

Cualquier archivo fuera de esta lista se considera **BASURA** y no debe usarse para entrenamiento.
