% Put the dynamics of a ZTE series in the same place
%
% Author : Gustav Strijkers
% Date   : 2026-09-17

function [series, motion] = zteRegisterDynamics(series, reporter)

    % Purpose:
    %   Register the dynamics of a ZTE series to one another, for a time course of an
    %   animal that moves.
    %
    % How it works:
    %   Each dynamic is located against the mean of the series by cross-correlation
    %   (proud.reco.epiVolumeShift, which finds the translation to a small part of a
    %   voxel, whatever the brightness of the dynamic) and moved there by a linear phase
    %   in its own Fourier transform, which shifts by a part of a voxel without the
    %   blurring an interpolation adds. The mean is then taken again from the moved
    %   dynamics and the measurement repeated once: the first mean is blurred by the
    %   very motion it is meant to take out.
    %
    %   In three dimensions. A ZTE volume is encoded in all three, so a linear phase
    %   along any of them moves the object -- unlike the stack of 2D slices of an EPI
    %   series, which epiRegisterVolumes moves in plane only.
    %
    %   Translation only. On 26876, a fixed animal, the motion is a fiftieth of a voxel
    %   (section 36.7) and there is nothing to correct: this is for animals that are
    %   awake or poorly fixed, and it is off unless it is asked for.
    %
    %   A dynamic at a time, and in place: the series is not copied, the mean is summed
    %   one dynamic after another, and an abort stops at the next dynamic with the ones
    %   already moved kept.
    %
    % Inputs:
    %   series   - the complex series, [x y z dynamics]
    %   reporter - proud.Reporter for the log and the abort; omit or pass empty to run
    %              silent
    %
    % Outputs:
    %   series - the series with its dynamics registered
    %   motion - the move of each dynamic in voxels, [dynamics 3]: where it was sampled
    %            to lie on the reference

if nargin < 2 || isempty(reporter)
    reporter = proud.Reporter();
end

[dimX, dimY, dimZ, dimD] = size(series, 1, 2, 3, 4);
motion = zeros(dimD, 3);

if dimD < 2 || numel(series) ~= dimX*dimY*dimZ*dimD
    return
end

reporter.message('Registering the ZTE dynamics ...');

% The frequencies of each axis, in cycles per voxel, in the order fftn keeps them
[X, Y, Z] = ndgrid(frequencies(dimX), frequencies(dimY), frequencies(dimZ));
stopped = false;

for pass = 1:2

    % The mean of the series as it lies now, summed a dynamic at a time
    reference = zeros(dimX, dimY, dimZ, 'like', real(series(1)));

    for dynamic = 1:dimD
        reference = reference + abs(series(:,:,:,dynamic));
    end

    reference = reference/dimD;

    for dynamic = 1:dimD

        if reporter.aborted('reco')
            stopped = true;
            break
        end

        step = proud.reco.epiVolumeShift(abs(series(:,:,:,dynamic)), reference);

        if any(abs(step) > 1e-3)
            % epiVolumeShift says where the dynamic has to be sampled to lie on the
            % reference, so the phase goes the other way
            ramp = exp(2i*pi*(step(1)*X + step(2)*Y + step(3)*Z));
            series(:,:,:,dynamic) = ifftn(fftn(series(:,:,:,dynamic)).*ramp);
            motion(dynamic,:) = motion(dynamic,:) + step;
        end

    end

    if stopped
        break
    end

end

reporter.message(strcat("Dynamics registered, largest move ", num2str(max(abs(motion(:))), 2), ...
    " voxels, median ", num2str(median(sqrt(sum(motion.^2, 2))), 2), " ..."));

end % zteRegisterDynamics



function f = frequencies(n)

% The frequencies of an n point transform in the order fftn keeps them, in cycles per
% voxel

f = ((0:n-1) - n*((0:n-1) >= ceil(n/2)))/n;

end % frequencies
