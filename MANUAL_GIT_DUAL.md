# 🛠️ PROTOCOLO DE CONFIGURACIÓN DUAL (VENUS-SERIES)

Este documento contiene los pasos exactos para vincular cualquier proyecto nuevo a tus dos cuentas de GitHub simultáneamente usando las llaves SSH ya configuradas.

## 1. Identidad Local (Obligatorio)
Fija tu firma personal para que los commits no usen el correo de la empresa:
git config --local user.name "Juan David Valencia"
git config --local user.email "jdvalen0@gmail.com"

## 2. Vinculación Dual (SSH)
Reemplaza 'NOMBRE_REPO' por el nombre del proyecto en GitHub.

# Agregar el origen (Fetch)
git remote add origin git@github.com-elico:Team-I4-0/NOMBRE_REPO.git

# Configurar el Push Dual (Elico + Personal)
git remote set-url --push --add origin git@github.com-elico:Team-I4-0/NOMBRE_REPO.git
git remote set-url --push --add origin git@github.com-personal:jdvalen0/NOMBRE_REPO.git

## 3. Gestión de Archivos Pesados (Git LFS)
Si manejas datos de investigación (>100MB), actívalo antes del primer push:
git lfs install
git lfs track "*.csv" "*.xlsx" "*.pkl"
git add .gitattributes

## 4. Primer Envío
git add .
git commit -m "Initial setup: dual sync & identity"
git branch -M main
git push -u origin main

---
### 🔍 Recordatorio de Hardware (Venus-series)
- Alias Elico: github.com-elico
- Alias Personal: github.com-personal
