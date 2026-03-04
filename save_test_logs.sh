#!/bin/bash
# Guarda logs de los contenedores (backend + bridge) para la sesión de pruebas.
# Uso: ./save_test_logs.sh [sufijo]
#   Sin argumentos: logs_pruebas/YYYY-MM-DD_HH-MM-SS.log
#   Con sufijo:     logs_pruebas/YYYY-MM-DD_HH-MM-SS_sufijo.log

set -e
REPO_ROOT="$(cd "$(dirname "$0")" && pwd)"
cd "$REPO_ROOT"
LOGDIR="${REPO_ROOT}/logs_pruebas"
mkdir -p "$LOGDIR"
STAMP=$(date +%Y-%m-%d_%H-%M-%S)
SUF="${1:-}"
FNAME="${STAMP}${SUF:+_$SUF}.log"
PATH_LOG="${LOGDIR}/${FNAME}"

echo "Guardando logs en: ${PATH_LOG}"
docker compose logs --no-color > "${PATH_LOG}" 2>&1
echo "  Total líneas: $(wc -l < "${PATH_LOG}")"

# Opcional: por servicio (mismo directorio, mismo prefijo)
docker compose logs --no-color nuvant-backend        > "${LOGDIR}/${STAMP}${SUF:+_$SUF}_nuvant-backend.log" 2>&1
docker compose logs --no-color bridge-linea1-final   > "${LOGDIR}/${STAMP}${SUF:+_$SUF}_bridge-linea1-final.log" 2>&1
echo "  También: ${STAMP}${SUF:+_$SUF}_nuvant-backend.log"
echo "  También: ${STAMP}${SUF:+_$SUF}_bridge-linea1-final.log"
echo "Listo."
