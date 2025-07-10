# 3D random undersampled k-space maker for pe1_order = 5 extended non-regular LUT
#
# Gustav Strijkers
# g.j.strijkers@amsterdamumc.nl
# July 2025

import numpy as np
import matplotlib.pyplot as plt
from pathlib import Path

# User input
size_of_kspace = [256, 256]
size_of_center = [32, 32]
accel_factor = 8
elliptical_shutter = True
variable_density = 0.8
output_folder = Path("./output/")

show_mask = False
speed = 10000

# Split 32-bit to 2x 16-bit
def split32to16(int32_value):
    high16 = (int32_value >> 16) & 0xFFFF
    low16_unsigned = int32_value & 0xFFFF
    if low16_unsigned >= 2**15:
        low16 = low16_unsigned - 2**16
    else:
        low16 = low16_unsigned
    return low16, high16

# Unique weighted sampling
def weighted_sample_unique(N, w, k):
    w = np.array(w).flatten()
    w = w / np.sum(w)
    idx = []
    available = np.ones(N, dtype=bool)
    for _ in range(k):
        w_current = w.copy()
        w_current[~available] = 0
        w_current = w_current / np.sum(w_current)
        cdf = np.cumsum(w_current)
        r = np.random.rand()
        sel = np.searchsorted(cdf, r)
        idx.append(sel)
        available[sel] = False
    return np.array(idx)

# Poisson pattern generator
def poisson_pattern(SizeY, SizeZ, VariableDensity, AccelFactor, Elliptical,
                    RandSeed, CalibRegY, CalibRegZ):
    np.random.seed(RandSeed)
    N_full = SizeY * SizeZ
    cy, cz = (SizeY + 1) / 2, (SizeZ + 1) / 2
    Y, Z = np.meshgrid(np.arange(1, SizeY+1), np.arange(1, SizeZ+1))

    a, b = SizeY / 2, SizeZ / 2
    R2 = ((Y - cy)/a)**2 + ((Z - cz)/b)**2
    sample_mask = np.ones((SizeZ, SizeY), dtype=bool)
    if Elliptical:
        sample_mask = R2 <= 1

    mask_calib = np.zeros((SizeZ, SizeY), dtype=bool)
    if Elliptical:
        rY, rZ = CalibRegY / 2, CalibRegZ / 2
        R2_calib = ((Y - cy)/rY)**2 + ((Z - cz)/rZ)**2
        mask_calib = R2_calib <= 1
    else:
        y1 = round(cy - CalibRegY/2)
        y2 = round(cy + CalibRegY/2 - 1)
        z1 = round(cz - CalibRegZ/2)
        z2 = round(cz + CalibRegZ/2 - 1)
        mask_calib[z1-1:z2, y1-1:y2] = True
    mask_calib &= sample_mask

    if AccelFactor <= 1:
        mask = sample_mask.copy()
        mask[mask_calib] = True
        z, y = np.where(mask)
        samples = np.column_stack((y - SizeY//2 - 1, z - SizeZ//2 - 1))
        return mask, samples

    N_target_total = round(N_full / AccelFactor)
    N_calib = np.sum(mask_calib)
    N_random = N_target_total - N_calib

    n_available = np.sum(sample_mask & ~mask_calib)
    if N_random > n_available:
        N_random = n_available
        N_target_total = N_random + N_calib
        AccelFactor = N_full / N_target_total

    R = np.sqrt(R2)
    if VariableDensity > 0:
        vd = np.exp(-(R / 0.15) ** VariableDensity)
    else:
        vd = np.ones((SizeZ, SizeY))
    vd[~sample_mask | mask_calib] = 0
    vd = vd / np.sum(vd)

    validZ, validY = np.where(sample_mask & ~mask_calib)
    weights = vd[sample_mask & ~mask_calib]
    drawn_idx = weighted_sample_unique(len(weights), weights, N_random)
    subZ, subY = validZ[drawn_idx], validY[drawn_idx]

    mask = np.zeros((SizeZ, SizeY), dtype=bool)
    mask[subZ, subY] = True
    mask[mask_calib] = True

    z, y = np.where(mask)
    samples = np.column_stack((y - SizeY//2 - 1, z - SizeZ//2 - 1))
    return mask, samples

# Generate the mask and samples
mask, samples = poisson_pattern(
    SizeY=size_of_kspace[0],
    SizeZ=size_of_kspace[1],
    VariableDensity=variable_density,
    AccelFactor=accel_factor,
    Elliptical=elliptical_shutter,
    RandSeed=11235,
    CalibRegY=size_of_center[0],
    CalibRegZ=size_of_center[1]
)

AF = mask.size / np.count_nonzero(mask)
NE = samples.shape[0]

# Show mask
if show_mask:
    plt.figure(11)
    frame_mask = np.zeros_like(mask)
    img = plt.imshow(frame_mask, cmap='gray', vmin=0, vmax=1)
    plt.axis('off')
    plt.title([f'Effective acceleration factor = {AF:.2f}',
               f'Number of samples = {NE}'], fontsize=12)
    ky = samples[:, 0] + size_of_kspace[0] // 2 + 1
    kz = samples[:, 1] + size_of_kspace[1] // 2 + 1
    for k in range(NE):
        frame_mask[kz[k]-1, ky[k]-1] = True
        img.set_data(frame_mask)
        plt.pause(1 / speed)
    plt.show()

# Export LUT
output_folder.mkdir(parents=True, exist_ok=True)
shutter = 'E' if elliptical_shutter else 'S'
filename = output_folder / f"nrLUT_3D_R{AF:.2f}_M{size_of_kspace[0]}x{size_of_kspace[1]}{shutter}.txt"
with open(filename, 'w') as f:
    l16, h16 = split32to16(NE)
    f.write(f"{l16}\n{h16}\n")
    for s in samples:
        f.write(f"{int(s[0])}\n{int(s[1])}\n")

# Print k-space summary
print("\n------- k-space summary -------")
print(f"K-space size       : {size_of_kspace[0]} x {size_of_kspace[1]}")
print(f"Center region      : {size_of_center[0]} x {size_of_center[1]}")
print(f"Acceleration       : {AF:.2f}")
print(f"Elliptical shutter : {elliptical_shutter}")
print(f"Variable density   : {variable_density}")
print(f"Encodes (lines)    : {NE}")
print(f"Output file        : {filename}\n")
