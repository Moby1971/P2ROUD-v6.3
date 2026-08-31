% ------------------------------------------------------------------------------------
%  Pseudo radial k-space trajectory
%  For MR Solutions custom 3D k-space (pe1_order = 4: exLUT)
%
%  Gustav Strijkers
%  July 2025
%
% ------------------------------------------------------------------------------------



%% clear all

clc;
clearvars;
close all;
%#ok<*AGROW>



%% Initialization

dimy = 96;                      % k-space y dimension (no_views)
dimz = 96;                      % k-space z dimension (no_views_2)
order = 1;                      % 0 = one direction; 1 = back and forth,
angleNr = 9;                   % golden angle number (see list below)
display = true;                 % show result true / false
outputdir = './output/';        % output directory
exportList = true;              % export true / false
reps = 1;                       % list repeats
viewSpeed = 1000;               % view speed

% Tiny golden angles
tinyGoldenAngles = [111.24611, 68.75388, 49.75077, 38.97762, 32.03967, 27.19840, 23.62814, 20.88643, 18.71484, 16.95229];



%% Generate pseudo-radial spokes within elliptical mask

rev = 1;                
numPointsTarget = dimy * dimz;
numSamplesPerSpoke = 2 * max(dimy, dimz);
t = linspace(-1, 1, numSamplesPerSpoke);

ry = dimy / 2;
rz = dimz / 2;

kSpaceList = [];
angle = 0;
spokeNr = 0;

while size(kSpaceList,1) < numPointsTarget

    spokeNr = spokeNr + 1;

    % Golden angle increment
    angle = angle + tinyGoldenAngles(angleNr);
    theta = deg2rad(angle);

    % Spoke coordinates
    y = round(t * cos(theta) * ry);
    z = round(t * sin(theta) * rz);

    % Alternate spoke direction
    if order == 1 && mod(spokeNr, 2) == 0
        y = flip(y);
        z = flip(z);
    end

    % Remove duplicates from this spoke manually (preserving order)
    spoke = [y(:), z(:)];
    [~, ia] = unique(spoke, 'rows', 'stable');
    spoke = spoke(ia, :);

    % Keep only points within the elliptical mask
    inside = (spoke(:,1).^2 / ry^2 + spoke(:,2).^2 / rz^2) <= 1;
    spoke = spoke(inside, :);

    % Append
    kSpaceList = [kSpaceList; spoke];

    % Trim if needed
    if size(kSpaceList,1) > numPointsTarget
        kSpaceList = kSpaceList(1:numPointsTarget, :);
        break;
    end

end

% Unique sampled k-space points
[uniquePoints, ~, ic] = unique(kSpaceList, 'rows');
numUnique = size(uniquePoints, 1);
numTotal  = size(kSpaceList, 1);

% Average coverage per unique location
avgSamplesPerPoint = numTotal / numUnique;

% Total elliptical mask size
[Ygrid, Zgrid] = meshgrid(-floor(dimy/2):(ceil(dimy/2)-1), -floor(dimz/2):(ceil(dimz/2)-1));
ellipticalMask = (Ygrid.^2 / ry^2 + Zgrid.^2 / rz^2) <= 1;
numEllipticalPoints = nnz(ellipticalMask);

% Percentage of elliptical k-space covered at least once
coveredFraction = 100 * numUnique / numEllipticalPoints;



%% export matrix

if exportList

    if order == 1
        ord = 'r';
    else
        ord = 'o';
    end

    filename = strcat(outputdir,filesep,'exLUT_radial_y',num2str(dimy),'_z',num2str(dimz),'_a',num2str(round(tinyGoldenAngles(angleNr),2)),'_r',num2str(reps),'.txt');
    fileID = fopen(filename,'w');

    for i = 1:length(kSpaceList)

        fprintf(fileID,num2str(kSpaceList(i,1)));
        fprintf(fileID,'\n');
        fprintf(fileID,num2str(kSpaceList(i,2)));
        fprintf(fileID,'\n');

    end

    fclose(fileID);

end



%% Display the trajectory true/false

if display

    % Parameters
    pixelSize = 10;
    figWidth  = dimy * pixelSize;
    figHeight = dimz * pixelSize;

    % Create fixed-size figure
    figure(11);
    clf;
    set(gcf, 'Color', 'k', ...
        'Units', 'pixels', ...
        'Position', [100 100 figWidth figHeight], ...
        'Resize', 'off');

    % Layout parameters
    cbWidth = 15;        % color bar width
    margin      = 40;    % margin between elements
    titleHeight = 30;    % vertical space for title

    % Axes size
    axLeft   = margin;
    axBottom = margin;
    axWidth  = figWidth - cbWidth - 3 * margin;
    axHeight = figHeight - titleHeight - 2 * margin;

    % Set up axes
    ax = axes('Units', 'pixels', 'Position', [axLeft axBottom axWidth axHeight], 'Color', 'k');
    axis off;
    set(gca, 'YDir', 'normal');

    % Initialize k-space display
    frameMask = zeros(dimz, dimy);
    img = imagesc(frameMask, [0 1]);
    baseMap = parula(255);  % or turbo(255), jet(255), etc.
    blackFirst = [0 0 0; baseMap];
    colormap(blackFirst);
    xlim([0.5 dimy+0.5]);
    ylim([0.5 dimz+0.5]);

    % Animate
    ky_idx = kSpaceList(:,1) + floor(dimy/2) + 1;
    kz_idx = kSpaceList(:,2) + floor(dimz/2) + 1;

    for cnt = 1:size(kSpaceList,1)
        y = ky_idx(cnt);
        z = kz_idx(cnt);
        if y >= 1 && y <= dimy && z >= 1 && z <= dimz
            frameMask(z, y) = frameMask(z, y) + 1;
            img.CData = frameMask;
            cmax = max(frameMask(:));
            img.Parent.CLim = [0.5, max(1, cmax)];
            pause(1/viewSpeed);
        end
    end

    % Colorbar
    cbLeft = axLeft + axWidth + margin;
    cbHeight = round(0.4 * axHeight);
    cbBottom = axBottom + round((axHeight - cbHeight)/2);
    cb = colorbar('Units', 'pixels', 'Position', [cbLeft cbBottom cbWidth cbHeight]);
    cb.Label.String = '# samples per k-space location';
    cb.Label.Color  = 'w';
    cb.Color        = 'w';

    % Title
    annotation('textbox', ...
        [0, 1 - titleHeight/figHeight, 1, titleHeight/figHeight], ...
        'String', 'Pseudo-radial k-space fill', ...
        'HorizontalAlignment', 'center', ...
        'Color', 'w', ...
        'FontSize', 16, ...
        'EdgeColor', 'none', ...
        'BackgroundColor', 'k');

end



%% Print summary

fprintf('\n--- k-space Trajectory Summary ---\n');
fprintf('Trajectory type     : Pseudo-radial\n');
fprintf('Dimensions (ky × kz): %d × %d\n', dimy, dimz);
fprintf('Total samples       : %d\n', numTotal);
fprintf('Unique positions    : %d / %d (%.1f%% coverage of elliptical mask)\n', numUnique, numEllipticalPoints, coveredFraction);
fprintf('Avg samples/point   : %.2f\n', avgSamplesPerPoint);
fprintf('Spoke direction     : %s\n', ternary(order==1, 'Alternating', 'Unidirectional'));
fprintf('Golden angle used   : %.5f° (index %d)\n', tinyGoldenAngles(angleNr), angleNr);
fprintf('Effective spokes    : %d\n', spokeNr);
fprintf('Revolutions approx. : %.2f\n', angle / 360);
fprintf('Output file         : %s\n', filename);
fprintf('----------------------------------\n\n');

function out = ternary(cond, valTrue, valFalse)
    if cond
        out = valTrue;
    else
        out = valFalse;
    end
end
