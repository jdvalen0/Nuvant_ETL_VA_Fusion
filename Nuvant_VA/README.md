# Nuvant_VA (Backend + UI)

Este modulo contiene:

- API FastAPI de entrenamiento/inferencia.
- UI operativa en `backend/api/static/index.html`.
- Persistencia local (`backend/db`, `backend/local_storage`).

## Nota de despliegue

El despliegue operativo actual del proyecto completo se hace desde la raiz del repositorio con `docker-compose.yml` principal, no desde `Nuvant_VA/docker/docker-compose.yml`.

Comando recomendado:

```bash
docker compose up -d --build
```

UI:

- `http://localhost:8000/static/`

## Documentos de referencia

- `../INSTRUCCIONES_OPERATIVAS.md` — operación, Docker, **señal PLC**
- `../DOCUMENTACION_TECNICA.md`
- `../OPERACION_SERVIDOR_REMOTO.md`
- `../GUIA_AJUSTES_PRODUCCION.md`
