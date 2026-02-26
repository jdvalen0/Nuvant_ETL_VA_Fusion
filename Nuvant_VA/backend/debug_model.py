import joblib
import numpy as np
from pathlib import Path
import os

storage = Path("/home/juan-david-valencia/Escritorio/Nuvant_ETL_VA_Fusion/Nuvant_VA/backend/api/static/storage")
refs = list(storage.glob("*"))

for ref in refs:
    model_path = ref / "model.pkl"
    if model_path.exists():
        try:
            m = joblib.load(model_path)
            print(f"Ref {ref.name}:")
            print(f"  Version: {m.get('version')}")
            print(f"  Threshold: {m.get('threshold')}")
            print(f"  Memory Bank shape: {m.get('memory_bank').shape}")
            if "train_dists" in m:
                pass
        except Exception as e:
            print(f"Error loading {ref}: {e}")
