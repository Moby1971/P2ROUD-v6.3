# 2D undersampled k-space maker using Gaussian weighting and PSF selection
#
# Gustav Strijkers
# g.j.strijkers@amsterdamumc.nl
# June 2025
#

import numpy as np
import matplotlib.pyplot as plt
from pathlib import Path

# ---- User Input ----
size_of_kspace = (192, 192)
n_trials = 1000
size_of_center = 32
x_factor = 2.5
gauss_sigma = 0.15
output_folder = Path("./output/")
show_mask = True
speed = 100000

output_folder.mkdir(parents=True, exist_ok=True)


# ---- Helper Functions ----
def split32to16(val):
    val = np.int32(val)
    high16 = np.int16((val >> 16) & 0xFFFF)
    low16_unsigned = np.int16(val & 0xFFFF)
    if low16_unsigned >= 2**15:
        low16 = np.int16(low16_unsigned - 2**16)
    else:
        low16 = low16_unsigned
    return low16, high16


def weighted_sample_unique(domain, weights, k):
    weights = np.array(weights, dtype=float)
    weights /= np.sum(weights)
    idx = []
    available = np.ones(len(domain), dtype=bool)

    for _ in range(k):
        w_curr = weights * available
        w_curr /= np.sum(w_curr)
        cdf = np.cumsum(w_curr)
        r = np.random.rand()
        sel = np.searchsorted(cdf, r)
        idx.append(domain[sel])
        available[sel] = False

    return sorted(idx)


def line_based_pattern(size_ro, size_pe, accel_factor, center_lines, gauss_sigma):
    cy = (size_pe + 1) // 2
    n_total_lines = round(size_pe / accel_factor)

    y1 = round(cy - center_lines / 2)
    y2 = round(cy + center_lines / 2 - 1)
    center_lines_range = list(range(y1, y2 + 1))
    n_center = len(center_lines_range)

    if n_center > n_total_lines:
        raise ValueError("Center region too large for requested acceleration.")

    n_draw = n_total_lines - n_center
    all_lines = list(range(1, size_pe + 1))
    available_lines = list(set(all_lines) - set(center_lines_range))

    ky = np.arange(-size_pe // 2, size_pe // 2)
    sigma = gauss_sigma * size_pe
    w = np.exp(-0.5 * (ky / sigma) ** 2)
    w /= np.sum(w)
    w = w[np.array(available_lines) - 1]

    drawn_idx = weighted_sample_unique(available_lines, w, n_draw)
    selected_lines = sorted(center_lines_range + drawn_idx)

    mask = np.zeros((size_ro, size_pe), dtype=bool)
    for line in selected_lines:
        mask[:, line - 1] = True

    samples = np.array(selected_lines) - size_pe // 2 - 1
    samples = np.column_stack((samples, np.zeros(len(samples), dtype=int)))

    return mask, samples


# ---- Main Loop ----
best_score = np.inf
best_mask = None
best_samples = None
best_psf = None

for _ in range(n_trials):
    np.random.seed(None)  # reseed RNG
    mask, samples = line_based_pattern(
        size_of_kspace[0], size_of_kspace[1], x_factor,
        size_of_center, gauss_sigma
    )

    pe_profile = np.mean(mask, axis=0)
    psf = np.abs(np.fft.fftshift(np.fft.ifft(pe_profile)))

    main_lobe_width = np.sum(psf > 0.5 * np.max(psf))
    side_lobe_level = np.max(psf[psf < np.max(psf)])

    score = main_lobe_width + side_lobe_level
    if score < best_score:
        best_score = score
        best_mask = mask.copy()
        best_samples = samples.copy()
        best_psf = psf.copy()

mask = best_mask
samples = best_samples
AF = np.prod(mask.shape) / np.count_nonzero(mask)
NE = samples.shape[0]

# ---- Display ----
if show_mask:
    ky = np.unique(samples[:, 0])
    ky_idx = ky + size_of_kspace[1] // 2 + 1
    ky_idx = ky_idx[(ky_idx >= 1) & (ky_idx <= size_of_kspace[1])]

    fig, axs = plt.subplots(1, 2, figsize=(10, 5))
    frame_mask = np.zeros_like(mask, dtype=bool)
    img = axs[0].imshow(frame_mask, cmap='gray', vmin=0, vmax=1)
    axs[0].set_title(f"Mask\nR = {AF:.4f}\nN = {NE}", fontsize=14)
    axs[0].axis('off')

    for cnt in ky_idx:
        frame_mask[:, cnt - 1] = True
        img.set_data(frame_mask)
        plt.pause(1 / speed)

    axs[1].plot(best_psf, 'k-', linewidth=1.5)
    axs[1].set_title("Point Spread Function", fontsize=14)
    axs[1].set_xlabel("Pixel")
    axs[1].set_ylabel("Amplitude")
    axs[1].set_xlim([0, size_of_kspace[1]])
    axs[1].grid(True)

    plt.show()

# ---- Export LUT ----
filename = output_folder / f"NonReg2DLUT_R{AF:.2f}_{size_of_kspace[1]}.txt"
with open(filename, 'w') as f:
    l16, h16 = split32to16(NE)
    f.write(f"{l16}\n{h16}\n")
    for val in samples[:, 0]:
        f.write(f"{val}\n0\n")
