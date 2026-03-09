"""
Pre-descarga pesos de PyTorch durante docker build.
Evita socket.gaierror en runtime cuando el contenedor no tiene internet/DNS.
"""
import torch
import torchvision.models as models

print("[Docker] Pre-descargando MobileNetV2 (FeatureExtractor)...")
models.mobilenet_v2(weights=models.MobileNet_V2_Weights.IMAGENET1K_V1)

print("[Docker] Pre-descargando WideResNet50 (PatchCore backbone)...")
models.wide_resnet50_2(weights=models.Wide_ResNet50_2_Weights.IMAGENET1K_V1)

print("[Docker] Pesos cacheados en /root/.cache/torch/hub/checkpoints/")
