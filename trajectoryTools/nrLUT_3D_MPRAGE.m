%% 3D MPRAGE random undersampled k-space maker for pe1_order = 5 extended non-regular LUT
%
% Gustav Strijkers
% g.j.strijkers@amsterdamumc.nl
% July 2025
%
%

clearvars;
close all;
clc;
%#ok<*UNRCH>


%% User input

sizeOfKspace = [128, 128];                % Size of k-space
sizeOfCenter = [32, 32];                % Size of center-filled region
xFactor = 4;                            % Desired acceleration factor (1 or higher)
variableDensity = 0.8;                  % Variable density (0 = uniform, >0 = more samples in the center, typical value = 0.8
eShutter = true;                        % Elliptical shutter (true/false)
mprageShotLength = 32;                  % MPRAGE shot length
showMask = true;                        % Show k-space filling
movieDelay = 0.0001;                    % Waiting time between drawing of k-space points (s)
outputFolder = "./output/";             % Output folder

gifSave = false;                        % Save animated gif (true/false)
gifFrameDelay = 0.0001;                 % Seconds per frame animated gif
gifFile = 'mprageKspaceFilling.gif';    % Gif file name
nShotsFullGif = 2;                      % Number of shots to save fully



%% Shot-length and kz size compatibility check

if mod(sizeOfKspace(2), mprageShotLength) ~= 0
    oldLength = mprageShotLength;
    divisors = 4:sizeOfKspace(2);
    valid = divisors(mod(sizeOfKspace(2), divisors) == 0);
    [~, idx] = min(abs(valid - oldLength));
    mprageShotLength = valid(idx);
    fprintf('Adjusted shot length from %d to %d to match kz size %d.\n', oldLength, mprageShotLength, sizeOfKspace(2));
end



%% Acceleration factor feasibility check for elliptical shutter
if eShutter
    ellipticalArea = pi * (sizeOfKspace(1)/2) * (sizeOfKspace(2)/2);
    maxSamples = floor(ellipticalArea);
    minAF = sizeOfKspace(1) * sizeOfKspace(2) / maxSamples;
    if xFactor < minAF
        oldAF = xFactor;
        xFactor = ceil(minAF * 100) / 100;  % round up slightly
        fprintf('Adjusted acceleration factor from %.2f to %.2f due to elliptical shutter constraint.\n', ...
            oldAF, xFactor);
    end
end



%% Generate undersampling mask using VD Poisson-disc

[mask, samples, sampleMaskOut, nCalib, nRandom] = poissonPattern('ShotLength', mprageShotLength, ...
    'SizeY', sizeOfKspace(1), 'SizeZ', sizeOfKspace(2), ...
    'AccelFactor', xFactor, 'VariableDensity', variableDensity, ...
    'CalibRegY', sizeOfCenter(1), 'CalibRegZ', sizeOfCenter(2), ...
    'Elliptical', eShutter);

Nfull = prod(sizeOfKspace);          % full Cartesian grid
Nacq = nCalib + nRandom;           % total acquired
AF = Nfull / Nacq;                   % actual acceleration
NE = Nacq;

fprintf('\n--- K-space summary ---\n');
fprintf('Total Cartesian k-space points:   %d\n', Nfull);
fprintf('Center samples:                   %d\n', nCalib);
fprintf('Random samples:                   %d\n', nRandom);
fprintf('Total acquired samples:           %d\n', Nacq);
fprintf('Requested acceleration factor:    %.4f\n', xFactor);
fprintf('Effective acceleration factor:    %.4f\n', AF);



%% Assign selected samples to radial shots

% Compute angle and radius
[kz, ky] = deal(samples(:,2), samples(:,1));
theta = atan2(kz, ky);
theta(theta < 0) = theta(theta < 0) + 2*pi;
r = sqrt(ky.^2 + kz.^2);

Ntotal = size(samples, 1);
Nshots = ceil(Ntotal / mprageShotLength);

% Sort all samples by theta, then r (center-outward within angular order)
[~, globalIdx] = sortrows([theta, r]);

shotList = cell(Nshots, 1);
startIdx = 1;

for s = 1:Nshots
    stopIdx = min(startIdx + mprageShotLength - 1, Ntotal);
    sel = globalIdx(startIdx:stopIdx);

    % Within this slice, sort again by r (just to be sure)
    [~, rorder] = sort(r(sel));
    shotList{s} = sel(rorder);

    startIdx = stopIdx + 1;
end



%% Visualization

if showMask

    figure(11); clf;
    img = zeros(sizeOfKspace(2), sizeOfKspace(1));  % [kz, ky]

    Ny = sizeOfKspace(1);
    Nz = sizeOfKspace(2);

    % Fixed colormap
    maxShotsForColor = 7;
    cmap = lines(maxShotsForColor);  % consistent color set
    colormap([0 0 0; cmap]);  % prepend black background

    % Color mapping: map each shot to a consistent color index
    colorIdx = mod(0:Nshots-1, maxShotsForColor) + 1;

    % Tick marks
    xticks = 1:Ny/8:Ny;
    yticks = 1:Nz/8:Nz;
    xticklabels = arrayfun(@(x) num2str(x - Ny/2 - 1), xticks, 'UniformOutput', false);
    yticklabels = arrayfun(@(y) num2str(y - Nz/2 - 1), yticks, 'UniformOutput', false);

    hImg = imagesc(img);
    axis image xy;

    % Fix the CLim to prevent color jumps
    set(gca, 'CLim', [0 maxShotsForColor]);

    set(gca, ...
        'Color', 'k', ...
        'XColor', 'w', ...
        'YColor', 'w', ...
        'XTick', xticks, ...
        'YTick', yticks, ...
        'XTickLabel', xticklabels, ...
        'YTickLabel', yticklabels, ...
        'TickDir', 'out', ...
        'TickLength', [0.005 0.005], ...
        'LineWidth', 1.2, ...
        'FontSize', 14, ...
        'FontName', 'Arial');

    set(gcf, 'Color', 'k');
    box on;

    title({sprintf('Effective acceleration factor = %.2f', AF), ...
        sprintf('Number of samples = %d', NE), ...
        sprintf('Shot length = %d', mprageShotLength)}, ...
        'FontSize', 16, 'Color', 'w');

    % Animate
    for s = 1:Nshots

        sel = shotList{s};

        for i = 1:numel(sel)

            ky = samples(sel(i),1) + Ny/2 + 1;
            kz = samples(sel(i),2) + Nz/2 + 1;
            img(kz,ky) = colorIdx(s);  % fixed color for shot s
            set(hImg, 'CData', img);
            drawnow;

            % Decide whether to save this frame
            if s <= nShotsFullGif
                frameShouldBeSaved = true;
            elseif i == numel(sel)
                frameShouldBeSaved = true;
            else
                frameShouldBeSaved = false;
            end

            if gifSave & frameShouldBeSaved

                frame = getframe(gcf);                % capture full figure (axes + title)
                im = frame2im(frame);                 % convert to RGB image
                scaleFactor = 0.25;                   % scale down for smaller GIF
                im = imresize(im, scaleFactor);       % resize full figure
                [A, map] = rgb2ind(im, 64);           % reduce color depth

                if s == 1 && i == 1
                    imwrite(A, map, gifFile, 'gif', 'LoopCount', Inf, 'DelayTime', gifFrameDelay);
                else
                    imwrite(A, map, gifFile, 'gif', 'WriteMode', 'append', 'DelayTime', gifFrameDelay);
                end

            end

            pause(movieDelay);

        end

    end

end


%% Export the k-space points to LUT file

if eShutter
    shutter = 'E';
else
    shutter = 'S';
end

filename = strcat(outputFolder,"nrLUT_MPRAGE_R",num2str(AF,2),"_S",num2str(mprageShotLength),"_M",num2str(sizeOfKspace(1)),"x",num2str(sizeOfKspace(2)),shutter,".txt");
fileID = fopen(filename,'w');

[l16, h16] = split32to16(NE);

fprintf(fileID,[num2str(l16),'\n']);
fprintf(fileID,[num2str(h16),'\n']);

for s = 1:Nshots
    sel = shotList{s};
    for i = 1:numel(sel)
        fprintf(fileID,[num2str(samples(sel(i),1)),'\n']);
        fprintf(fileID,[num2str(samples(sel(i),2)),'\n']);
    end
end

fclose(fileID);




%% Helper functions


% Poisson-disc undersampling mask generator
function [mask, samples, sampleMask, n_calib, n_random] = poissonPattern(varargin)

p = inputParser;
addParameter(p,'SizeY',128); addParameter(p,'SizeZ',128);
addParameter(p,'VariableDensity',0.8); addParameter(p,'AccelFactor',2);
addParameter(p,'Elliptical',false); addParameter(p,'RandSeed',11235);
addParameter(p,'CalibRegY',16); addParameter(p,'CalibRegZ',16);
addParameter(p,'ShotLength',64); parse(p,varargin{:}); S = p.Results;

rng(S.RandSeed);
SizeY = S.SizeY; SizeZ = S.SizeZ;
cy = (SizeY + 1) / 2; cz = (SizeZ + 1) / 2;
[Y, Z] = meshgrid(1:SizeY, 1:SizeZ);
a = SizeY / 2; b = SizeZ / 2;
R2 = ((Y - cy) / a).^2 + ((Z - cz) / b).^2;

sampleMask = true(SizeZ, SizeY);
if S.Elliptical
    sampleMask = R2 <= 1;
end

maskCalib = false(SizeZ, SizeY); %#ok<PREALL>
rY = S.CalibRegY / 2; rZ = S.CalibRegZ / 2;
R2calib = ((Y - cy) / rY).^2 + ((Z - cz) / rZ).^2;
maskCalib = R2calib <= 1 & sampleMask;

% Total desired number of samples from full Cartesian k-space
N_full = S.SizeY * S.SizeZ;
N_target = round(N_full / S.AccelFactor);
n_calib = nnz(maskCalib);
n_acq = round(N_target / S.ShotLength) * S.ShotLength;
n_acq = max(n_acq, n_calib);  % avoid going below calibration
n_random = n_acq - n_calib;

% Variable density map
vd = ones(SizeZ, SizeY);
if S.VariableDensity > 0
    R = sqrt(R2);
    vd = exp(-(R / 0.15).^S.VariableDensity);
end
vd(~sampleMask | maskCalib) = 0;
vd = vd / sum(vd(:));

[validZ, validY] = find(sampleMask & ~maskCalib);
weights = vd(sampleMask & ~maskCalib);
drawn = weightedSampleUnique(length(weights), weights, n_random);
subZ = validZ(drawn);
subY = validY(drawn);

mask = false(SizeZ, SizeY);
mask(sub2ind([SizeZ, SizeY], subZ, subY)) = true;
mask(maskCalib) = true;
[z, y] = find(mask);
samples = [y - floor(SizeY/2) - 1, z - floor(SizeZ/2) - 1];

end


% Unique weighted undersampling
function idx = weightedSampleUnique(N, w, k)

w = w(:) / sum(w); idx = zeros(k,1); avail = true(N,1);

for cnt = 1:k
    wCurr = w;
    wCurr(~avail) = 0;
    wCurr = wCurr / sum(wCurr);
    cdf = cumsum(wCurr);
    r = rand();
    sel = find(cdf >= r, 1, 'first');
    idx(cnt) = sel;
    avail(sel) = false;
end

end


% Split value into HI and LO 16-bit signed components
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
