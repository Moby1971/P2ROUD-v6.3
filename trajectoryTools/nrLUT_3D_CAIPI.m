
%% 3D CAIPIRINHA-style undersampled k-space generator
%
% Gustav Strijkers
% g.j.strijkers@amsterdamumc.nl
% July 2025
%

clearvars;
close all;
clc;
%#ok<*AGROW>


%% User input

sizeOfKspace = [128, 128];              % ky x kz
ACSsize = [25, 25];                     % Fully sampled ACS region [ky, kz]
Ry = 2;                                 % Undersampling factor in ky
Rz = 2;                                 % Undersampling factor in kz
outputFolder = "./output/";             % Output folder
showKspace = true;                      % Visualize mask (true/false)


%% Ensure Ry and Rz are integers

RyOrig = Ry;
RzOrig = Rz;
Ry = round(Ry);
Rz = round(Rz);
if Ry ~= RyOrig
    fprintf('INFO: Ry rounded from %.1f to %d.\n', RyOrig, Ry);
end
if Rz ~= RzOrig
    fprintf('INFO: Rz rounded from %.1f to %d.\n', RzOrig, Rz);
end


%% Generate 3D GRAPPA mask

[mask, samples] = caipirinha3DPattern(sizeOfKspace, Ry, Rz, ACSsize);


%% Summary

AF = numel(mask) / nnz(mask);       % Effective acceleration
NE = size(samples,1);               % Number of encodes
fileName = strcat(outputFolder,"nrLUT_3D_CAIPI_R",num2str(AF,2),"_",num2str(sizeOfKspace(1)),"x",num2str(sizeOfKspace(2)),".txt");

fprintf('\n------- CAIPIRINHA 3D k-space summary -------\n');
fprintf('K-space size               : %d x %d \n', sizeOfKspace);
fprintf('ACS size                   : %d x %d\n', ACSsize);
fprintf('Undersampling              : %d x %d\n', Ry, Rz);
fprintf('Effective acceleration     : %.2f\n', AF);
fprintf('Encodes (lines)            : %d\n', NE);
fprintf('Output file                : %s\n\n', fileName);


%% Display a slice of the mask (optional)

if showKspace
    figure(1); clf;
    imagesc(mask);
    colormap(gray);
    axis image off;
    title(sprintf('CAIPIRINHA 3D k-space \n R = %.2f \n N = %d', AF, NE), 'FontSize', 14);
end


%% Export LUT

fileID = fopen(fileName,'w');

[l16, h16] = split32to16(NE);
fprintf(fileID,[num2str(l16),'\n']);
fprintf(fileID,[num2str(h16),'\n']);

for cnt = 1:NE
    fprintf(fileID,"%d\n", samples(cnt,1)); % ky
    fprintf(fileID,"%d\n", samples(cnt,2)); % kz
end

fclose(fileID);


%% GRAPPA-style 3D pattern generator

function [mask, samples] = caipirinha3DPattern(sizeOfKspace, Ry, Rz, ACSdim)

kyDim = sizeOfKspace(1);
kzDim = sizeOfKspace(2);
mask = false(kyDim, kzDim);

% Define ACS block
cy = (kyDim + 1) / 2;
cz = (kzDim + 1) / 2;
y1 = round(cy - ACSdim(1)/2);
y2 = round(cy + ACSdim(1)/2 - 1);
z1 = round(cz - ACSdim(2)/2);
z2 = round(cz + ACSdim(2)/2 - 1);

% Fill ACS region
mask(y1:y2, z1:z2) = true;

% CAIPIRINHA-style sampling outside ACS
shiftCount = 0;
for kz = 1:kzDim
    if mod(kz - 1, Rz) ~= 0
        continue;
    end
    zOffset = mod(shiftCount, Ry);  % manual shift cycle
    shiftCount = shiftCount + 1;
    for ky = 1:kyDim
        if kz >= z1 && kz <= z2 && ky >= y1 && ky <= y2
            continue;
        end
        if mod(ky - 1 - zOffset, Ry) == 0
            mask(ky, kz) = true;
        end
    end
end

% Extract ky-kz coordinates
samples = [];
for ky = 1:kyDim
    for kz = 1:kzDim
        if mask(ky, kz)
            samples(end+1,:) = [ky - floor(kyDim/2) - 1, kz - floor(kzDim/2) - 1];
        end
    end
end

end


%% Split 32-bit to 2x 16-bit

function [low16, high16] = split32to16(int32Value)

int32Value = int32(int32Value);
high16 = int16(bitshift(double(int32Value), -16));
low16_unsigned = bitand(double(int32Value), 65535);

if low16_unsigned >= 2^15
    low16 = int16(low16_unsigned - 2^16);
else
    low16 = int16(low16_unsigned);
end

end
