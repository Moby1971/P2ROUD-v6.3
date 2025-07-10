# 3D MPRAGE random undersampled k-space maker for pe1_order = 5 extended non-regular LUT
#
# Gustav Strijkers
# g.j.strijkers@amsterdamumc.nl
# July 2025
#

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.colors as mcolors
import os
import imageio
from time import sleep

# User input

sizeOfKspace = [128, 128]               # Size of k-space
sizeOfCenter = [16, 16]                 # Size of center-filled region
xFactor = 4                             # Desired acceleration factor (1 or higher)
variableDensity = 0.8                   # Variable density (0 = uniform, >0 = more samples in the center, typical value = 0.8)
eShutter = True                         # Elliptical shutter (True/False)
mprageShotLength = 64                   # MPRAGE shot length

showMask = False                        # Show k-space filling
movieDelay = 0.1                        # Waiting time between drawing of k-space points (s)
outputFolder = "./output/"              # Output folder

gifSave = False                         # Save animated gif (True/False)
gifFrameDelay = 0.0001                  # Seconds per frame animated gif
gifFile = 'mprageKspaceFilling.gif'     # Gif file name
nShotsFullGif = 2                       # Number of shots to save fully

os.makedirs(outputFolder, exist_ok=True)

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.colors as mcolors
import os
import imageio
from time import sleep

# Helper functions
def split32to16(int32_value):
    int32_value = int(int32_value)
    high16 = np.int16(int32_value >> 16)
    low16_unsigned = int32_value & 0xFFFF
    if low16_unsigned >= 2**15:
        low16 = np.int16(low16_unsigned - 2**16)
    else:
        low16 = np.int16(low16_unsigned)
    return low16, high16

def weightedSampleUnique(N, weights, k):
    weights = np.array(weights, dtype=float)
    weights /= weights.sum()
    indices = []
    available = np.ones(N, dtype=bool)
    for _ in range(k):
        w_curr = weights.copy()
        w_curr[~available] = 0
        w_curr /= w_curr.sum()
        cdf = np.cumsum(w_curr)
        r = np.random.rand()
        sel = np.searchsorted(cdf, r, side='right')
        indices.append(sel)
        available[sel] = False
    return np.array(indices)

def poissonPattern(SizeY=128, SizeZ=128, VariableDensity=0.8, AccelFactor=2, Elliptical=False,
                   RandSeed=11235, CalibRegY=16, CalibRegZ=16, ShotLength=64):

    np.random.seed(RandSeed)
    cy = (SizeY + 1) / 2
    cz = (SizeZ + 1) / 2
    Y, Z = np.meshgrid(np.arange(1, SizeY + 1), np.arange(1, SizeZ + 1))
    a, b = SizeY / 2, SizeZ / 2
    R2 = ((Y - cy) / a) ** 2 + ((Z - cz) / b) ** 2

    sampleMask = np.ones((SizeZ, SizeY), dtype=bool)
    if Elliptical:
        sampleMask = R2 <= 1

    rY, rZ = CalibRegY / 2, CalibRegZ / 2
    R2calib = ((Y - cy) / rY) ** 2 + ((Z - cz) / rZ) ** 2
    maskCalib = (R2calib <= 1) & sampleMask

    N_full = SizeY * SizeZ
    N_target = round(N_full / AccelFactor)
    n_calib = np.count_nonzero(maskCalib)
    n_acq = round(N_target / ShotLength) * ShotLength
    n_acq = max(n_acq, n_calib)
    n_random = n_acq - n_calib

    vd = np.ones((SizeZ, SizeY))
    if VariableDensity > 0:
        R = np.sqrt(R2)
        vd = np.exp(-(R / 0.15) ** VariableDensity)
    vd[~sampleMask | maskCalib] = 0
    vd /= vd.sum()

    validZ, validY = np.where(sampleMask & ~maskCalib)
    weights = vd[sampleMask & ~maskCalib]
    drawn = weightedSampleUnique(len(weights), weights, n_random)
    subZ = validZ[drawn]
    subY = validY[drawn]

    mask = np.zeros((SizeZ, SizeY), dtype=bool)
    mask[subZ, subY] = True
    mask[maskCalib] = True
    z, y = np.where(mask)
    samples = np.stack([y - SizeY // 2 - 1, z - SizeZ // 2 - 1], axis=1)

    return mask, samples, mask, n_calib, n_random

# Compatibility check
if sizeOfKspace[1] % mprageShotLength != 0:
    oldLength = mprageShotLength
    divisors = [d for d in range(4, sizeOfKspace[1] + 1) if sizeOfKspace[1] % d == 0]
    idx = np.argmin(np.abs(np.array(divisors) - oldLength))
    mprageShotLength = divisors[idx]
    print(f'Adjusted shot length from {oldLength} to {mprageShotLength} to match kz size {sizeOfKspace[1]}.')

if eShutter:
    ellipticalArea = np.pi * (sizeOfKspace[0] / 2) * (sizeOfKspace[1] / 2)
    maxSamples = int(np.floor(ellipticalArea))
    minAF = sizeOfKspace[0] * sizeOfKspace[1] / maxSamples
    if xFactor < minAF:
        oldAF = xFactor
        xFactor = np.ceil(minAF * 100) / 100
        print(f'Adjusted acceleration factor from {oldAF:.2f} to {xFactor:.2f} due to elliptical shutter constraint.')

mask, samples, sampleMaskOut, nCalib, nRandom = poissonPattern(
    ShotLength=mprageShotLength,
    SizeY=sizeOfKspace[0], SizeZ=sizeOfKspace[1],
    AccelFactor=xFactor, VariableDensity=variableDensity,
    CalibRegY=sizeOfCenter[0], CalibRegZ=sizeOfCenter[1],
    Elliptical=eShutter
)

# Report parameters
Nfull = np.prod(sizeOfKspace)
Nacq = nCalib + nRandom
AF = Nfull / Nacq
NE = Nacq

print('\n----- k-space summary ------')
print(f'Total Cartesian k-space points:   {Nfull}')
print(f'Center samples:                   {nCalib}')
print(f'Random samples:                   {nRandom}')
print(f'Total acquired samples:           {Nacq}')
print(f'Requested acceleration factor:    {xFactor:.4f}')
print(f'Effective acceleration factor:    {AF:.4f}')

# Fill k-space
kz, ky = samples[:, 1], samples[:, 0]
theta = np.arctan2(kz, ky)
theta[theta < 0] += 2 * np.pi
r = np.sqrt(ky ** 2 + kz ** 2)

Ntotal = samples.shape[0]
Nshots = int(np.ceil(Ntotal / mprageShotLength))
globalIdx = np.lexsort((r, theta))
shotList = []
startIdx = 0
for s in range(Nshots):
    stopIdx = min(startIdx + mprageShotLength, Ntotal)
    sel = globalIdx[startIdx:stopIdx]
    sel = sel[np.argsort(r[sel])]
    shotList.append(sel)
    startIdx = stopIdx

# Show the filling
if showMask:
    fig, ax = plt.subplots(figsize=(8, 8))
    img = np.zeros((sizeOfKspace[1], sizeOfKspace[0]), dtype=int)
    cmap = plt.colormaps['tab10']
    colors = cmap(np.linspace(0, 1, 7))
    black = np.array([[0, 0, 0, 1]])
    colormap_array = np.vstack([black, colors])
    im = ax.imshow(img, cmap=mcolors.ListedColormap(colormap_array), vmin=0, vmax=7)
    ax.set_xticks([])
    ax.set_yticks([])
    ax.set_facecolor('k')
    ax.set_title(f'Effective acceleration factor = {AF:.2f}\nNumber of samples = {NE}\nShot length = {mprageShotLength}',
                 fontsize=12, color='w')
    fig.patch.set_facecolor('k')

    maxShotsForColor = 7
    colorIdx = (np.arange(Nshots) % maxShotsForColor) + 1
    frames = []

    for s, sel in enumerate(shotList):
        col = colorIdx[s]
        for i in range(len(sel)):
            ky = samples[sel[i], 0] + sizeOfKspace[0] // 2 + 1
            kz = samples[sel[i], 1] + sizeOfKspace[1] // 2 + 1
            img[kz, ky] = col
        im.set_data(img)  # Update image only once per shot
        plt.pause(movieDelay)

        if gifSave and (s < nShotsFullGif):
            fig.canvas.draw()
            frame = np.frombuffer(fig.canvas.tostring_rgb(), dtype=np.uint8)
            frame = frame.reshape(fig.canvas.get_width_height()[::-1] + (3,))
            frames.append(frame.copy())

    if gifSave:
        imageio.mimsave(gifFile, frames, duration=gifFrameDelay)
        
    plt.show()

# Export the k-space file
shutter = 'E' if eShutter else 'S'
filename = f"{outputFolder}/nrLUT_MPRAGE_R{AF:.2f}_S{mprageShotLength}_M{sizeOfKspace[0]}x{sizeOfKspace[1]}{shutter}.txt"

with open(filename, 'w') as f:
    l16, h16 = split32to16(NE)
    f.write(f"{l16}\n")
    f.write(f"{h16}\n")
    for sel in shotList:
        for i in sel:
            f.write(f"{samples[i, 0]}\n")
            f.write(f"{samples[i, 1]}\n")


