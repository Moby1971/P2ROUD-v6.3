# 2D undersampled k-space maker using Gaussian weighting and PSF selection
#
# Gustav Strijkers
# g.j.strijkers@amsterdamumc.nl
# July 2025

import numpy as np
import matplotlib.pyplot as plt
from pathlib import Path

# User input
size_of_kspace = [256, 256]     # RO x PE
n_trials = 1000                 # Number of mask trials
center_lines = 32               # Number of center-filled lines
accel_factor = 2.5              # Acceleration factor
gauss_sigma = 0.15              # Gaussian std-dev (fraction of PE size)
output_folder = Path("./output/")
show_kspace = False
speed = 100000

# Weighted sampling helper
def weighted_sample_unique(domain, weights, k):
    weights = np.array(weights)
    weights = weights / np.sum(weights)
    idx = []
    available = np.ones(len(domain), dtype=bool)
    for _ in range(k):
        w = weights.copy()
        w[~available] = 0
        w = w / np.sum(w)
        cdf = np.cumsum(w)
        r = np.random.rand()
        sel = np.searchsorted(cdf, r)
        idx.append(domain[sel])
        available[sel] = False
    return np.array(idx)

# Generate a line-based undersampling pattern
def line_based_pattern(SizeRO, SizePE, AccelFactor, CenterLines, GaussSigma):
    cy = (SizePE + 1) / 2
    N_total_lines = round(SizePE / AccelFactor)
    y1 = round(cy - CenterLines / 2)
    y2 = round(cy + CenterLines / 2 - 1)
    center_lines = np.arange(y1, y2 + 1)
    N_center = len(center_lines)

    if N_center > N_total_lines:
        raise ValueError("Center region too large for requested acceleration.")

    N_draw = N_total_lines - N_center
    all_lines = np.arange(1, SizePE + 1)
    available_lines = np.setdiff1d(all_lines, center_lines)

    ky = np.arange(-SizePE / 2, SizePE / 2)
    sigma = GaussSigma * SizePE
    w = np.exp(-0.5 * (ky / sigma) ** 2)
    w = w / np.sum(w)
    w = w[available_lines - 1]

    drawn_idx = weighted_sample_unique(available_lines, w, N_draw)
    selected_lines = np.sort(np.concatenate([center_lines, drawn_idx]))

    mask = np.zeros((SizeRO, SizePE), dtype=bool)
    mask[:, selected_lines - 1] = True
    samples = selected_lines - SizePE // 2 - 1
    samples = np.column_stack((samples, np.zeros_like(samples)))
    return mask, samples

# Split 32-bit to 2x 16-bit
def split32to16(int32_value):
    int32_value = int(int32_value)
    high16 = (int32_value >> 16) & 0xFFFF
    low16_unsigned = int32_value & 0xFFFF
    if low16_unsigned >= 2**15:
        low16 = low16_unsigned - 2**16
    else:
        low16 = low16_unsigned
    return low16, high16

# Main mask selection loop
best_score = float('inf')
best_mask = None
best_samples = None
best_psf = None

for _ in range(n_trials):
    np.random.seed()
    mask, samples = line_based_pattern(size_of_kspace[0], size_of_kspace[1],
                                       accel_factor, center_lines, gauss_sigma)
    pe_profile = mask.mean(axis=0)
    psf = np.abs(np.fft.fftshift(np.fft.ifft(pe_profile)))

    main_lobe_width = np.sum(psf > 0.5 * np.max(psf))
    side_lobe_level = np.max(psf[psf < np.max(psf)])
    score = main_lobe_width + side_lobe_level

    if score < best_score:
        best_score = score
        best_mask = mask
        best_samples = samples
        best_psf = psf

# Final selection
mask = best_mask
samples = best_samples

AF = mask.size / np.count_nonzero(mask)
NE = samples.shape[0]

# Display
if show_kspace:
    import time
    plt.figure(12)
    plt.clf()

    plt.subplot(1, 2, 1)
    frame_mask = np.zeros_like(mask)
    img = plt.imshow(frame_mask, cmap='gray', vmin=0, vmax=1)
    plt.axis('off')
    plt.title(f'Mask\nR = {AF:.4f}\nN = {NE}', fontsize=14)

    ky = np.unique(samples[:, 0])
    ky_idx = ky + size_of_kspace[1] // 2
    ky_idx = ky_idx[(ky_idx >= 0) & (ky_idx < size_of_kspace[1])]

    for k in ky_idx:
        frame_mask[:, int(k)] = True

        img.set_data(frame_mask)
        plt.pause(1 / speed)

    plt.subplot(1, 2, 2)
    plt.plot(best_psf, 'k-', linewidth=1.5)
    plt.title('Point Spread Function', fontsize=14)
    plt.xlabel('Pixel')
    plt.ylabel('Amplitude')
    plt.grid(True)
    plt.xlim([0, size_of_kspace[1]])
    plt.show()

# Export LUT
output_folder.mkdir(parents=True, exist_ok=True)
filename = output_folder / f"nrLUT_2D_R{AF:.2f}_{size_of_kspace[1]}.txt"
with open(filename, 'w') as f:
    l16, h16 = split32to16(NE)
    f.write(f"{l16}\n{h16}\n")
    for sample in samples:
        f.write(f"{int(sample[0])}\n0\n")

ky_min = int(samples[:, 0].min())
ky_max = int(samples[:, 0].max())

# Summary
print('\n------- k-space summary -------')
print(f'K-space size       : {size_of_kspace[0]} x {size_of_kspace[1]}')
print(f'Center lines       : {center_lines}')
print(f'Acceleration       : {AF:.2f}')
print(f'Encodes (lines)    : {NE}')
print(f'ky range           : {ky_min} to {ky_max}')
print(f'Gaussian sigma     : {gauss_sigma:.2f} ({100 * gauss_sigma:.1f}% of PE size)')
print(f'Trials run         : {n_trials}')
print(f'Best score         : {best_score:.3f}')
print(f'Output file        : {filename}\n')
