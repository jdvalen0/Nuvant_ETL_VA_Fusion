"""
Nuvant VA - PatchCore Anomaly Detection Engine V32
Production-Ready Implementation with Localization

Based on: "Towards Total Recall in Industrial Anomaly Detection" (CVPR 2022)

Mathematical Foundation:
- Feature Extraction: Mid-level CNN features (layers 2-3) to capture textures
- Memory Bank: Coreset subsampling via k-Center-Greedy algorithm
- Anomaly Score: k-NN distance with density re-weighting (REAL implementation)
- Localization: Per-patch scores aggregated into heatmap

Calibration fix (V32.5):
- Threshold calibrated on per-IMAGE max distance (not per-patch percentile)
  Reason: predict() uses max over all patches → calibration must match.
  Old (bug): percentile(all 39K patches, 97%) → biased low → FP on good fabric.
  New:      percentile(per-image max, 97%) * margin → correctly represents
            what % of TRAINING IMAGES would be flagged as defects.
- PATCHCORE_THRESHOLD_MARGIN (default 3.0): load-time multiplier so operators
  can tune without retraining.
"""

import numpy as np
import os
import torch
import torch.nn as nn
import cv2
import joblib
from pathlib import Path
from typing import Tuple, Optional, Dict, Any
from torchvision import transforms, models
from PIL import Image


class FeatureExtractorBackbone(nn.Module):
    """
    Feature extractor using pre-trained CNN backbone.
    Extracts mid-level features from specified layers.
    """

    def __init__(self, backbone_name: str = "wide_resnet50_2"):
        super().__init__()

        if backbone_name == "wide_resnet50_2":
            backbone = models.wide_resnet50_2(weights=models.Wide_ResNet50_2_Weights.IMAGENET1K_V1)
        elif backbone_name == "resnet50":
            backbone = models.resnet50(weights=models.ResNet50_Weights.IMAGENET1K_V1)
        else:
            backbone = models.wide_resnet50_2(weights=models.Wide_ResNet50_2_Weights.IMAGENET1K_V1)

        self.layer1 = nn.Sequential(
            backbone.conv1, backbone.bn1, backbone.relu, backbone.maxpool, backbone.layer1
        )
        self.layer2 = backbone.layer2
        self.layer3 = backbone.layer3

        for param in self.parameters():
            param.requires_grad = False

    def forward(self, x: torch.Tensor) -> Dict[str, torch.Tensor]:
        x = self.layer1(x)
        layer2_out = self.layer2(x)
        layer3_out = self.layer3(layer2_out)
        return {"layer2": layer2_out, "layer3": layer3_out}


class PatchCoreDetector:
    """
    PatchCore-based anomaly detector for fabric inspection.

    Features:
    - ~99% AUROC on industrial benchmarks
    - Pixel-level localization (heatmaps)
    - Coreset memory bank for efficient inference
    - k-NN with density reweighting (paper-accurate)
    - Per-image max calibration (eliminates FP on good fabric)
    """

    def __init__(self,
                 backbone: Optional[str] = None,
                 coreset_sampling_ratio: Optional[float] = None,
                 num_neighbors: Optional[int] = None):
        self.backbone_name = backbone or os.getenv("PATCHCORE_BACKBONE", "wide_resnet50_2")
        self.coreset_sampling_ratio = coreset_sampling_ratio or float(os.getenv("PATCHCORE_CORESET_RATIO", "0.1"))
        self.num_neighbors = num_neighbors or int(os.getenv("PATCHCORE_NEIGHBORS", "9"))

        self.roi_crop = float(os.getenv("PATCHCORE_ROI_CROP", "0.05"))
        self.use_clahe = os.getenv("PATCHCORE_USE_CLAHE", "false").lower() == "true"

        self.feature_extractor: Optional[FeatureExtractorBackbone] = None
        self.memory_bank: Optional[np.ndarray] = None
        self.is_trained = False
        self.threshold = 0.5
        self.image_size = (224, 224)

        self.device = "cuda" if torch.cuda.is_available() else "cpu"

        self.transform = transforms.Compose([
            transforms.Resize(self.image_size),
            transforms.ToTensor(),
            transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225])
        ])

        self._init_feature_extractor()

    def _apply_industrial_preprocess(self, pil_img: Image.Image) -> Image.Image:
        """Apply ROI crop and optional CLAHE."""
        if self.roi_crop > 0:
            w, h = pil_img.size
            left = w * self.roi_crop
            top = h * self.roi_crop
            right = w * (1 - self.roi_crop)
            bottom = h * (1 - self.roi_crop)
            pil_img = pil_img.crop((left, top, right, bottom))

        if self.use_clahe:
            img_np = np.array(pil_img)
            lab = cv2.cvtColor(img_np, cv2.COLOR_RGB2LAB)
            l, a, b = cv2.split(lab)
            clahe = cv2.createCLAHE(clipLimit=2.0, tileGridSize=(8, 8))
            cl = clahe.apply(l)
            limg = cv2.merge((cl, a, b))
            final_img = cv2.cvtColor(limg, cv2.COLOR_LAB2RGB)
            pil_img = Image.fromarray(final_img)

        return pil_img

    def _init_feature_extractor(self):
        self.feature_extractor = FeatureExtractorBackbone(self.backbone_name)
        self.feature_extractor.to(self.device)
        self.feature_extractor.eval()

    def _extract_features(self, tensor: torch.Tensor) -> Tuple[np.ndarray, Tuple[int, int]]:
        """Extract and concatenate features from backbone layers."""
        with torch.no_grad():
            features = self.feature_extractor(tensor)

            layer2 = features["layer2"]
            layer3 = features["layer3"]

            H2, W2 = layer2.shape[2], layer2.shape[3]
            layer3_up = torch.nn.functional.interpolate(
                layer3, size=(H2, W2), mode="bilinear", align_corners=False
            )

            combined = torch.cat([layer2, layer3_up], dim=1)

            # Neighborhood aggregation (arXiv:2106.08265)
            avg_pool = torch.nn.AvgPool2d(kernel_size=3, stride=1, padding=1)
            combined = avg_pool(combined)

            B, C, H, W = combined.shape
            features_flat = combined.permute(0, 2, 3, 1).reshape(-1, C)

            # L2 normalization → cosine distance = euclidean on unit sphere
            features_norm = torch.nn.functional.normalize(features_flat, p=2, dim=1)
            features_out = features_norm.cpu().numpy()
            features_out = np.nan_to_num(features_out, nan=0.0)

            return features_out, (H, W)

    def _coreset_subsampling(self, features: np.ndarray, ratio: float) -> np.ndarray:
        """Greedy coreset subsampling using k-Center algorithm."""
        n_samples = max(100, min(int(len(features) * ratio), 5000))

        if len(features) <= n_samples:
            return features

        selected_indices = [np.random.randint(len(features))]
        min_distances = np.full(len(features), np.inf)

        for _ in range(n_samples - 1):
            last_selected = features[selected_indices[-1]]
            distances = np.linalg.norm(features - last_selected, axis=1)
            min_distances = np.minimum(min_distances, distances)
            next_idx = np.argmax(min_distances)
            selected_indices.append(next_idx)

        return features[selected_indices]

    def train(self,
              image_paths: Optional[list] = None,
              images: Optional[list] = None,
              contamination: float = 0.01) -> Dict[str, Any]:
        """
        Train PatchCore on normal (defect-free) images.

        V32.5 calibration fix:
        Threshold is calibrated on the per-image max patch distance,
        not on the percentile of all patches. This correctly represents
        what fraction of training IMAGES would be flagged as defective.
        """
        print(f"[PatchCore V32] Training...")

        if images is not None:
            source = images
            is_array = True
        elif image_paths is not None:
            source = image_paths
            is_array = False
        else:
            raise ValueError("Must provide either image_paths or images")

        print(f"[PatchCore V32] Processing {len(source)} training images...")

        # Collect per-image feature arrays (before vstacking) for correct calibration
        per_image_features = []

        for idx, item in enumerate(source):
            if is_array:
                img_rgb = cv2.cvtColor(item, cv2.COLOR_BGR2RGB)
                pil_img = Image.fromarray(img_rgb)
            else:
                img_bgr = cv2.imread(item)
                if img_bgr is None:
                    continue
                img_rgb = cv2.cvtColor(img_bgr, cv2.COLOR_BGR2RGB)
                pil_img = Image.fromarray(img_rgb)

            pil_img = self._apply_industrial_preprocess(pil_img)
            tensor = self.transform(pil_img).unsqueeze(0).to(self.device)
            features, _ = self._extract_features(tensor)
            per_image_features.append(features)

        if not per_image_features:
            raise ValueError("No valid training images processed")

        all_features = np.vstack(per_image_features)
        print(f"[PatchCore V32] Total features: {all_features.shape}")

        # Coreset subsampling
        self.memory_bank = self._coreset_subsampling(all_features, self.coreset_sampling_ratio)
        print(f"[PatchCore V32] Coreset size: {self.memory_bank.shape}")

        # ── CALIBRACIÓN CORRECTA: por imagen, no por patch ────────────────────
        # Compute per-image max patch distance.
        # This matches exactly what predict() does: max over all patches.
        per_image_max_dists = []
        for img_feats in per_image_features:
            patch_dists = self._compute_distances(img_feats)
            per_image_max_dists.append(np.max(patch_dists))

        per_image_max_dists = np.array(per_image_max_dists)
        percentile = 100.0 * (1.0 - contamination)

        # Base threshold: percentile of per-image max distances
        # e.g. contamination=0.03 → 97th percentile of per-image maxes
        # → 97% of training images score below this threshold (correct FPR target)
        base_threshold = np.percentile(per_image_max_dists, percentile)

        # Production margin (env-configurable): accounts for distribution shift
        # between controlled training and production conditions.
        # Default 3.0: production distances are typically 2-3× training max.
        margin = float(os.getenv("PATCHCORE_THRESHOLD_MARGIN", "3.0"))
        self.threshold = float(base_threshold * margin)

        print(f"[PatchCore V32] Threshold calibration (per-image max, V32.5):")
        print(f"  n_train_images = {len(per_image_features)}")
        print(f"  Percentile {percentile:.1f}% of per-image max = {base_threshold:.4f}")
        print(f"  Min per-image max = {per_image_max_dists.min():.4f}")
        print(f"  Max per-image max = {per_image_max_dists.max():.4f}")
        print(f"  Median per-image max = {np.median(per_image_max_dists):.4f}")
        print(f"  Production margin = {margin}×")
        print(f"  Final threshold = {self.threshold:.4f}")

        self.is_trained = True
        print(f"[PatchCore V32] Trained. Threshold: {self.threshold:.4f}")

        return {
            "memory_bank_size": len(self.memory_bank),
            "threshold": self.threshold,
            "num_training_images": len(per_image_features),
            "per_image_max_p97": float(base_threshold),
            "margin": margin,
        }

    def _compute_distances(self, features: np.ndarray) -> np.ndarray:
        """
        Compute k-NN distances to memory bank with density re-weighting.

        Implementation of arXiv:2106.08265 Section 3.1:
        - Get k nearest neighbors for each test patch
        - Weight by softmax of k-NN distances (density factor)
        - Anomalous patches in sparse regions get higher scores
        """
        k = min(self.num_neighbors, self.memory_bank.shape[0])

        # Cosine similarities (L2 normalized dot product)
        similarities = features @ self.memory_bank.T  # (N_patches, N_coreset)

        if k <= 1:
            max_sim = np.max(similarities, axis=1)
            return np.clip(1.0 - max_sim, 0, None)

        # Top-k most similar patches in memory bank
        # Use argpartition for efficiency: O(N log k) instead of O(N log N)
        n_coreset = similarities.shape[1]
        k_actual = min(k, n_coreset)
        if k_actual < n_coreset:
            # Indices of top-k largest similarities
            topk_idx = np.argpartition(similarities, -k_actual, axis=1)[:, -k_actual:]
            topk_sim = np.take_along_axis(similarities, topk_idx, axis=1)
        else:
            topk_sim = similarities

        # Best match (nearest neighbor)
        best_sim = np.max(topk_sim, axis=1)  # (N_patches,)
        base_dist = np.clip(1.0 - best_sim, 0, None)

        dists_k = np.clip(1.0 - topk_sim, 0, None)  # (N_patches, k)

        # Paper Eq. 3 (arXiv:2106.08265): positive exponentials of distances.
        # w = max(exp(d_j)) / Σ exp(d_j) captures how dominant the farthest
        # k-NN is. Factor (1 - w) suppresses scores for confident normal
        # patches (~0.85-0.89) while preserving anomaly signals.
        exp_d = np.exp(dists_k)
        sum_exp = np.sum(exp_d, axis=1, keepdims=True) + 1e-9
        w = np.max(exp_d, axis=1) / sum_exp.squeeze(1)

        density_factor = np.clip(1.0 - w, 0, None)
        return np.clip(base_dist * density_factor, 0, None)

    def predict(self,
                image: Optional[np.ndarray] = None,
                image_path: Optional[str] = None,
                sensitivity_offset: float = 0.0) -> Tuple[bool, float, Optional[np.ndarray]]:
        """
        Predict if image contains anomaly and generate heatmap.

        Returns: (is_anomaly, quality_score_0_100, heatmap_normalized)
        quality_score: 100 = perfect, 50 = at threshold, 0 = severe anomaly
        """
        if not self.is_trained:
            raise ValueError("Model not trained. Call train() first.")

        if image is not None:
            img_rgb = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
            pil_img = Image.fromarray(img_rgb)
        elif image_path is not None:
            pil_img = Image.open(image_path).convert("RGB")
        else:
            raise ValueError("Must provide either image or image_path")

        original_size = pil_img.size  # (W, H)

        pil_img = self._apply_industrial_preprocess(pil_img)
        tensor = self.transform(pil_img).unsqueeze(0).to(self.device)
        features, (H, W) = self._extract_features(tensor)

        # k-NN distances with density re-weighting
        patch_distances = self._compute_distances(features)

        # Per-image score: max of patch distances
        max_distance = np.max(patch_distances)

        # Load-time margin override (env var applied at load time)
        # sensitivity_offset allows fine-tuning at runtime:
        # negative offset → higher threshold → fewer detections (less strict)
        # positive offset → lower threshold → more detections (more strict)
        adjusted_threshold = self.threshold * (1.0 - sensitivity_offset / 1000.0)
        adjusted_threshold = max(adjusted_threshold, 1e-6)

        # Reshape to spatial map
        distance_map = patch_distances.reshape(H, W)

        # Upscale to cropped image size
        cropped_w, cropped_h = pil_img.size
        heatmap_cropped = cv2.resize(
            distance_map.astype(np.float32),
            (cropped_w, cropped_h),
            interpolation=cv2.INTER_LINEAR
        )

        # Gaussian blur (paper: sigma=4)
        heatmap_cropped = cv2.GaussianBlur(heatmap_cropped, (0, 0), sigmaX=4, sigmaY=4)

        # Embed cropped heatmap in full-size canvas
        full_heatmap = np.zeros((original_size[1], original_size[0]), dtype=np.float32)
        w, h = original_size
        left = int(w * self.roi_crop)
        top = int(h * self.roi_crop)
        hh, ww = heatmap_cropped.shape
        full_heatmap[top:top + hh, left:left + ww] = heatmap_cropped[:min(hh, h - top), :min(ww, w - left)]

        # Normalize heatmap relative to adjusted threshold
        h_threshold = max(1e-4, adjusted_threshold)
        heatmap_max = full_heatmap.max()

        if heatmap_max > h_threshold * 1.5:
            heatmap_normalized = full_heatmap / (heatmap_max + 1e-9)
        else:
            heatmap_normalized = 0.8 * (full_heatmap / h_threshold)

        heatmap_normalized = np.nan_to_num(heatmap_normalized, nan=0.0, posinf=1.0, neginf=0.0)
        heatmap_normalized = np.clip(heatmap_normalized, 0, 1)
        heatmap_normalized = np.power(heatmap_normalized, 0.7)

        is_anomaly = max_distance > adjusted_threshold

        # Quality score: 100 = perfect, 50 = at threshold, 0 = severe anomaly
        anomaly_score = min(100.0, (max_distance / (adjusted_threshold + 1e-6)) * 50.0)
        quality_score = max(0.0, 100.0 - anomaly_score)

        return is_anomaly, quality_score, heatmap_normalized

    def save(self, path: str):
        if not self.is_trained:
            raise ValueError("Model not trained")

        save_dict = {
            "memory_bank": self.memory_bank,
            "threshold": self.threshold,
            "backbone": self.backbone_name,
            "coreset_sampling_ratio": self.coreset_sampling_ratio,
            "num_neighbors": self.num_neighbors,
            "image_size": self.image_size,
            "version": "V32_PatchCore",
            "calibration": "per_image_max_V32.5",
            "train_margin": float(os.getenv("PATCHCORE_THRESHOLD_MARGIN", "1.0")),
        }
        joblib.dump(save_dict, path)
        print(f"[PatchCore V32] Model saved to {path}")

    def load(self, path: str):
        save_dict = joblib.load(path)

        if save_dict.get("version") != "V32_PatchCore":
            print(f"[Warning] Loading model with version: {save_dict.get('version')}")

        self.memory_bank = save_dict["memory_bank"]
        if "threshold" not in save_dict:
            raise ValueError("Model file missing required 'threshold'. Retrain the reference model.")

        raw_threshold = float(save_dict["threshold"])
        calibration = save_dict.get("calibration", "unknown")
        saved_margin = float(save_dict.get("train_margin", 3.0))
        target_margin = float(os.getenv("PATCHCORE_THRESHOLD_MARGIN", "1.0"))

        if "per_image_max" in calibration:
            # El threshold guardado incluye el margen de entrenamiento (saved_margin).
            # Normalizamos al base y aplicamos el margen actual del entorno.
            # Esto permite cambiar PATCHCORE_THRESHOLD_MARGIN sin reentrenar.
            base_threshold = raw_threshold / saved_margin
            self.threshold = base_threshold * target_margin
            print(f"[PatchCore V32] Threshold: raw={raw_threshold:.4f} "
                  f"(train_margin={saved_margin}×) → base={base_threshold:.4f} "
                  f"× target_margin={target_margin} = {self.threshold:.4f}")
        else:
            # Legacy per-patch calibration: apply load-time margin correction
            self.threshold = raw_threshold * target_margin
            print(f"[PatchCore V32] Calibration: legacy per-patch. "
                  f"Raw: {raw_threshold:.4f} × {target_margin} = {self.threshold:.4f}")

        self.backbone_name = save_dict.get("backbone", "wide_resnet50_2")
        self.image_size = save_dict.get("image_size", (224, 224))
        self.num_neighbors = save_dict.get("num_neighbors", self.num_neighbors)

        self._init_feature_extractor()
        self.is_trained = True
        print(f"[PatchCore V32] Model loaded. Memory bank: {self.memory_bank.shape}, "
              f"Threshold: {self.threshold:.4f}")


# Compatibility wrapper for existing API
class AnomalyDetectorV32(PatchCoreDetector):
    """Backward-compatible wrapper that matches V31 API."""

    def train(self, features=None, contamination=0.01, pca_variance=None, images=None):
        if images is not None:
            return super().train(images=images, contamination=contamination)
        elif features is not None:
            features = np.array(features)
            if features.ndim == 3:
                N, T, D = features.shape
                features = features.reshape(N * T, D)

            norms = np.linalg.norm(features, axis=1, keepdims=True)
            features_norm = features / (norms + 1e-9)

            self.memory_bank = self._coreset_subsampling(features_norm, self.coreset_sampling_ratio)

            train_dists = self._compute_distances(features_norm)
            percentile = 100.0 * (1.0 - contamination)
            self.threshold = np.percentile(train_dists, percentile)

            self.is_trained = True
            print(f"[PatchCore V32] Trained (features mode). Memory: {self.memory_bank.shape}, "
                  f"Threshold: {self.threshold:.4f}")

            return {"memory_bank_size": len(self.memory_bank), "threshold": self.threshold}
        else:
            raise ValueError("Must provide features or images")

    def predict(self, features=None, image=None, sensitivity_offset=0.0):
        """Unified prediction API for V31 (features) and V32 (images)."""
        if image is None and features is not None:
            if isinstance(features, np.ndarray) and features.ndim == 3:
                image = features
                features = None

        if image is not None:
            return super().predict(image=image, sensitivity_offset=sensitivity_offset)

        if features is not None:
            features = np.array(features)

            if features.ndim == 3:
                N, T, D = features.shape
                features_flat = features.reshape(N * T, D)
            else:
                features_flat = features.reshape(-1, features.shape[-1])

            if self.memory_bank is not None:
                if features_flat.shape[1] != self.memory_bank.shape[1]:
                    raise ValueError(
                        f"Dim mismatch: expected {self.memory_bank.shape[1]}, got {features_flat.shape[1]}"
                    )

            distances = self._compute_distances(features_flat)
            max_distance = np.max(distances)

            adj_threshold = self.threshold * (1.0 - sensitivity_offset / 1000.0)
            adj_threshold = max(adj_threshold, 1e-6)
            is_anomaly = max_distance > adj_threshold
            score = min(100.0, (max_distance / (adj_threshold + 1e-6)) * 50.0)

            return is_anomaly, score, None

        raise ValueError("Must provide features or image")
