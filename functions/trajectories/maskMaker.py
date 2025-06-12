
# 3D undersampled k-space maker for pe1_order = 5 extended non-regular LUT
# Gustav Strijkers, June 2025

import numpy as np
import matplotlib.pyplot as plt
import os

# ---- User input ----
sizeOfKspace = (128, 128)
sizeOfCenter = (16, 16)
xFactor = 4
eShutter = True
variableDensity = 0.8
outputFolder = "./output/"
showMask = True
speed = 1000

# ---- Helper functions ----

def split32to16(value):
    value = np.int32(value)
    high16 = np.int16((value >> 16) & 0xFFFF)
    low16_unsigned = value & 0xFFFF
    if low16_unsigned >= 2**15:
        low16 = np.int16(low16_unsigned - 2**16)
    else:
        low16 = np.int16(low16_unsigned)
    return low16, high16


def weighted_sample_unique(weights, k, seed=None):
    rng = np.random.default_rng(seed)
    weights = np.array(weights, dtype=np.float64)
    weights /= weights.sum()
    indices = np.arange(len(weights))
    chosen = []
    avail = np.ones(len(weights), dtype=bool)

    for _ in range(k):
        w = np.where(avail, weights, 0)
        w /= w.sum()
        sel = rng.choice(indices, p=w)
        chosen.append(sel)
        avail[sel] = False

    return np.array(chosen)


def poissonPattern(SizeY=128, SizeZ=128, VariableDensity=0.8, AccelFactor=2,
                   Elliptical=False, RandSeed=11235, CalibRegY=16, CalibRegZ=16):
    rng = np.random.default_rng(RandSeed)
    N_full = SizeY * SizeZ
    cy, cz = (SizeY + 1) / 2, (SizeZ + 1) / 2
    Y, Z = np.meshgrid(np.arange(1, SizeY+1), np.arange(1, SizeZ+1))

    # Elliptical shutter
    a, b = SizeY / 2, SizeZ / 2
    R2 = ((Y - cy) / a)**2 + ((Z - cz) / b)**2
    sampleMask = R2 <= 1 if Elliptical else np.ones_like(R2, dtype=bool)

    # Calibration region
    maskCalib = np.zeros_like(sampleMask, dtype=bool)
    if Elliptical:
        rY, rZ = CalibRegY / 2, CalibRegZ / 2
        R2calib = ((Y - cy) / rY)**2 + ((Z - cz) / rZ)**2
        maskCalib = R2calib <= 1
    else:
        y1 = int(round(cy - CalibRegY / 2))
        y2 = int(round(cy + CalibRegY / 2 - 1))
        z1 = int(round(cz - CalibRegZ / 2))
        z2 = int(round(cz + CalibRegZ / 2 - 1))
        maskCalib[z1-1:z2, y1-1:y2] = True
    maskCalib &= sampleMask

    # Special case: full sampling
    if AccelFactor <= 1:
        mask = sampleMask.copy()
        mask[maskCalib] = True
        z, y = np.where(mask)
        samples = np.stack((y - SizeY // 2 - 1, z - SizeZ // 2 - 1), axis=-1)
        return mask, samples

    N_target_total = round(N_full / AccelFactor)
    N_calib = np.count_nonzero(maskCalib)
    N_random = N_target_total - N_calib

    n_available = np.count_nonzero(sampleMask & ~maskCalib)
    if N_random > n_available:
        N_random = n_available
        N_target_total = N_random + N_calib
        AccelFactor = N_full / N_target_total

    # Variable density
    R = np.sqrt(R2)
    if VariableDensity > 0:
        vd = np.exp(-(R / 0.15) ** VariableDensity)
    else:
        vd = np.ones_like(R)
    vd[~sampleMask | maskCalib] = 0
    vd /= vd.sum()

    validZ, validY = np.where(sampleMask & ~maskCalib)
    weights = vd[sampleMask & ~maskCalib]
    drawn = weighted_sample_unique(weights, N_random, seed=RandSeed)
    subZ, subY = validZ[drawn], validY[drawn]

    mask = np.zeros_like(sampleMask, dtype=bool)
    mask[subZ, subY] = True
    mask[maskCalib] = True

    z, y = np.where(mask)
    samples = np.stack((y - SizeY // 2 - 1, z - SizeZ // 2 - 1), axis=-1)

    return mask, samples

# ---- Generate mask and samples ----
mask, samples = poissonPattern(SizeY=sizeOfKspace[0], SizeZ=sizeOfKspace[1],
                               VariableDensity=variableDensity, AccelFactor=xFactor,
                               Elliptical=eShutter, CalibRegY=sizeOfCenter[0],
                               CalibRegZ=sizeOfCenter[1])

AF = mask.size / np.count_nonzero(mask)
NE = np.count_nonzero(mask)

# ---- Show mask ----
if showMask:
    plt.ion()
    fig, ax = plt.subplots()
    frameMask = np.zeros_like(mask, dtype=bool)
    img = ax.imshow(frameMask, cmap='gray', vmin=0, vmax=1)
    ax.set_title(f"Effective acceleration factor = {AF:.4f}\nNumber of samples = {NE}")
    ax.axis('off')

    ky = samples[:, 0] + sizeOfKspace[0] // 2 + 1
    kz = samples[:, 1] + sizeOfKspace[1] // 2 + 1

    for cnt in range(NE):
        frameMask[kz[cnt]-1, ky[cnt]-1] = True
        img.set_data(frameMask)
        plt.pause(1 / speed)
        
    plt.ioff()
    plt.show()

# ---- Export samples to LUT file ----
if not os.path.exists(outputFolder):
    os.makedirs(outputFolder)

shutter = 'e' if eShutter else 's'
filename = os.path.join(outputFolder, f"eLUT_{NE}_{sizeOfKspace[0]}_{sizeOfKspace[1]}_{shutter}.txt")

with open(filename, 'w') as f:
    low16, high16 = split32to16(NE)
    f.write(f"{low16},\n")
    f.write(f"{high16},\n")
    for cnt in range(NE):
        f.write(f"{samples[cnt,0]},\n")
        f.write(f"{samples[cnt,1]},\n")
