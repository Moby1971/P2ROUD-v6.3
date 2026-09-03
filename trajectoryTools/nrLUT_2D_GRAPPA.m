% 2D GRAPPA-style undersampled k-space mask generator
%
% Author : Gustav Strijkers
% Date   : 2026-09-02
%
% Purpose:
%   Generate the undersampling look-up table for a 2D GRAPPA-style acquisition:
%   every R-th phase encoding line, plus a fully sampled block at the centre.
%
% How it works:
%   Two regions with different rules. Away from the centre only every R-th line
%   is measured, which is where the acceleration comes from; at the centre a
%   block of ACS lines is measured in full.
%
%   The ACS block is what makes the reconstruction possible. GRAPPA works out
%   how to synthesise the missing lines from the measured ones, and it can only
%   learn that from a region where both are present -- so the fully sampled
%   centre is training data, not merely extra signal.
%
%   Regular undersampling produces coherent aliasing: discrete copies of the
%   object rather than noise. That is deliberate here, since the parallel
%   imaging reconstruction unfolds exactly that kind of aliasing. It is the
%   opposite of what a compressed sensing pattern wants, which is why
%   nrLUT_2D_Gauss and nrLUT_3D_Poisson exist beside this.
%
%   R is rounded to an integer, since a fractional line spacing has no meaning
%   for the acquisition, and the rounding is announced rather than done
%   silently.
%
% Inputs:
%   none - a script; the values under "User input" below are the settings, and
%          are meant to be edited before running
%
% Output:
%   none - writes the look-up table to outputFolder, and shows the sampling
%          pattern when asked to

clearvars;
close all;
clc;


%% User input

sizeOfKspace = [256, 256];      % RO x PE
numberOfACS = 32;               % Number of ACS lines, must be even
R = 3.5;                          % Acceleration factor
outputFolder = "./output/";     % Output folder
showKspace = true;              % Visualize mask (true/false)
speed = 50;                     % Display speed



%% Ensure R is integer

Rorig = R;
R = round(R);
if R ~= Rorig
    fprintf('INFO: R rounded from %.1f to %d.\n', Rorig, R);
end


%% Generate GRAPPA mask

[mask, samples] = grappaPattern('SizeRO', sizeOfKspace(1), ...
    'SizePE', sizeOfKspace(2), 'AccelFactor', R, ...
    'CenterLines', numberOfACS);


%% Summary

AF = numel(mask) / nnz(mask);       % Effective acceleration
NE = size(samples,1);               % Number of encodes

fprintf('\n------- GRAPPA K-space Summary -------\n');
fprintf('K-space size               : %d x %d\n', sizeOfKspace(1), sizeOfKspace(2));
fprintf('ACS lines                  : %d\n', numberOfACS);
fprintf('Effective Acceleration     : %.2f\n', AF);
fprintf('Encodes (lines)            : %d\n', NE);
fprintf('Output file                : %s\n\n', strcat(outputFolder,"nrLUT_2D_GRAPPA_R",num2str(AF,2),"_",num2str(sizeOfKspace(2)),".txt"));


%% Display mask (optional)

if showKspace

    figure(1); clf;
    frameMask = false(size(mask));
    img = imagesc(frameMask);
    colormap(gray);
    clim([0 1]);
    axis image off;
    title({'GRAPPA Mask'; ['R = ', num2str(AF,4)]; ['N = ', num2str(NE)]}, 'FontSize', 14);

    % Animate
    ky = unique(samples(:,1));
    ky_idx = ky + floor(sizeOfKspace(2)/2) + 1;
    ky_idx = ky_idx(ky_idx >= 1 & ky_idx <= sizeOfKspace(2));

    for cnt = 1:length(ky_idx)
        frameMask(:, ky_idx(cnt)) = true;
        img.CData = frameMask;
        pause(1/speed);
    end

end


%% Export LUT (kz = 0 always)

filename = strcat(outputFolder,"nrLUT_2D_GRAPPA_R",num2str(AF,2),"_",num2str(sizeOfKspace(2)),".txt");
fileID = fopen(filename,'w');

[l16, h16] = split32to16(NE);
fprintf(fileID,[num2str(l16),'\n']);
fprintf(fileID,[num2str(h16),'\n']);

for cnt = 1:NE
    fprintf(fileID,[num2str(samples(cnt,1)),'\n']);
    fprintf(fileID,"0\n");
end

fclose(fileID);


%% GRAPPA-style line-based pattern

function [mask, samples] = grappaPattern(varargin)

p = inputParser;
addParameter(p,'SizeRO',256,@isnumeric);
addParameter(p,'SizePE',256,@isnumeric);
addParameter(p,'AccelFactor',4,@isnumeric);
addParameter(p,'CenterLines',32,@isnumeric);
parse(p,varargin{:});
S = p.Results;

SizeRO = S.SizeRO;
SizePE = S.SizePE;
AF = S.AccelFactor;

% Center (ACS) region
cy = (SizePE + 1) / 2;
y1 = round(cy - S.CenterLines/2);
y2 = round(cy + S.CenterLines/2 - 1);
centerLines = y1:y2;

% Uniformly spaced PE lines (excluding ACS)
maskLines = false(1, SizePE);
maskLines(centerLines) = true;

for k = 1:SizePE
    if ~maskLines(k) && mod(k - y1, AF) == 0
        maskLines(k) = true;
    end
end

% Final mask and coordinate list
mask = false(SizeRO, SizePE);
mask(:,maskLines) = true;

selectedLines = find(maskLines);
samples = selectedLines(:) - floor(SizePE/2) - 1;
samples = [samples, zeros(length(samples),1)];

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
