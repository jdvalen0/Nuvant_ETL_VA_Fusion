# Nuvant Camera Bridge — Dockerfile
# Python 3.7 requerido por stapipy wheel (cp37)
FROM python:3.7-slim

ENV DEBIAN_FRONTEND=noninteractive
ENV PYTHONDONTWRITEBYTECODE=1
ENV PYTHONUNBUFFERED=1

# Dependencias de sistema para OpenCV headless y Sentech SDK
RUN apt-get update && apt-get install -y --no-install-recommends \
    libglib2.0-0 \
    libsm6 \
    libxext6 \
    libgl1-mesa-glx \
    libusb-1.0-0 \
    libpng16-16 \
    libturbojpeg0 \
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

# Definir rutas estándar de Sentech SDK para consistencia
ENV STAPI_ROOT_PATH=/opt/sentech
RUN mkdir -p /opt/sentech/lib

RUN ARCH=$(uname -m) && \
    echo "Building for Architecture: $ARCH" && \
    if [ "$ARCH" = "x86_64" ]; then \
    WHL="/tmp/wheels/stapipy-1.1.2.1-cp37-cp37m-linux_x86_64.whl"; \
    if [ -f "$WHL" ]; then \
    pip install --no-cache-dir "$WHL" && \
    cp -PR /tmp/lib/* /opt/sentech/lib/ && \
    ldconfig; \
    else \
    echo "ERROR: x86_64 wheel not found at $WHL"; exit 1; \
    fi; \
    elif [ "$ARCH" = "aarch64" ]; then \
    WHL=$(ls /tmp/wheels/stapipy*aarch64.whl 2>/dev/null || ls /tmp/wheels/stapipy*arm64.whl 2>/dev/null); \
    if [ -n "$WHL" ] && [ -f "$WHL" ]; then \
    pip install --no-cache-dir "$WHL" && \
    cp -PR /tmp/lib/* /opt/sentech/lib/ && \
    ldconfig; \
    else \
    echo "WARNING: ARM64 wheel not found. Camera LIVE mode will fail on this hardware."; \
    echo "Please place the ARM64 .whl in camera_bridge/wheels/ to enable LIVE mode."; \
    fi; \
    fi

# Configure environment variables as per .stprofile
ENV GENICAM_GENTL64_PATH="/opt/sentech/lib:${GENICAM_GENTL64_PATH}"
ENV LD_LIBRARY_PATH="/opt/sentech/lib:/opt/sentech/lib/GenICam:${LD_LIBRARY_PATH}"
ENV LIBRARY_PATH="/opt/sentech/lib:/opt/sentech/lib/GenICam:${LIBRARY_PATH}"

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
