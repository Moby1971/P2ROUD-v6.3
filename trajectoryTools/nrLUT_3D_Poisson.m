%% 3D random undersampled k-space maker for pe1_order = 5 extended non-regular LUT
%
% Gustav Strijkers
% g.j.strijkers@amsterdamumc.nl
% June 2025
%
%

clearvars;
close all;
clc;
%#ok<*UNRCH>



%% User input

% Size of k-space
sizeOfKspace = [170, 74];

% Size of center-filled region
sizeOfCenter = [45, 15];

% Desired acceleration factor (1 or higher)
xFactor = 3;

% Elliptical shutter (true/false)
eShutter = true;

% Variable density (0 = uniform, >0 = more samples in the center, typical value = 0.8
variableDensity = 0.8;

% Output folder
outputFolder = "./output/";

% Show the mask (true/false)
showMask = true;
speed = 10000;




%% Calculate the mask and k-space points

[mask, samples] = poissonPattern('SizeY', sizeOfKspace(1), 'SizeZ', sizeOfKspace(2), ...
    'Elliptical',eShutter,'AccelFactor',xFactor,'VariableDensity',variableDensity, ...
    'CalibRegY', sizeOfCenter(1), 'CalibRegZ', sizeOfCenter(2));




%% Show the mask

AF = numel(mask) / nnz(mask);
NE = nnz(mask);

if showMask
    figure(11);
    frameMask = false(size(mask));

    % Initialize display
    img = imagesc(frameMask);
    colormap(gray);
    clim([0 1]);
    axis image off;
    title({strcat("Effective acceleration factor = ", num2str(AF,4)), ...
        strcat("Number of samples = ",num2str(NE))},'FontSize', 20);

    % Convert (ky, kz) sample coordinates to matrix indices
    ky = samples(:,1) + floor(sizeOfKspace(1)/2) + 1;
    kz = samples(:,2) + floor(sizeOfKspace(2)/2) + 1;

    for cnt = 1:NE
        frameMask(kz(cnt), ky(cnt)) = true;
        img.CData = frameMask;
        pause(1/speed);
    end
end



%% Export the k-space points to LUT file

if eShutter
    shutter = 'E';
else
    shutter = 'S';
end

filename = strcat(outputFolder,"nrLUT_3D_R",num2str(AF,2),"_M",num2str(sizeOfKspace(1)),"x",num2str(sizeOfKspace(2)),shutter,".txt");
fileID = fopen(filename,'w');

[l16, h16] = split32to16(NE);

fprintf(fileID,[num2str(l16),'\n']);
fprintf(fileID,[num2str(h16),'\n']);

for cnt = 1:NE
     fprintf(fileID,[num2str(samples(cnt,1)),'\n']);
     fprintf(fileID,[num2str(samples(cnt,2)),'\n']);
end
 
fclose(fileID);



%% Helper functions


% Split value into HI and LO 16-bit signed components
function [low16, high16] = split32to16(int32Value)

% Ensure the input is a 32-bit signed integer
int32Value = int32(int32Value);

% Extract the high 16 bits
high16 = int16(bitshift(double(int32Value), -16));

% Extract the low 16 bits
low16_unsigned = bitand(double(int32Value), 65535);

% Convert to signed 16-bit representation
if low16_unsigned >= 2^15 % Check if the highest bit is set
    low16 = int16(low16_unsigned - 2^16);
else
    low16 = int16(low16_unsigned);
end

end


function [mask, samples] = poissonPattern(varargin)

p = inputParser;
addParameter(p,'SizeY',128,@isnumeric);
addParameter(p,'SizeZ',128,@isnumeric);
addParameter(p,'VariableDensity',0.8,@isnumeric);
addParameter(p,'AccelFactor',2,@isnumeric);
addParameter(p,'Elliptical',false,@islogical);
addParameter(p,'RandSeed',11235,@isnumeric);
addParameter(p,'CalibRegY',16,@isnumeric);
addParameter(p,'CalibRegZ',16,@isnumeric);
parse(p,varargin{:});
S = p.Results;

rng(S.RandSeed);

SizeY = S.SizeY;
SizeZ = S.SizeZ;
N_full = SizeY * SizeZ;

cy = (SizeY + 1) / 2;
cz = (SizeZ + 1) / 2;
[Y, Z] = meshgrid(1:SizeY, 1:SizeZ);

% Elliptical shutter
a = SizeY / 2;
b = SizeZ / 2;
R2 = ((Y - cy) / a).^2 + ((Z - cz) / b).^2;

sampleMask = true(SizeZ, SizeY);
if S.Elliptical
    sampleMask = R2 <= 1;
end

% Calibration region, elliptical if selected
maskCalib = false(SizeZ, SizeY);
if S.Elliptical
    rY = S.CalibRegY / 2;
    rZ = S.CalibRegZ / 2;
    R2calib = ((Y - cy) / rY).^2 + ((Z - cz) / rZ).^2;
    maskCalib = R2calib <= 1;
else
    y1 = round(cy - S.CalibRegY/2);
    y2 = round(cy + S.CalibRegY/2 - 1);
    z1 = round(cz - S.CalibRegZ/2);
    z2 = round(cz + S.CalibRegZ/2 - 1);
    maskCalib(z1:z2, y1:y2) = true;
end
maskCalib = maskCalib & sampleMask;

% Special case: full sampling
if S.AccelFactor <= 1
    mask = sampleMask;
    mask(maskCalib) = true;
    [z, y] = find(mask);
    samples = [y - floor(SizeY/2) - 1, z - floor(SizeZ/2) - 1];
    return;
end

% Desired sample count
N_target_total = round(N_full / S.AccelFactor);
N_calib = nnz(maskCalib);
N_random = N_target_total - N_calib;

% Feasibility check
n_available = nnz(sampleMask & ~maskCalib);
if N_random > n_available
    N_random = n_available;
    N_target_total = N_random + N_calib;
    S.AccelFactor = N_full / N_target_total;
end

% Variable density weighting
R = sqrt(R2);
if S.VariableDensity > 0
    vd = exp(-(R / 0.15).^S.VariableDensity);
else
    vd = ones(SizeZ, SizeY);
end
vd(~sampleMask | maskCalib) = 0;
vd = vd / sum(vd(:));

% Draw weighted samples
[validZ, validY] = find(sampleMask & ~maskCalib);
weights = vd(sampleMask & ~maskCalib);
drawn = weighted_sample_unique(length(weights), weights, N_random);
subZ = validZ(drawn);
subY = validY(drawn);

% Build final mask
mask = false(SizeZ, SizeY);
mask(sub2ind([SizeZ, SizeY], subZ, subY)) = true;
mask(maskCalib) = true;

% Output coordinates
[z, y] = find(mask);
samples = [y - floor(SizeY/2) - 1, z - floor(SizeZ/2) - 1];

end



% Unique weighted sampling
function idx = weighted_sample_unique(N, w, k)

w = w(:) / sum(w);
idx = zeros(k,1);
avail = true(N,1);
for cnt = 1:k
    w_curr = w;
    w_curr(~avail) = 0;
    w_curr = w_curr / sum(w_curr);
    cdf = cumsum(w_curr);
    r = rand();
    sel = find(cdf >= r, 1, 'first');
    idx(cnt) = sel;
    avail(sel) = false;
end

end