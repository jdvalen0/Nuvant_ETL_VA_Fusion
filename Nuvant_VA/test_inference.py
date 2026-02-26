import numpy as np
import base64
import cv2
import sys
import os

# Set working directory to project root or Nuvant_VA so it finds backend
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), ".")))

try:
    from backend.core.anomaly_patchcore import PatchCoreDetector
except ImportError as e:
    print(f"Error import: {e}")
    sys.exit(1)

detector = PatchCoreDetector()
img = np.random.randint(0, 255, (256, 256, 3), dtype=np.uint8)
img2 = np.random.randint(0, 255, (256, 256, 3), dtype=np.uint8)

# train
print("Training...")
detector.train(images=[img, img, img2, img2])

print("Predicting same image...")
is_anom, score, heatmap = detector.predict(image=img)
print(f"Is Anomaly: {is_anom}, Quality Score: {score}")
print("Heatmap max:", np.max(heatmap) if heatmap is not None else "None")

print("Predicting different image...")
img3 = np.random.randint(0, 255, (256, 256, 3), dtype=np.uint8)
is_anom, score, heatmap = detector.predict(image=img3)
print(f"Is Anomaly: {is_anom}, Quality Score: {score}")
print("Heatmap max:", np.max(heatmap) if heatmap is not None else "None")
