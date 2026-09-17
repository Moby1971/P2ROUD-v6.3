% Put the scanner's gradient directions into the sense DICOM means by them
%
% Author : Gustav Strijkers
% Date   : 2026-09-16

function correctGradientTable(folder, reporter)

    % Purpose:
    %   Correct the sign of the gradient directions in the .bvec file the NIfTI export
    %   writes, so that the table the analysis reads agrees with the images.
    %
    % How it works:
    %   Tag (0018,9089) is defined in the patient frame, and dicm2nii converts it into
    %   the image frame correctly. What the scanner puts into it does not match that
    %   definition along the anterior-posterior axis: on scan 32518 the tag reads
    %   [-0.231 0.447 0.864] and the .bvec beside the images [-0.231 -0.447 0.864], the
    %   conversion having negated y for this geometry, and it is the table with y the
    %   other way round that the images agree with.
    %
    %   Measured with MRtrix's dwigradcheck, which tracks with every permutation and
    %   every sign of the table and takes the mean streamline length. On this scan as
    %   exported, 5.81 mm, against 9.87 mm for the same table with y negated. On the
    %   scanner's own reconstruction of the same scan with the scanner's own table,
    %   7.88 against 11.74. With y negated the check ranks the table it is given first,
    %   with no flip and no permutation, so what is left is consistent.
    %
    %   It is the scanner's convention and not something the reconstruction does: the
    %   images this app writes are the scanner's own, and correlate with them at 0.80
    %   as they lie against 0.63 mirrored. The DICOM files are therefore left exactly
    %   as the scanner writes them, and only the table the analysis reads is put right.
    %
    %   The correction is a reflection in the anterior-posterior axis, written in the
    %   image axes the .bvec uses, so that it holds for a stack in any orientation and
    %   not only for the axial ones it was measured on.
    %
    % Inputs:
    %   folder   - the folder the NIfTI export wrote to
    %   reporter - proud.Reporter for the log; omit or pass empty to run silent
    %
    % Output:
    %   none; the .bvec files in the folder are rewritten

if nargin < 2 || isempty(reporter)
    reporter = proud.Reporter();
end

files = dir(fullfile(folder, '*.bvec'));

for k = 1:numel(files)

    stem = regexprep(files(k).name, '\.bvec$', '');
    image = imageBeside(folder, stem);

    if isempty(image)
        continue
    end

    table = readmatrix(fullfile(folder, files(k).name), 'FileType', 'text');

    if size(table, 1) ~= 3 || isempty(table)
        continue
    end

    reflection = apReflection(image);
    table = reflection*table;

    writematrix(table, fullfile(folder, files(k).name), 'FileType', 'text', ...
        'Delimiter', ' ', 'WriteMode', 'overwrite');

    reporter.message(strcat("Gradient directions corrected in ", string(files(k).name), " ..."), 1);

end

end



function file = imageBeside(folder, stem)

% The image the table belongs to, whose header says how its axes lie

file = '';
candidates = {strcat(stem, '.nii'), strcat(stem, '.nii.gz')};

for k = 1:numel(candidates)

    if isfile(fullfile(folder, candidates{k}))
        file = fullfile(folder, candidates{k});
        return
    end

end

end



function reflection = apReflection(image)

% Reflecting the anterior-posterior axis, expressed in the image's own axes
%
% The columns of the header's matrix are the image axes in the scanner frame, where y
% is anterior. Taking the directions there, turning y round and bringing them back
% gives a sign on one row for a stack that lies along the axes, and the right thing
% for one that does not.

reflection = diag([1 -1 1]);
header = niftiinfo(image);
matrix = [header.raw.srow_x; header.raw.srow_y; header.raw.srow_z];
axes = double(matrix(:,1:3));
lengths = sqrt(sum(axes.^2, 1));

if any(lengths < eps) || abs(det(axes)) < eps
    return
end

axes = axes./lengths;
reflection = axes\(diag([1 -1 1])*axes);
reflection(abs(reflection) < 1e-9) = 0;

end
