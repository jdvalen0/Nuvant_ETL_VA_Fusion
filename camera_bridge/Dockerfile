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

# Instalar stapipy desde wheel local (x86_64)
# Los .whl se copian desde el proyecto ETL original
COPY wheels/stapipy-1.1.2.1-cp37-cp37m-linux_x86_64.whl /tmp/
RUN pip install --no-cache-dir /tmp/stapipy-1.1.2.1-cp37-cp37m-linux_x86_64.whl

# Librería nativa requerida por stapipy
COPY lib/libStApi_TL.so.1.1 /usr/local/lib/
RUN ldconfig

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
