# ------------------------------------------------------------------------------------
#  Pseudo spiral k-space trajectory
#  For MR Solutions custom 3D k-space (pe1_order = 4: exLUT)
#
#  Gustav Strijkers
#  July 2025
#
# ------------------------------------------------------------------------------------



import numpy as np
import matplotlib.pyplot as plt
import os

# Initialization
dimy = 64
dimz = 64
order = 1
angleNr = 3
display = False
outputdir = './output/'
exportList = True
reps = 1
viewSpeed = 1000

tinyGoldenAngles = [111.24611, 68.75388, 49.75077, 38.97762, 32.03967, 27.19840, 23.62814, 20.88643, 18.71484, 16.95229]

# Spiral generation
rev = 1
angle = 0
numberOfSpiralPoints = 256
dimYZ = 256
radiusY = dimYZ // 2
radiusZ = dimYZ // 2
center = [radiusY, radiusZ]

center = np.array([radiusY, radiusZ])
edge = center + np.array([
    round(radiusY * np.cos(np.deg2rad(angle))),
    round(radiusZ * np.sin(np.deg2rad(angle)))
])

r = np.linalg.norm(np.array(edge) - np.array(center))
thetaOffset = np.arctan2(edge[1] - center[1], edge[0] - center[0])

gamma = 0.8
t = np.linspace(0, 1, numberOfSpiralPoints)**gamma * (dimYZ / 2 - 1)
theta = np.linspace(0, 2 * np.pi * rev, numberOfSpiralPoints)
theta += np.deg2rad(np.random.rand() * 360)

y0 = np.cos(theta) * t + center[0]
z0 = np.sin(theta) * t + center[1]

ky = []
kz = []
numberOfSpirals = 2000

for ns in range(1, numberOfSpirals + 1):
    angle += tinyGoldenAngles[angleNr - 1]
    rad = np.deg2rad(angle)

    y = (y0 - center[0]) * np.cos(rad) + (z0 - center[1]) * np.sin(rad) + center[0]
    z = -(y0 - center[0]) * np.sin(rad) + (z0 - center[1]) * np.cos(rad) + center[1]

    y *= dimy / dimYZ
    z *= dimz / dimYZ

    if order == 1 and ns % 2 == 0:
        y = np.flip(y)
        z = np.flip(z)

    ky.extend(y)
    kz.extend(z)

ky = np.floor(np.array(ky) - dimy / 2).astype(int)
kz = np.floor(np.array(kz) - dimz / 2).astype(int)
kSpaceList = np.column_stack((ky, kz))

# Remove repeats
for _ in range(100):
    diffs = np.diff(kSpaceList, axis=0)
    mask = np.any(diffs != 0, axis=1)
    mask = np.insert(mask, 0, True)
    kSpaceList = kSpaceList[mask]

loc = np.where((kSpaceList[:, 0] == 0) & (kSpaceList[:, 1] == 0))[0]
kSpaceList = np.delete(kSpaceList, loc[::2], axis=0)

kSpaceList = kSpaceList[:dimy * dimz * reps, :]
uniquePoints, ic = np.unique(kSpaceList, axis=0, return_inverse=True)
numUnique = uniquePoints.shape[0]
numTotal = kSpaceList.shape[0]
avgSamplesPerPoint = numTotal / numUnique

ry = dimy / 2
rz = dimz / 2
Ygrid, Zgrid = np.meshgrid(np.arange(-dimy//2, np.ceil(dimy/2)),
                           np.arange(-dimz//2, np.ceil(dimz/2)))
ellipticalMask = (Ygrid**2 / ry**2 + Zgrid**2 / rz**2) <= 1
numEllipticalPoints = np.count_nonzero(ellipticalMask)
coveredFraction = 100 * numUnique / numEllipticalPoints
effectiveSpirals = numTotal // numberOfSpiralPoints

if exportList:
    os.makedirs(outputdir, exist_ok=True)
    ord = 'r' if order == 1 else 'o'
    filename = os.path.join(outputdir, f'exLUT_spiral_y{dimy}_z{dimz}_a{round(tinyGoldenAngles[angleNr-1],2)}_r{reps}.txt')
    with open(filename, 'w') as f:
        for y, z in kSpaceList:
            f.write(f"{y}\n{z}\n")

if display:
    pixelSize = 10
    figWidth = dimy * pixelSize
    figHeight = dimz * pixelSize

    fig = plt.figure(figsize=(figWidth / 100, figHeight / 100), facecolor='black')
    ax = fig.add_axes([0.05, 0.05, 0.8, 0.85])
    ax.set_facecolor('black')
    ax.axis('off')

    frameMask = np.zeros((dimz, dimy), dtype=int)
    img = ax.imshow(frameMask, cmap='viridis', vmin=0.5, vmax=1)

    ky_idx = kSpaceList[:, 0] + dimy // 2
    kz_idx = kSpaceList[:, 1] + dimz // 2

    for cnt in range(kSpaceList.shape[0]):
        y, z = ky_idx[cnt], kz_idx[cnt]
        if 0 <= y < dimy and 0 <= z < dimz:
            frameMask[z, y] += 1
            img.set_data(frameMask)
            img.set_clim(vmin=0.5, vmax=max(1, frameMask.max()))
            plt.pause(1 / viewSpeed)

    cbar = fig.colorbar(img, ax=ax, fraction=0.046, pad=0.04)
    cbar.set_label('# samples per k-space location', color='white')
    cbar.ax.yaxis.set_tick_params(color='white')
    plt.setp(plt.getp(cbar.ax.axes, 'yticklabels'), color='white')
    fig.suptitle('Pseudo-spiral k-space fill', color='white', fontsize=16)
    plt.show()

def ternary(cond, valTrue, valFalse):
    return valTrue if cond else valFalse

print('\n--- k-space trajectory summary ---')
print(f'Trajectory type        : Pseudo-spiral')
print(f'Dimensions (ky × kz)   : {dimy} × {dimz}')
print(f'Total samples          : {numTotal}')
print(f'Unique positions       : {numUnique} / {numEllipticalPoints} ({coveredFraction:.1f}% elliptical coverage)')
print(f'Avg samples/point      : {avgSamplesPerPoint:.2f}')
print(f'Spiral direction       : {ternary(order==1, "Alternating", "Unidirectional")}')
print(f'Golden angle used      : {tinyGoldenAngles[angleNr-1]:.5f}° (index {angleNr})')
print(f'Effective spirals      : {effectiveSpirals}')
print(f'Revolutions per spiral : {rev}')
print(f'Output file            : {filename}')
print('----------------------------------\n')
