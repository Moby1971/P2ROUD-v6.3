% What a diffusion acquisition can be analysed with
%
% Author : Gustav Strijkers
% Date   : 2026-09-16

function scheme = diffusionScheme(bValues, directions)

    % Purpose:
    %   Say what a diffusion series supports, so that the script written beside the
    %   images fits the scan in hand rather than the one it was first written for.
    %
    % How it works:
    %   Two numbers decide everything.
    %
    %   How many shells were measured decides how many tissues can be separated. A
    %   multi-shell fit holds no more tissues than the acquisition has distinct b
    %   values, counting b = 0 as one of them: two shells and a b = 0 allow white
    %   matter, grey matter and fluid, one shell and a b = 0 allow two of them. A third
    %   tissue on one shell is not refused -- msmt_csd fits it and says nothing -- it is
    %   simply shared out arbitrarily between tissues the data cannot tell apart.
    %
    %   How many directions were measured decides the highest spherical harmonic order
    %   the data carry: order l needs (l+1)(l+2)/2 of them, so 6 directions reach order
    %   2, 15 reach 4, 28 reach 6 and 45 reach 8. Nothing refuses this either: asked for
    %   an orientation distribution from 6 directions, msmt_csd returns one of order 8,
    %   45 coefficients fitted to 6 measurements, which tracks and looks like a result.
    %   That is worse than an error, so below 15 directions the tensor is fitted and
    %   tracked instead -- which is what a 6 direction scan is for, and it tracks
    %   perfectly well, one direction to a voxel.
    %
    %   A tensor needs a b = 0 to divide by and 6 directions that between them fix all
    %   six of its components: six directions in a plane, or the same direction six
    %   times, are still not a tensor, so the design matrix is checked for rank rather
    %   than the directions merely counted.
    %
    %   Directions are counted as lines rather than arrows, since a diffusion gradient
    %   and its opposite measure the same thing, and per shell, since that is how a
    %   multi-shell fit uses them.
    %
    % Inputs:
    %   bValues    - nVolumes x 1, s/mm2
    %   directions - nVolumes x 3 unit vectors, zero where b is zero
    %
    % Output:
    %   scheme - what the acquisition is and what it supports:
    %              shells      the b values measured, rounded, ascending
    %              nShells     how many of them
    %              nB0         volumes without diffusion weighting
    %              nWeighted   volumes with it
    %              nDirections directions in the best filled shell
    %              nUnique     directions over the whole series
    %              lmax        the highest order those directions carry, 0 below 6
    %              tensor      true when a tensor can be fitted
    %              fod         true when an orientation distribution is worth fitting
    %              tissues     the tissues a multi-shell fit can separate here
    %              algorithm   what to track with, '' for the default from a
    %                          distribution

scheme = struct('shells', [], 'nShells', 0, 'nB0', 0, 'nWeighted', 0, ...
    'nDirections', 0, 'nUnique', 0, 'lmax', 0, 'tensor', false, 'fod', false, ...
    'tissues', {{}}, 'algorithm', '');

if isempty(bValues)
    return
end

bValues = bValues(:);

if isempty(directions)
    directions = zeros(numel(bValues), 3);
end

bValues(~isfinite(bValues)) = 0;
directions(~isfinite(directions)) = 0;
weighted = bValues > 0;
scheme.nB0 = nnz(~weighted);
scheme.nWeighted = nnz(weighted);
scheme.shells = unique(round(bValues(weighted)/100)*100)';
scheme.nShells = numel(scheme.shells);

% The best filled shell, since that is the one an orientation distribution is fitted to
for shell = scheme.shells

    onThisShell = weighted & round(bValues/100)*100 == shell;
    scheme.nDirections = max(scheme.nDirections, countDirections(directions(onThisShell,:)));

end

% A tensor is fitted to all the weighted volumes together, so it is all of their
% directions that have to fix its six components
[scheme.nUnique, unique3D] = countDirections(directions(weighted,:));
scheme.lmax = highestOrder(scheme.nDirections);
scheme.tensor = scheme.nB0 >= 1 && scheme.nUnique >= 6 && fixesATensor(unique3D);
scheme.fod = scheme.tensor && scheme.lmax >= 4;

if scheme.fod && scheme.nShells >= 2
    scheme.tissues = {'wm', 'gm', 'csf'};
elseif scheme.fod
    scheme.tissues = {'wm', 'csf'};
end

if scheme.fod
    scheme.algorithm = '';
elseif scheme.tensor
    scheme.algorithm = 'Tensor_Det';
end

end % diffusionScheme



function [n, kept] = countDirections(directions)

% How many directions these are, counting a direction and its opposite as one, and
% which they are

n = 0;
kept = zeros(0, 3);

if isempty(directions)
    return
end

lengths = sqrt(sum(directions.^2, 2));
directions = directions(lengths > 0, :)./lengths(lengths > 0);

if isempty(directions)
    return
end

% A gradient and its opposite measure the same thing, so turn each one the same way
% round before they are counted
for k = 1:size(directions, 1)

    first = find(abs(directions(k,:)) > 1e-6, 1, 'first');

    if ~isempty(first) && directions(k,first) < 0
        directions(k,:) = -directions(k,:);
    end

end

kept = unique(round(directions, 3), 'rows');
n = size(kept, 1);

end % countDirections



function fixed = fixesATensor(directions)

% Whether these directions between them fix all six components of a tensor
%
% Six directions are the fewest a tensor can be fitted from, but only if they point in
% six different enough ways: the signal along a direction g holds the tensor as the
% six products of its components, and it is those six that have to be separable. Six
% directions in a plane, or spread over a cone, leave the design matrix short of rank
% and the fit is then a guess dressed as a measurement.

fixed = false;

if size(directions, 1) < 6
    return
end

design = [directions(:,1).^2, directions(:,2).^2, directions(:,3).^2, ...
    2*directions(:,1).*directions(:,2), 2*directions(:,1).*directions(:,3), ...
    2*directions(:,2).*directions(:,3)];

fixed = rank(design) == 6;

end % fixesATensor



function lmax = highestOrder(nDirections)

% The highest even spherical harmonic order (l+1)(l+2)/2 coefficients fit into

lmax = 0;

for l = 2:2:8

    if (l + 1)*(l + 2)/2 <= nDirections
        lmax = l;
    end

end

end % highestOrder
