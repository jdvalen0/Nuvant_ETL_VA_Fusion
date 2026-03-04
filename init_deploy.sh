#!/bin/bash

# ══════════════════════════════════════════════════════════════════════════════
# Vision System - Script de inicialización de despliegue (Agnóstico Ubuntu)
# ══════════════════════════════════════════════════════════════════════════════

set -e

echo "🚀 Iniciando preparación del entorno Vision System..."

# 1. Definir rutas de persistencia (Consolidado V33.1)
PERSISTENCE_DIRS=(
    "Nuvant_VA/backend/db"
    "Nuvant_VA/backend/logs"
    "Nuvant_VA/backend/local_storage"
)

# 2. Crear directorios con permisos del usuario actual
echo "📬 Creando estructura de directorios persistentes..."
for dir in "${PERSISTENCE_DIRS[@]}"; do
    if [ ! -d "$dir" ]; then
        mkdir -p "$dir"
        echo "   [OK] Creado: $dir"
    else
        echo "   [SKIP] Ya existe: $dir"
    fi
    # Asegurar que Git respete la carpeta
    touch "$dir/.gitkeep"
done

# 3. Verificar imágenes de simulación
if [ ! -d "simulate_images" ]; then
    echo "⚠️  ADVERTENCIA: No se encuentra la carpeta 'simulate_images'."
    mkdir -p simulate_images
    echo "   [INFO] Carpeta creada. Coloca tus imágenes JPEG en 'simulate_images/' para el modo simulación."
fi

# 4. Ajustar permisos para Docker (Evitar creación como Root)
# Si los dirs fueron escritos por contenedores (root), chmod puede fallar; no abortar.
echo "🔐 Ajustando permisos de seguridad..."
chmod -R 775 Nuvant_VA/backend/db Nuvant_VA/backend/logs Nuvant_VA/backend/local_storage 2>/dev/null || true

echo "✅ Entorno listo para el despliegue."
echo "💡 Para iniciar el sistema ejecute:"
echo "   docker compose up -d"
echo "══════════════════════════════════════════════════════════════════════════════"
