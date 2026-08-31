# 2D GRAPPA-style undersampled k-space mask generator
#
# Gustav Strijkers
# g.j.strijkers@amsterdamumc.nl
# July 2025

import numpy as np
import matplotlib.pyplot as plt
from pathlib import Path

# User input
size_of_kspace = [256, 256]         # RO x PE
number_of_ACS = 32                  # Number of ACS lines, must be even
R = 3                               # Acceleration factor
output_folder = Path("./output/")   # Output folder
show_kspace = False                 # Visualize mask
speed = 50                          # Display speed

# Ensure R is integer
R_orig = R
R = round(R)
if R != R_orig:
    print(f'INFO: R rounded from {R_orig:.1f} to {R}.')

# GRAPPA-style pattern generator
def grappa_pattern(SizeRO, SizePE, AccelFactor, CenterLines):
    cy = (SizePE + 1) / 2
    y1 = round(cy - CenterLines / 2)
    y2 = round(cy + CenterLines / 2 - 1)
    center_lines = np.arange(y1, y2 + 1)

    mask_lines = np.zeros(SizePE, dtype=bool)
    mask_lines[center_lines - 1] = True

    for k in range(1, SizePE + 1):
        if not mask_lines[k - 1] and (k - y1) % AccelFactor == 0:
            mask_lines[k - 1] = True

    mask = np.zeros((SizeRO, SizePE), dtype=bool)
    mask[:, mask_lines] = True

    selected_lines = np.where(mask_lines)[0]
    samples = selected_lines - (SizePE // 2)
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

# Generate GRAPPA mask
mask, samples = grappa_pattern(SizeRO=size_of_kspace[0],
                               SizePE=size_of_kspace[1],
                               AccelFactor=R,
                               CenterLines=number_of_ACS)

# Summary
AF = mask.size / np.count_nonzero(mask)
NE = samples.shape[0]

file_name = output_folder / f"nrLUT_2D_GRAPPA_R{AF:.2f}_{size_of_kspace[1]}.txt"

ky_min = int(samples[:, 0].min())
ky_max = int(samples[:, 0].max())


print('\n------- GRAPPA K-space summary -------')
print(f'K-space size               : {size_of_kspace[0]} x {size_of_kspace[1]}')
print(f'ACS lines                  : {number_of_ACS}')
print(f'Effective Acceleration     : {AF:.2f}')
print(f'Encodes (lines)            : {NE}')
print(f'ky range                   : {ky_min} to {ky_max}')
print(f'Output file                : {file_name}\n')

# Display mask
if show_kspace:
    import time
    plt.figure()
    frame_mask = np.zeros_like(mask)
    img = plt.imshow(frame_mask, cmap='gray', vmin=0, vmax=1)
    plt.axis('off')
    plt.title(f"GRAPPA Mask\nR = {AF:.4f}\nN = {NE}", fontsize=14)
    ky = np.unique(samples[:, 0])
    ky_idx = ky + size_of_kspace[1] // 2
    ky_idx = ky_idx[(ky_idx >= 0) & (ky_idx < size_of_kspace[1])]

    for idx in ky_idx:
        frame_mask[:, int(idx)] = True

        img.set_data(frame_mask)
        plt.pause(1 / speed)

    plt.show()

# Export LUT (kz = 0 always)
output_folder.mkdir(parents=True, exist_ok=True)
with open(file_name, 'w') as f:
    l16, h16 = split32to16(NE)
    f.write(f"{l16}\n")
    f.write(f"{h16}\n")
    for sample in samples:
        f.write(f"{int(sample[0])}\n")
        f.write("0\n")
