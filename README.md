# Nuvant Vision System

Sistema de inspección industrial en tiempo real con detección de anomalías no supervisada (PatchCore V32), backend FastAPI y bridge de cámara GigE.

## Estado vigente

- Flujo productivo: `CALIBRATE -> TRAIN -> PAUSE -> INSPECT`.
- **Inspección por sesión**: cada "Iniciar → Detener" crea una inspección; el informe se genera por inspección.
- Entrenamiento dinámico: captura desde cámara con límite configurable + submuestreo aleatorio.
- Ajuste en caliente: slider de sensibilidad (`sensOffset`) aplicado sobre umbral ya entrenado.
- Persistencia: modelos, SQLite (referencias, inspecciones, defectos) en volúmenes locales.
- Señal PLC S7 (opcional): bit de defecto en PLC Siemens vía snap7; configuración en `.env`.

## Servicios activos

- `nuvant-backend`: API, entrenamiento, inferencia y UI.
- `bridge-l1-final`: adquisición de cámara (`stapipy`) y envío WS a backend.
- Orquestación: `docker-compose.yml` en la raíz.

## Arranque rápido

```bash
chmod +x init_deploy.sh
./init_deploy.sh
docker compose up -d --build
```

UI:
- `http://localhost:8000/static/`
- `http://<IP_SERVIDOR>:8000/static/`

## Documentación canónica

| Documento | Contenido |
|-----------|-----------|
| `INSTRUCCIONES_OPERATIVAS.md` | Comandos Docker, flujo operativo completo, PLC, cámara. |
| `DOCUMENTACION_TECNICA.md` | Arquitectura, API, frontend y parámetros. |
| `AUDITORIA_CAMBIOS_INSPECCION.md` | Modelo inspección, informe por sesión, correcciones BUG-1 a BUG-6. |
| `CAPTURA_LOGS_PRUEBAS.md` | Cómo capturar y guardar logs durante pruebas. |
| `OPERACION_SERVIDOR_REMOTO.md` | Despliegue, operación en servidor y recuperación. |
| `GUIA_AJUSTES_PRODUCCION.md` | Metodología de tuning (`contamination`, `sensOffset`). |
| `ARQUITECTURA_Y_TEORIA_PHD.md` | Fundamento científico PatchCore. |
| `AUDITORIA_PRE_PRUEBAS.md` | Checklist pre-pruebas, cuándo reconstruir. |
