# ------------------------------------------------------------------------------------
#  Pseudo radial k-space trajectory
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
angleNr = 10
display = False
outputdir = './output/'
exportList = True
reps = 1
viewSpeed = 1000

tinyGoldenAngles = [111.24611, 68.75388, 49.75077, 38.97762, 32.03967,
                    27.19840, 23.62814, 20.88643, 18.71484, 16.95229]

rev = 1
numPointsTarget = dimy * dimz
numSamplesPerSpoke = 2 * max(dimy, dimz)
t = np.linspace(-1, 1, numSamplesPerSpoke)

ry = dimy / 2
rz = dimz / 2

kSpaceList = []
angle = 0
spokeNr = 0

while len(kSpaceList) < numPointsTarget:
    spokeNr += 1
    angle += tinyGoldenAngles[angleNr - 1]
    theta = np.deg2rad(angle)

    y = np.round(t * np.cos(theta) * ry).astype(int)
    z = np.round(t * np.sin(theta) * rz).astype(int)

    if order == 1 and spokeNr % 2 == 0:
        y = np.flip(y)
        z = np.flip(z)

    spoke = list(zip(y, z))
    seen = set()
    spoke_unique = []
    for pt in spoke:
        if pt not in seen:
            seen.add(pt)
            spoke_unique.append(pt)

    spoke_inside = [pt for pt in spoke_unique if (pt[0]**2 / ry**2 + pt[1]**2 / rz**2) <= 1]

    kSpaceList.extend(spoke_inside)

    if len(kSpaceList) > numPointsTarget:
        kSpaceList = kSpaceList[:numPointsTarget]
        break

kSpaceArray = np.array(kSpaceList)
uniquePoints, indices = np.unique(kSpaceArray, axis=0, return_inverse=True)
numUnique = uniquePoints.shape[0]
numTotal = kSpaceArray.shape[0]
avgSamplesPerPoint = numTotal / numUnique

Ygrid, Zgrid = np.meshgrid(np.arange(-dimy//2, dimy//2),
                           np.arange(-dimz//2, dimz//2))
ellipticalMask = (Ygrid**2 / ry**2 + Zgrid**2 / rz**2) <= 1
numEllipticalPoints = np.count_nonzero(ellipticalMask)
coveredFraction = 100 * numUnique / numEllipticalPoints

if exportList:
    os.makedirs(outputdir, exist_ok=True)
    ord = 'r' if order == 1 else 'o'
    filename = os.path.join(outputdir, f'exLUT_radial_y{dimy}_z{dimz}_a{round(tinyGoldenAngles[angleNr-1],2)}_r{reps}.txt')
    with open(filename, 'w') as f:
        for y, z in kSpaceArray:
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

    ky_idx = kSpaceArray[:, 0] + dimy // 2
    kz_idx = kSpaceArray[:, 1] + dimz // 2

    for cnt in range(kSpaceArray.shape[0]):
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

    fig.suptitle('Pseudo-radial k-space fill', color='white', fontsize=16)
    plt.show()

def ternary(cond, valTrue, valFalse):
    return valTrue if cond else valFalse

print('\n--- k-space trajectory summary ---')
print(f'Trajectory type     : Pseudo-radial')
print(f'Dimensions (ky × kz): {dimy} × {dimz}')
print(f'Total samples       : {numTotal}')
print(f'Unique positions    : {numUnique} / {numEllipticalPoints} ({coveredFraction:.1f}% coverage of elliptical mask)')
print(f'Avg samples/point   : {avgSamplesPerPoint:.2f}')
print(f'Spoke direction     : {ternary(order==1, "Alternating", "Unidirectional")}')
print(f'Golden angle used   : {tinyGoldenAngles[angleNr-1]:.5f}° (index {angleNr})')
print(f'Effective spokes    : {spokeNr}')
print(f'Revolutions approx. : {angle / 360:.2f}')
print(f'Output file         : {filename}')
print('----------------------------------\n')
