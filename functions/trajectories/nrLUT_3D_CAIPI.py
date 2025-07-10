# 3D CAIPIRINHA-style undersampled k-space generator
#
# Gustav Strijkers
# g.j.strijkers@amsterdamumc.nl
# July 2025

import numpy as np
import matplotlib.pyplot as plt
from pathlib import Path

# User input
size_of_kspace = [128, 128]        # ky x kz
acs_size = [25, 25]                # Fully sampled ACS region [ky, kz]
Ry = 2                             # Undersampling factor in ky
Rz = 2                             # Undersampling factor in kz
output_folder = Path("./output/")  # Output folder
show_kspace = False                # Visualize mask (True/False)

# Ensure Ry and Rz are integers
Ry_orig, Rz_orig = Ry, Rz
Ry, Rz = round(Ry), round(Rz)
if Ry != Ry_orig:
    print(f'INFO: Ry rounded from {Ry_orig:.1f} to {Ry}.')
if Rz != Rz_orig:
    print(f'INFO: Rz rounded from {Rz_orig:.1f} to {Rz}.')

# CAIPIRINHA-style 3D pattern generator
def caipirinha3D_pattern(size_of_kspace, Ry, Rz, ACSdim):
    ky_dim, kz_dim = size_of_kspace
    mask = np.zeros((ky_dim, kz_dim), dtype=bool)

    cy = (ky_dim + 1) / 2
    cz = (kz_dim + 1) / 2
    y1 = round(cy - ACSdim[0] / 2)
    y2 = round(cy + ACSdim[0] / 2 - 1)
    z1 = round(cz - ACSdim[1] / 2)
    z2 = round(cz + ACSdim[1] / 2 - 1)

    mask[y1-1:y2, z1-1:z2] = True

    shift_count = 0
    for kz in range(1, kz_dim + 1):
        if (kz - 1) % Rz != 0:
            continue
        z_offset = shift_count % Ry
        shift_count += 1
        for ky in range(1, ky_dim + 1):
            if z1 <= kz <= z2 and y1 <= ky <= y2:
                continue
            if (ky - 1 - z_offset) % Ry == 0:
                mask[ky - 1, kz - 1] = True

    samples = []
    for ky in range(1, ky_dim + 1):
        for kz in range(1, kz_dim + 1):
            if mask[ky - 1, kz - 1]:
                samples.append([ky - (ky_dim // 2) - 1, kz - (kz_dim // 2) - 1])
    return mask, np.array(samples)

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

# Generate 3D CAIPIRINHA mask
mask, samples = caipirinha3D_pattern(size_of_kspace, Ry, Rz, acs_size)

# Summary
AF = mask.size / np.count_nonzero(mask)
NE = samples.shape[0]
file_name = output_folder / f"nrLUT_3D_CAIPI_R{AF:.2f}_{size_of_kspace[0]}x{size_of_kspace[1]}.txt"

print('\n------- CAIPIRINHA 3D k-space summary -------')
print(f'K-space size               : {size_of_kspace[0]} x {size_of_kspace[1]}')
print(f'ACS size                   : {acs_size[0]} x {acs_size[1]}')
print(f'Undersampling              : {Ry} x {Rz}')
print(f'Effective acceleration     : {AF:.2f}')
print(f'Encodes (lines)            : {NE}')
print(f'Output file                : {file_name}\n')

# Display a slice of the mask (optional)
if show_kspace:
    plt.figure()
    plt.imshow(mask, cmap='gray')
    plt.axis('off')
    plt.title(f'CAIPIRINHA 3D k-space \n R = {AF:.2f} \n N = {NE}', fontsize=14)
    plt.show()

# Export LUT
output_folder.mkdir(parents=True, exist_ok=True)
with open(file_name, 'w') as f:
    l16, h16 = split32to16(NE)
    f.write(f"{l16}\n")
    f.write(f"{h16}\n")
    for sample in samples:
        f.write(f"{int(sample[0])}\n")
        f.write(f"{int(sample[1])}\n")
