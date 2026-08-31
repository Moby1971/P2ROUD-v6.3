%% 2D undersampled k-space maker using Gaussian weighting and PSF selection
%
% Gustav Strijkers
% g.j.strijkers@amsterdamumc.nl
% July 2025
%

clearvars;
close all;
clc;


%% User input

sizeOfKspace = [256, 256];      % Size of k-space phase encoding readout x phase encoding (readout is merely for display purposes)
nTrials = 1000;                 % Number of times the mask is generated, to choose the best one
sizeOfCenter = 32;              % Number of center-filled lines (must be even)
xFactor = 2.5;                  % Acceleration factor
gaussSigma = 0.15;              % Gaussian std-dev relative to PE size (e.g., 0.3 = 30% width)
outputFolder = "./output/";     % Output folder
showKspace = true;              % Show the k-space filling (true/false)
speed = 100000;


%% Generate 100 masks and select best based on PSF

bestScore = inf;
bestMask = [];
bestSamples = [];
bestPSF = [];

for trial = 1:nTrials

    rng('shuffle');

    [mask, samples] = lineBasedPattern('SizeRO', sizeOfKspace(1), ...
        'SizePE', sizeOfKspace(2), 'AccelFactor', xFactor, ...
        'CenterLines', sizeOfCenter, 'GaussSigma', gaussSigma);

    % Average across RO direction
    pe_profile = mean(mask, 1);  % size: 1 x PE
    psf = abs(fftshift(ifft(pe_profile)));

    % Define a simple score: mainlobe width + max sidelobe
    mainLobeWidth = sum(psf > 0.5 * max(psf));  % half-max width
    sideLobeLevel = max(psf(psf < max(psf)));   % max outside the main lobe

    score = mainLobeWidth + sideLobeLevel;
    if score < bestScore
        bestScore = score;
        bestMask = mask;
        bestSamples = samples;
        bestPSF = psf;
    end

end

% Final selection
mask = bestMask;
samples = bestSamples;


%% Display the final mask and PSF

AF = numel(mask) / nnz(mask);
NE = size(samples,1);

if showKspace

    figure(12); clf;
    subplot(1,2,1);
    frameMask = false(size(mask));
    img = imagesc(frameMask);
    colormap(gray);
    clim([0 1]);
    axis image off;
    title({'Mask'; ['R = ', num2str(AF,4)]; ['N = ', num2str(NE)]}, 'FontSize', 14);

    % Extract unique ky lines
    ky = unique(samples(:,1));
    ky_idx = ky + floor(sizeOfKspace(2)/2) + 1;
    ky_idx = ky_idx(ky_idx >= 1 & ky_idx <= sizeOfKspace(2));

    for cnt = 1:length(ky_idx)
        frameMask(:, ky_idx(cnt)) = true;
        img.CData = frameMask;
        pause(1/speed);
    end

    subplot(1,2,2);
    plot(bestPSF, 'k-', 'LineWidth', 1.5);
    title('Point Spread Function', 'FontSize', 14);
    xlabel('Pixel'); ylabel('Amplitude');
    xlim([0 sizeOfKspace(2)]);
    grid on;

end


%% Export LUT (kz = 0 always)

filename = strcat(outputFolder,"nrLUT_2D_R",num2str(AF,2),"_",num2str(sizeOfKspace(2)),".txt");
fileID = fopen(filename,'w');

[l16, h16] = split32to16(NE);
fprintf(fileID,[num2str(l16),'\n']);
fprintf(fileID,[num2str(h16),'\n']);

for cnt = 1:NE
    fprintf(fileID,[num2str(samples(cnt,1)),'\n']);
    fprintf(fileID,"0\n");
end

fclose(fileID);


%% Summary

fprintf('\n------- k-space summary -------\n');
fprintf('K-space size       : %d x %d\n', sizeOfKspace(1), sizeOfKspace(2));
fprintf('Center lines       : %d\n', sizeOfCenter);
fprintf('Acceleration       : %.2f\n', AF);
fprintf('Encodes (lines)    : %d\n', NE);
fprintf('Gaussian sigma     : %.2f (%.1f%% of PE size)\n', gaussSigma, 100*gaussSigma);
fprintf('Trials run         : %d\n', nTrials);
fprintf('Best score         : %.3f\n', bestScore);
fprintf('Output file        : %s\n\n', filename);


%% Line-based pattern generator

function [mask, samples] = lineBasedPattern(varargin)

p = inputParser;
addParameter(p,'SizeRO',256,@isnumeric);
addParameter(p,'SizePE',256,@isnumeric);
addParameter(p,'AccelFactor',4,@isnumeric);
addParameter(p,'CenterLines',32,@isnumeric);
addParameter(p,'GaussSigma',0.3,@isnumeric);
parse(p,varargin{:});
S = p.Results;

SizeRO = S.SizeRO;
SizePE = S.SizePE;
cy = (SizePE + 1) / 2;

% Number of total unique PE lines
N_total_lines = round(SizePE / S.AccelFactor);

% Center region
y1 = round(cy - S.CenterLines/2);
y2 = round(cy + S.CenterLines/2 - 1);
centerLines = y1:y2;
N_center = numel(centerLines);

if N_center > N_total_lines
    error("Center region too large for requested acceleration.");
end

% Draw remaining lines
N_draw = N_total_lines - N_center;
allLines = 1:SizePE;
availableLines = setdiff(allLines, centerLines);

ky = (-SizePE/2):(SizePE/2 - 1);
sigma = S.GaussSigma * SizePE;
w = exp(-0.5 * (ky / sigma).^2);
w = w / sum(w);
w = w(availableLines);

drawnIdx = weighted_sample_unique(availableLines, w, N_draw);
selectedLines = sort([centerLines(:); drawnIdx(:)]);

mask = false(SizeRO, SizePE);
mask(:,selectedLines) = true;

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


%% Weighted sampling

function idx = weighted_sample_unique(domain, weights, k)
weights = weights(:) / sum(weights);
N = length(domain);
idx = zeros(k,1);
available = true(N,1);

for i = 1:k
    w_curr = weights;
    w_curr(~available) = 0;
    w_curr = w_curr / sum(w_curr);
    cdf = cumsum(w_curr);
    r = rand();
    sel = find(cdf >= r, 1, 'first');
    idx(i) = domain(sel);
    available(sel) = false;
end
end