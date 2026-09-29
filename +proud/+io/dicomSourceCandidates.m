% Where the scanner's DICOM images of a scan might be
%
% Author : Gustav Strijkers
% Date   : 2026-09-29

function candidates = dicomSourceCandidates(mrdImportPath)

% Purpose:
%   List the folders the scanner's DICOM images of a scan could be in, in the order
%   they are tried, each paired with the folder an export goes to when they are found
%   there.
%
% How it works:
%   MR Solutions keeps the MRD files and the DICOM images side by side:
%
%     <base>/MRD/<study>/<scan>/            the import folder
%     <base>/Data/<study>/DICOM/<scan>/     its DICOM images, or in a series
%                                           folder 1, 2 or 3 below it
%
%   and the export goes into <base>/Data/<study>/, beside the scanner's DICOM folder.
%   The layout is found on whole path components: the last component named MRD with
%   a study and a scan after it. The app did this on text, replacing every "MRD" in the
%   path by "Data" and then taking the first "Data"; a path with "Data" or "MRD" in it
%   before that, such as /Users/me/Data/MRD/343/8455/, failed on it and fell back to
%   the import folder, and with DICOM images found there the export folder came out
%   empty.
%
%   A path without that shape is searched in the import folder itself and its series
%   folders 1 to 3, and the export goes beside the import folder, into its parent.
%
% Inputs:
%   mrdImportPath - char or string, the folder the MRD file was read from, with or
%                   without a trailing separator
%
% Output:
%   candidates - struct array with fields search and export, both char ending in a
%                separator; empty for an empty import path

candidates = struct('search', {}, 'export', {});
importPath = char(mrdImportPath);
if isempty(importPath)
    return
end

parts = strsplit(importPath, {'/', '\'});
parts = parts(~cellfun(@isempty, parts));      % the separators at the ends, and doubled ones
lead = '';
if any(importPath(1) == '/\')
    lead = filesep;                 % an absolute path starts with a separator
    if numel(importPath) > 1 && any(importPath(2) == '/\')
        lead = [filesep filesep];   % and a network path with two
    end
end
join = @(p) [lead, strjoin(p, filesep), filesep];

mrd = find(strcmp(parts, 'MRD'));
mrd = mrd(mrd + 2 <= numel(parts));
if ~isempty(mrd)
    m = mrd(end);
    study = [parts(1:m-1), {'Data'}, parts(m+1)];
    source = join([study, {'DICOM'}, parts(m+2)]);
    export = join(study);
else
    source = join(parts);
    export = join(parts(1:end-1));
end

candidates(end+1) = struct('search', source, 'export', export);
for series = 1:3
    candidates(end+1) = struct('search', [source, num2str(series), filesep], 'export', export); %#ok<AGROW>
end

end % dicomSourceCandidates
