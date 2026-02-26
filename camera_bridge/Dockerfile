# Nuvant Camera Bridge — Dockerfile
# Python 3.7 requerido por stapipy wheel (cp37)
FROM python:3.7-slim

ENV DEBIAN_FRONTEND=noninteractive
ENV PYTHONDONTWRITEBYTECODE=1
ENV PYTHONUNBUFFERED=1

# Dependencias de sistema para OpenCV headless
RUN apt-get update && apt-get install -y --no-install-recommends \
    libglib2.0-0 \
    libsm6 \
    libxext6 \
    libgl1-mesa-glx \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Instalar dependencias Python (sin stapipy aún)
COPY requirements.txt .
RUN pip install --upgrade pip && \
    pip install --no-cache-dir -r requirements.txt

# Instalar stapipy desde wheel local (Detección de Arquitectura)
ARG TARGETPLATFORM
COPY wheels/ /tmp/wheels/
COPY lib/ /tmp/lib/

RUN ARCH=$(uname -m) && \
    echo "Building for Architecture: $ARCH" && \
    if [ "$ARCH" = "x86_64" ]; then \
    WHL="/tmp/wheels/stapipy-1.1.2.1-cp37-cp37m-linux_x86_64.whl"; \
    if [ -f "$WHL" ]; then \
    pip install --no-cache-dir "$WHL" && \
    cp /tmp/lib/libStApi_TL.so.1.1 /usr/local/lib/ && \
    ldconfig; \
    else \
    echo "ERROR: x86_64 wheel not found at $WHL"; exit 1; \
    fi; \
    elif [ "$ARCH" = "aarch64" ]; then \
    WHL=$(ls /tmp/wheels/stapipy*aarch64.whl 2>/dev/null || ls /tmp/wheels/stapipy*arm64.whl 2>/dev/null); \
    if [ -n "$WHL" ] && [ -f "$WHL" ]; then \
    pip install --no-cache-dir "$WHL" && \
    cp /tmp/lib/libStApi_TL.so.1.1 /usr/local/lib/ && \
    ldconfig; \
    else \
    echo "WARNING: ARM64 wheel not found. Camera LIVE mode will fail on this hardware."; \
    echo "Please place the ARM64 .whl in camera_bridge/wheels/ to enable LIVE mode."; \
    fi; \
    fi

# Código del bridge
COPY camera_bridge.py .

# Directorio para imágenes de simulación (se monta como volumen en docker-compose)
RUN mkdir -p /simulate_images

# Variables de entorno por defecto
ENV CAMERA_MODE=simulate
ENV CAMERA_FPS=5.0
ENV JPEG_QUALITY=80
ENV VA_BACKEND_WS_URL=ws://nuvant-backend:8000/api/inference/camera_feed
ENV SIMULATE_DIR=/simulate_images

CMD ["python", "camera_bridge.py"]
