% ------------------------------------------------------------------------------------
%  Pseudo spiral k-space trajectory
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



%% Initialization

dimy = 96;                      % k-space y dimension (no_views)
dimz = 96;                      % k-space z dimension (no_views_2)
order = 1;                      % 0 = one direction; 1 = back and forth,
angleNr = 4;                    % golden angle number (see list below)
display = true;                 % show result true / false
outputdir = './output/';        % output directory
exportList = true;              % export true / false
reps = 1;                       % list repeats
viewSpeed = 1000;               % view speed

% Tiny golden angles
tinyGoldenAngles = [111.24611, 68.75388, 49.75077, 38.97762, 32.03967, 27.19840, 23.62814, 20.88643, 18.71484, 16.95229];



%% Make a spiral

rev = 1;                      
angle = 0;
numberOfSpiralPoints = 256;

% Start with same x and y radius
dimYZ = 256;
radiusY = floor(dimYZ/2);
radiusZ = floor(dimYZ/2);
center = [radiusY,radiusZ];

% Last point on spiral
edge = center + [round(radiusY * cosd(angle)),round(radiusZ * sind(angle))];

% Radius of first point to second
r = norm(edge-center);

% Angle between two point wrt the y-axis
thetaOffset = tan((edge(2)- center(2))/(edge(1)-center(1)));

% Radius with nonlinear growth to reduce center crowding
gamma = 0.8;  % controls center tapering (0.7–0.9 works well)
t = linspace(0, 1, numberOfSpiralPoints).^gamma * (dimYZ/2 - 1);  % from 0 to edge

% Angle for full revolutions
theta = linspace(0, 2*pi*rev, numberOfSpiralPoints);

% Optional random base rotation to reduce artifacts
theta = theta + deg2rad(rand() * 360);

% Spiral coordinates
y0 = cos(theta) .* t + center(1);
z0 = sin(theta) .* t + center(2);



%% Repeat with golden angle increments

ky = [];
kz = [];
numberOfSpirals = 2000;

for ns = 1:numberOfSpirals

    % Cumulative golden angle to break periodic overlap
    angle = angle + tinyGoldenAngles(angleNr);  % allow >360°


    % Rotate the spiral
    y =  (y0-center(1))*cosd(angle) + (z0-center(2))*sind(angle) + center(1);
    z = -(y0-center(1))*sind(angle) + (z0-center(2))*cosd(angle) + center(2);

    % Scale to correct y and z dimensions;
    y = y * dimy/dimYZ;
    z = z * dimz/dimYZ;

    if order == 1 && mod(ns,2) == 0
        y = flip(y);
        z = flip(z);
    end

    % Add the spiral to the list
    ky = [ky, y]; %#ok<*AGROW>
    kz = [kz, z];

end



%% Discretize and remove repeats

% Discretize
ky = floor(ky - dimy/2);
kz = floor(kz - dimz/2);

% List of k-space points
kSpaceList = [ky',kz'];

% Remove repeats
for i = 1:100
    idx = find(~any(diff(kSpaceList), 2))+1;
    kSpaceList(idx, :) = [];
end

% Limit number of [0 0]s vy removing half of them
loc = find(kSpaceList(:,1) == 0 & kSpaceList(:,2)==0);
loc = loc(1:2:end);
kSpaceList(loc,:) = [];

kSpaceList = kSpaceList(1:dimy*dimz*reps,:);

% Unique points and density
[uniquePoints, ~, ic] = unique(kSpaceList, 'rows');
numUnique = size(uniquePoints, 1);
numTotal  = size(kSpaceList, 1);
avgSamplesPerPoint = numTotal / numUnique;

% Elliptical mask size (for fill percentage)
ry = dimy / 2;
rz = dimz / 2;
[Ygrid, Zgrid] = meshgrid(-floor(dimy/2):(ceil(dimy/2)-1), -floor(dimz/2):(ceil(dimz/2)-1));
ellipticalMask = (Ygrid.^2 / ry^2 + Zgrid.^2 / rz^2) <= 1;
numEllipticalPoints = nnz(ellipticalMask);
coveredFraction = 100 * numUnique / numEllipticalPoints;

% Estimate number of spirals used
effectiveSpirals = floor(numTotal / numberOfSpiralPoints);



%% export matrix

if exportList

    if order == 1
        ord = 'r';
    else
        ord = 'o';
    end

    filename = strcat(outputdir,filesep,'exLUT_spiral_y',num2str(dimy),'_z',num2str(dimz),'_a',num2str(round(tinyGoldenAngles(angleNr),2)),'_r',num2str(reps),'.txt');
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
        'String', 'Pseudo-spiral k-space fill', ...
        'HorizontalAlignment', 'center', ...
        'Color', 'w', ...
        'FontSize', 16, ...
        'EdgeColor', 'none', ...
        'BackgroundColor', 'k');

end



%% Print summary

fprintf('\n--- k-space Trajectory Summary ---\n');
fprintf('Trajectory type        : Pseudo-spiral\n');
fprintf('Dimensions (ky × kz)   : %d × %d\n', dimy, dimz);
fprintf('Total samples          : %d\n', numTotal);
fprintf('Unique positions       : %d / %d (%.1f%% elliptical coverage)\n', numUnique, numEllipticalPoints, coveredFraction);
fprintf('Avg samples/point      : %.2f\n', avgSamplesPerPoint);
fprintf('Spiral direction       : %s\n', ternary(order==1, 'Alternating', 'Unidirectional'));
fprintf('Golden angle used      : %.5f° (index %d)\n', tinyGoldenAngles(angleNr), angleNr);
fprintf('Effective spirals      : %d\n', effectiveSpirals);
fprintf('Revolutions per spiral : %d\n', rev);
fprintf('Output file            : %s\n', filename);
fprintf('----------------------------------\n\n');

function out = ternary(cond, valTrue, valFalse)
    if cond
        out = valTrue;
    else
        out = valFalse;
    end
end