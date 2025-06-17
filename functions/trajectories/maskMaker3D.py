# 3D undersampled k-space maker for pe1_order = 5 extended non-regular LUT
#
# Gustav Strijkers
# g.j.strijkers@amsterdamumc.nl
# June 2025
#
#


import numpy as np
import matplotlib.pyplot as plt
import os

# User input

size_of_kspace = (128, 128)  # Size of k-space
size_of_center = (16, 16)    # Size of center-filled region
x_factor = 2                 # Acceleration factor
e_shutter = True             # Elliptical shutter
variable_density = 0.8       # Variable density
output_folder = "./output/"  # Output folder
show_mask = True             # Show the mask
speed = 10000                # Animation speed

os.makedirs(output_folder, exist_ok=True)

#%% Helper functions

def split32to16(int32_value):
    int32_value = np.int32(int32_value)
    high16 = np.int16(int32_value >> 16)
    low16_unsigned = np.int32(int32_value & 0xFFFF)
    low16 = np.int16(low16_unsigned - 2**16 if low16_unsigned >= 2**15 else low16_unsigned)
    return low16, high16

def weighted_sample_unique(N, w, k):
    w = w / np.sum(w)
    idx = np.zeros(k, dtype=int)
    avail = np.ones(N, dtype=bool)
    for cnt in range(k):
        w_curr = np.where(avail, w, 0)
        w_curr /= np.sum(w_curr)
        cdf = np.cumsum(w_curr)
        sel = np.searchsorted(cdf, np.random.rand(), side='right')
        idx[cnt] = sel
        avail[sel] = False
    return idx

def poisson_pattern(SizeY, SizeZ, VariableDensity, AccelFactor, Elliptical, CalibRegY, CalibRegZ, RandSeed=11235):
    np.random.seed(RandSeed)
    N_full = SizeY * SizeZ
    cy, cz = (SizeY + 1) / 2, (SizeZ + 1) / 2
    Y, Z = np.meshgrid(np.arange(1, SizeY + 1), np.arange(1, SizeZ + 1))
    a, b = SizeY / 2, SizeZ / 2
    R2 = ((Y - cy) / a)**2 + ((Z - cz) / b)**2

    sample_mask = np.ones((SizeZ, SizeY), dtype=bool)
    if Elliptical:
        sample_mask = R2 <= 1

    mask_calib = np.zeros((SizeZ, SizeY), dtype=bool)
    if Elliptical:
        rY, rZ = CalibRegY / 2, CalibRegZ / 2
        R2calib = ((Y - cy) / rY)**2 + ((Z - cz) / rZ)**2
        mask_calib = R2calib <= 1
    else:
        y1, y2 = round(cy - CalibRegY/2), round(cy + CalibRegY/2 - 1)
        z1, z2 = round(cz - CalibRegZ/2), round(cz + CalibRegZ/2 - 1)
        mask_calib[z1:z2+1, y1:y2+1] = True
    mask_calib &= sample_mask

    if AccelFactor <= 1:
        mask = sample_mask.copy()
        mask[mask_calib] = True
        z, y = np.where(mask)
        return mask, np.column_stack((y - SizeY // 2 - 1, z - SizeZ // 2 - 1))

    N_target_total = round(N_full / AccelFactor)
    N_calib = np.count_nonzero(mask_calib)
    N_random = N_target_total - N_calib
    n_available = np.count_nonzero(sample_mask & ~mask_calib)
    if N_random > n_available:
        N_random = n_available
        N_target_total = N_random + N_calib

    R = np.sqrt(R2)
    vd = np.exp(-(R / 0.15)**VariableDensity) if VariableDensity > 0 else np.ones((SizeZ, SizeY))
    vd[~sample_mask | mask_calib] = 0
    vd /= np.sum(vd)

    validZ, validY = np.where(sample_mask & ~mask_calib)
    weights = vd[sample_mask & ~mask_calib]
    drawn = weighted_sample_unique(len(weights), weights, N_random)
    subZ, subY = validZ[drawn], validY[drawn]

    mask = np.zeros((SizeZ, SizeY), dtype=bool)
    mask[subZ, subY] = True
    mask[mask_calib] = True

    z, y = np.where(mask)
    return mask, np.column_stack((y - SizeY // 2 - 1, z - SizeZ // 2 - 1))

#%% Generate the mask and samples

mask, samples = poisson_pattern(
    SizeY=size_of_kspace[0], SizeZ=size_of_kspace[1],
    VariableDensity=variable_density, AccelFactor=x_factor,
    Elliptical=e_shutter, CalibRegY=size_of_center[0],
    CalibRegZ=size_of_center[1]
)

AF = mask.size / np.count_nonzero(mask)
NE = np.count_nonzero(mask)

#%% Show mask

if show_mask:
    plt.figure(11)
    frame_mask = np.zeros_like(mask, dtype=bool)
    img = plt.imshow(frame_mask, cmap='gray', vmin=0, vmax=1)
    plt.axis('off')
    plt.axis('image')
    plt.title(f"Effective acceleration factor = {AF:.4f}\nNumber of samples = {NE}", fontsize=20)

    ky = samples[:, 0] + size_of_kspace[0] // 2 + 1
    kz = samples[:, 1] + size_of_kspace[1] // 2 + 1

    for cnt in range(NE):
        frame_mask[kz[cnt], ky[cnt]] = True
        img.set_data(frame_mask)
        plt.pause(1/speed)

    plt.show()

#%% Export to LUT

shutter = 'E' if e_shutter else 'S'
filename = os.path.join(
    output_folder, f"NonRegLUT_R{AF:.2f}_M{size_of_kspace[0]}x{size_of_kspace[1]}{shutter}.txt"
)

with open(filename, 'w') as f:
    l16, h16 = split32to16(NE)
    f.write(f"{l16}\n{h16}\n")
    for ky, kz in samples:
        f.write(f"{ky}\n{kz}\n")
