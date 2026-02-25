#!/usr/bin/env bash
set -e

# Si StApi trae script de entorno, sourséalo aquí (ajusta la ruta real):
# source /opt/stapi/bin/setenv.sh
# o source /etc/profile.d/stapi.sh

# Fallback: añade rutas comunes (ajusta a tu caso)
export LD_LIBRARY_PATH="/opt/stapi/lib:/usr/local/lib:${LD_LIBRARY_PATH}"

exec python3 /scripts/script-camera1.py
