% Measure the 3D UTE readout trajectory per gradient axis from scans of a small object
%
% Author : Gustav Strijkers
% Date   : 2026-09-27

function result = measureUteTrajectory(scans, varargin)

    % Purpose:
    %   The k-space trajectory of a 3D UTE readout, per gradient axis, measured on
    %   scans of a small object placed off centre, and written as a three column
    %   ktraj.txt that Retrospective and P2ROUD read from their settings folder.
    %
    % How it works:
    %   A small object at r gives, on a spoke of direction n at readout sample t,
    %   the signal S(t) = A(t) exp(-2 pi i q(t) . n) with q_a(t) = k_a(t) r_a: its
    %   phase over the spokes is linear in the direction, with a slope that is k
    %   times the position, per axis. At every sample the q that makes all spokes
    %   coherent (a matched filter over the spokes) is found, starting at q = 0
    %   where k has not yet moved and following it sample by sample. A phase that
    %   is the same on every spoke -- off-resonance, receiver phase, drift -- does
    %   not enter the coherence at all. The measurement stops where the coherence
    %   falls below MinCoherence, which for an object of a few voxels is where its
    %   own k-space signal has gone.
    %
    %   k and position enter only as a product, so the position is needed, and it
    %   has to come from something other than an assumed trajectory:
    %
    %     "plateau" (the default) On the plateau of the readout k rises by the
    %               plateau slope gp of the default profile per sample, whatever the
    %               ramp before it did, so there q_a(t) = r_a (gp t + c_a) and r_a is
    %               the slope of q_a over t divided by gp. That needs the object to
    %               stay coherent into the plateau: a small object with a long T2.
    %               The plateau samples are those after the default profile's
    %               gradient has reached PlateauFraction of its plateau.
    %     given     'Positions', in mm, measured some other way.
    %     "image"   An image made with the default profile (BART's inverse NUFFT on
    %               a 128 grid, in the axes of the LUT). A fallback only: the image of
    %               an object made with a trajectory that is off is scaled by the
    %               ratio of the true to the assumed k, so these positions, and the
    %               scale of the measured k with them, follow the default profile.
    %               Refining them with the fitted trajectory does not converge (on
    %               33335 the z position ran from 17.6 to 11.5 mm in four rounds):
    %               k and r trade against each other.
    %
    %   Each axis's sign is chosen so that k increases along the readout, which
    %   removes any sign convention between the data, the image and the LUT.
    %
    %   Per axis, only scans in which the object lies at least MinOffset mm off centre
    %   on that axis are used, each weighted by that offset squared (the precision of
    %   k from a phase). Four models are fitted, all with the plateau slope of the
    %   default profile, since the plateau cannot be measured this way (it is
    %   degenerate with the image scale):
    %
    %     shift    the default profile delayed per axis
    %     stretch  the default profile delayed, and its ramp stretched, per axis
    %     linear   a linear gradient ramp: start and length per axis
    %     sine     a sine gradient ramp: start and length per axis
    %
    %   The written profile starts at data sample DataOffset + 1, which is the data
    %   offset to reconstruct with, and has as many rows as the default profile or
    %   as the readout has samples left, whichever is fewer. Use it with zero Gx, Gy
    %   and Gz delays.
    %
    %   This is the method of P2ROUD6's status sections 20.5 and 99.1. Fitting a
    %   trajectory to the data consistency of a reconstruction does not work on real
    %   data (P2ROUD6 section 20.3); measuring it does.
    %
    % Protocol:
    %   A small object -- a bead or thin capillary of about 1 to 3 voxels -- scanned
    %   with the UTE protocol whose trajectory is wanted, unchanged, at positions that
    %   together lie well off centre on every axis, on both sides if possible.
    %
    % Inputs:
    %   scans - scan folders or MRD files (string array); each folder holds one
    %           *.MRD and the lut*.txt of the scan. Or a struct array with the data
    %           themselves, as a test builds them: raw (samples x experiments), lut
    %           (3 x experiments, int16 scaled), fov (mm) and name
    %   Name-value options:
    %     'DataOffset'   data samples skipped before the profile starts; default:
    %                    the sample before the directed spokes' mean magnitude first
    %                    reaches 90 % of its maximum over samples 4 on
    %     'Positions'    object positions, mm, one row [x y z] per scan in the axes
    %                    of the LUT; when given, PositionMethod is not used
    %     'PositionMethod' "plateau" (default) or "image", see above
    %     'PlateauFraction' the fraction of its plateau the default profile's
    %                    gradient must have reached for a sample to count as on
    %                    the plateau; default 0.95
    %     'MinPlateauSamples' coherent plateau samples needed per scan; default 8
    %     'Model'        "best" (default: the lowest weighted rms), "shift",
    %                    "stretch", "linear" or "sine"
    %     'MinCoherence' coherence below which a sample is not used; default 0.85
    %     'MinOffset'    mm off centre for an axis to be measured on a scan; default 5
    %     'Output'       ktraj.txt to write; default: none
    %     'Plot'         true for a figure of the measured and fitted k; default false
    %     'Reporter'     function handle taking a message; default fprintf
    %
    % Output:
    %   result - struct: profile (N x 3), dataOffset, model, fits (per model: the
    %            parameters per axis and the weighted rms per axis), scans (per scan:
    %            file, fov, position, samples, q, coherence, k), positionsFrom

    opts = parseOptions(varargin{:});
    say = opts.Reporter;
    if ~isstruct(scans)
        scans = string(scans);
    end
    default = defaultProfile();

    % --- Measure q(t) on every scan -------------------------------------------------
    meas = struct([]);
    for j = 1:numel(scans)
        if isstruct(scans)
            file = string(scans(j).name); raw = double(scans(j).raw); fov = scans(j).fov; lut = scans(j).lut;
        else
            [file, lutFile] = scanFiles(scans(j));
            [raw, fov] = readScan(file);                   % samples x experiments
            lut = reshape(load(lutFile), 3, []);
        end
        lut = lut(:, 1:size(raw, 2));
        directed = vecnorm(lut, 2, 1) > 32767 / 2;         % as retro.traj.uteDirectedSpokes
        S = raw(:, directed);
        n = lut(:, directed) / 32767;
        m = mean(abs(S), 2);
        if isempty(opts.DataOffset)
            ref = max(m(4:end));
            offset = find((1:numel(m))' >= 4 & m >= 0.9 * ref, 1) - 1;
        else
            offset = opts.DataOffset;
        end
        [q, C] = trackQ(S, n, offset + 1, opts.MinCoherence);
        meas(j).file = file;
        meas(j).fov = fov;
        meas(j).offset = offset;
        meas(j).S = S;
        meas(j).n = n;
        meas(j).q = q;
        meas(j).C = C;
        used = find(C >= opts.MinCoherence);
        say(sprintf('%s: data offset %d, coherent to sample %d (%d samples)', file, offset, max([used; 0]), numel(used)));
    end
    offsets = [meas.offset];
    if any(offsets ~= offsets(1))
        error('measureUteTrajectory:offset', 'The scans differ in data offset (%s); give DataOffset.', mat2str(offsets));
    end
    offset = offsets(1);

    % --- Positions, k per axis and the fits, the positions refined from the fit -----
    nSamples = size(meas(1).S, 1);
    gp = mean(diff(default(end - 10:end))) * numel(default);        % plateau, cycles/FOV per sample
    models = ["shift" "stretch" "linear" "sine"];
    if ~isempty(opts.Positions)
        positionsFrom = "given";
        P = opts.Positions;
        assert(isequal(size(P), [numel(meas) 3]), 'measureUteTrajectory:positions', 'Positions: one row [x y z] mm per scan');
        for j = 1:numel(meas)
            meas(j).r = P(j, :) / meas(j).fov;
        end
    elseif opts.PositionMethod == "plateau"
        positionsFrom = "plateau";
        gd = diff([0; default(:)]);
        first = offset + find(gd >= opts.PlateauFraction * mean(gd(end - 10:end)), 1);
        for j = 1:numel(meas)
            t = (1:nSamples)';
            on = t >= first & meas(j).C >= opts.MinCoherence;
            if nnz(on) < opts.MinPlateauSamples
                error('measureUteTrajectory:plateau', ['%s is coherent on %d samples of the plateau (from data ' ...
                    'sample %d), %d needed. The object loses its signal before the plateau: scan a smaller object ' ...
                    'with a long T2 (a water capillary), give Positions, or use PositionMethod "image", whose ' ...
                    'positions follow the default profile.'], meas(j).file, nnz(on), first, opts.MinPlateauSamples);
            end
            X = [t(on) ones(nnz(on), 1)];
            slope = X \ meas(j).q(on, :);
            meas(j).r = slope(1, :) / gp;
        end
    else
        positionsFrom = "image";
        say('  WARNING: positions from an image made with the default profile; the scale of the measured k follows it');
        kfun = @(x) repmat(nominalK(default, x - offset), 1, 3);
        for j = 1:numel(meas)
            meas(j).r = imagePosition(meas(j).S, meas(j).n, kfun, offset);
        end
    end
    for j = 1:numel(meas)
        say(sprintf('  position %s mm (%s)', mat2str(round(meas(j).r * meas(j).fov, 2)), positionsFrom));
    end
    [fits, fitData, chosen] = fitAll(meas, default, offset, gp, models, opts, say);
    for j = 1:numel(meas)
        meas(j).k = meas(j).q ./ meas(j).r .* [fitData{1}.sign fitData{2}.sign fitData{3}.sign];
    end

    % --- The profile ------------------------------------------------------------------------
    N = min(numel(default), nSamples - offset);
    x = offset + (1:N)';
    profile = zeros(N, 3);
    for a = 1:3
        profile(:, a) = modelK(chosen, fits.(chosen).params(a, :), x, default, offset, gp) / N + 0;
    end
    say(sprintf('  written model: %s, %d rows from data sample %d', chosen, N, offset + 1));

    result = struct('profile', profile, 'dataOffset', offset, 'model', chosen, 'fits', fits, ...
        'positionsFrom', positionsFrom, 'scans', rmfield(meas, {'S', 'n'}));

    if strlength(opts.Output) > 0
        writeProfile(opts.Output, result);
        say(sprintf('  written %s', opts.Output));
    end
    if opts.Plot
        plotFits(result, fitData, default, offset, gp);
    end

end % measureUteTrajectory


function [fits, fitData, chosen] = fitAll(meas, default, offset, gp, models, opts, say)

    % k per axis from q and the positions, with the sign that makes it increase, and
    % the four models fitted to it
    names = 'xyz';
    nSamples = size(meas(1).S, 1);
    t = (1:nSamples)';
    kn = @(x) nominalK(default, x - offset);
    fitData = cell(1, 3);
    for a = 1:3
        tt = []; kk = []; ww = [];
        for j = 1:numel(meas)
            ra = meas(j).r(a);
            if abs(ra * meas(j).fov) < opts.MinOffset, continue; end
            ok = meas(j).C >= opts.MinCoherence;
            tt = [tt; t(ok)]; kk = [kk; meas(j).q(ok, a) / ra]; ww = [ww; repmat(ra ^ 2, nnz(ok), 1)]; %#ok<AGROW>
        end
        if isempty(tt)
            error('measureUteTrajectory:axis', ['No scan has the object %g mm or more off centre along %s; ' ...
                'scan it further out on that axis.'], opts.MinOffset, names(a));
        end
        sgn = sign(sum(ww .* kk .* kn(tt)));
        fitData{a} = struct('t', tt, 'k', sgn * kk, 'w', ww, 'sign', sgn);
    end
    fits = struct();
    fo = optimset('TolX', 1e-5, 'TolFun', 1e-10, 'MaxFunEvals', 4000, 'MaxIter', 4000, 'Display', 'off');
    for mdl = models
        P = zeros(3, 2); rmsA = zeros(1, 3);
        for a = 1:3
            f = fitData{a};
            model = @(p, x) modelK(mdl, p, x, default, offset, gp);
            E = @(p) sum(f.w .* (f.k - model(p, f.t)) .^ 2) / sum(f.w);
            switch mdl
                case "shift",   starts = [0; 3; -3];
                case "stretch", starts = [0 1; 3 1; 0 0.7];
                otherwise,      starts = [offset + 4, 30; offset + 8, 40; offset + 2, 20];
            end
            best = inf;
            for s = 1:size(starts, 1)
                [p, e] = fminsearch(E, starts(s, :), fo);
                if e < best, best = e; P(a, 1:numel(p)) = p; end
            end
            rmsA(a) = sqrt(best);
        end
        fits.(mdl) = struct('params', P, 'rms', rmsA);
        say(sprintf('    %-8s rms %s cycles/FOV (x y z), parameters per axis %s', mdl, mat2str(round(rmsA, 3)), ...
            mat2str(round(P, 2))));
    end
    if opts.Model == "best"
        [~, b] = min(arrayfun(@(mm) sum(fits.(mm).rms .^ 2), models));
        chosen = models(b);
    else
        chosen = opts.Model;
    end

end % fitAll


function opts = parseOptions(varargin)

    % The name-value options with their defaults
    p = inputParser;
    p.addParameter('DataOffset', [], @(v) isempty(v) || (isscalar(v) && v >= 0 && v == round(v)));
    p.addParameter('Positions', [], @isnumeric);
    p.addParameter('PositionMethod', "plateau", @(v) any(string(v) == ["plateau" "image"]));
    p.addParameter('PlateauFraction', 0.95, @(v) isscalar(v) && v > 0 && v <= 1);
    p.addParameter('MinPlateauSamples', 8, @(v) isscalar(v) && v >= 2);
    p.addParameter('Model', "best", @(v) any(string(v) == ["best" "shift" "stretch" "linear" "sine"]));
    p.addParameter('MinCoherence', 0.85, @(v) isscalar(v) && v > 0 && v < 1);
    p.addParameter('MinOffset', 5, @(v) isscalar(v) && v >= 0);
    p.addParameter('Output', "", @(v) ischar(v) || isstring(v));
    p.addParameter('Plot', false, @islogical);
    p.addParameter('Reporter', @(s) fprintf('%s\n', s), @(v) isa(v, 'function_handle'));
    p.parse(varargin{:});
    opts = p.Results;
    opts.Model = string(opts.Model);
    opts.PositionMethod = string(opts.PositionMethod);
    opts.Output = string(opts.Output);

end % parseOptions


function profile = defaultProfile()

    % The app's default readout profile, one column
    if ~isempty(which('retro.io.defaultUteTrajectory'))
        profile = retro.io.defaultUteTrajectory();
    elseif ~isempty(which('proud.io.defaultUteTrajectory'))
        profile = proud.io.defaultUteTrajectory();
    else
        error('measureUteTrajectory:path', 'Neither Retrospective nor P2ROUD is on the MATLAB path.');
    end

end % defaultProfile


function [file, lutFile] = scanFiles(scan)

    % The MRD file and the LUT of a scan, given its folder or its MRD file
    if isfolder(scan)
        f = dir(fullfile(scan, '*.MRD'));
        f = f(~startsWith({f.name}, 'retro_'));
        assert(~isempty(f), 'measureUteTrajectory:scan', 'No MRD file in %s', scan);
        file = string(fullfile(f(1).folder, f(1).name));
    else
        file = scan;
    end
    l = dir(fullfile(fileparts(file), 'lut*.txt'));
    assert(~isempty(l), 'measureUteTrajectory:scan', 'No lut*.txt beside %s', file);
    lutFile = string(fullfile(l(1).folder, l(1).name));

end % scanFiles


function [raw, fov] = readScan(file)

    % Samples x experiments, and the field of view in mm from the MRD header
    if ~isempty(which('retro.io.importMRD'))
        im = retro.io.importMRD(char(file), 'seq', 'cen');
    else
        im = proud.io.importMRD(char(file), 'seq', 'cen');
    end
    raw = double(reshape(im, size(im, 1), []).');
    fid = fopen(file, 'r');
    txt = fread(fid, [1 inf], '*char');
    fclose(fid);
    tok = regexp(txt, ':FOV (\d+(\.\d+)?)', 'tokens', 'once');
    assert(~isempty(tok), 'measureUteTrajectory:fov', 'No :FOV in the header of %s', file);
    fov = str2double(tok{1});

end % readScan


function [q, C] = trackQ(S, n, t0, minC)

    % q(t) per sample by the matched filter, followed from q = 0 at sample t0 until
    % the coherence has stayed below minC for three samples
    nS = size(S, 1);
    q = nan(nS, 3);
    C = zeros(nS, 1);
    fo = optimset('TolX', 1e-6, 'TolFun', 1e-10, 'MaxFunEvals', 1000, 'Display', 'off');
    qp = [0 0 0]; qpp = [0 0 0]; low = 0;
    for t = t0:nS
        d = S(t, :);
        ad = sum(abs(d));
        J = @(x) -abs(sum(d .* exp(2i * pi * (x(:)' * n)))) / ad;
        [x1, f1] = fminsearch(J, qp + (qp - qpp), fo);
        [x2, f2] = fminsearch(J, qp, fo);
        if f2 < f1, x1 = x2; f1 = f2; end
        q(t, :) = x1; C(t) = -f1;
        qpp = qp; qp = x1;
        if C(t) < minC, low = low + 1; else, low = 0; end
        if low >= 3, break; end
    end
    % Only the samples up to the first loss of coherence are trusted: a track that
    % recovers afterwards may have jumped to another maximum
    lost = find(C(t0:end) < minC, 1) + t0 - 1;
    if ~isempty(lost), C(lost:end) = min(C(lost:end), minC - eps); end

end % trackQ


function r = imagePosition(S, n, kfun, offset)

    % The object's position, in fields of view along the LUT axes, from BART's
    % inverse NUFFT on a 128 grid; kfun(x) gives k per axis (cycles/FOV) at data
    % samples x. The inverse leaves bright voxels along the border of the grid, so
    % the search for the object keeps clear of it.
    N = 128;
    x = (offset + 1:size(S, 1))';
    kx = kfun(x);
    rows = find(all(abs(kx) <= N / 2 - 1, 2));
    keep = 1:2:size(S, 2);
    k = reshape(kx(rows, :)', 3, [], 1) .* reshape(n(:, keep), 3, 1, []);   % 3 x samples x spokes
    data = reshape(S(x(rows), keep), [1 numel(rows) numel(keep)]);
    im = abs(runBart(sprintf('nufft -i -l 0.01 -d%d:%d:%d -t', N, N, N), k, data));
    edge = 6;
    inner = false(size(im));
    inner(edge + 1:end - edge, edge + 1:end - edge, edge + 1:end - edge) = true;
    im(~inner) = 0;
    [~, i] = max(im(:));
    [c1, c2, c3] = ind2sub(size(im), i);
    w = 6;
    r1 = max(c1 - w, 1):min(c1 + w, N); r2 = max(c2 - w, 1):min(c2 + w, N); r3 = max(c3 - w, 1):min(c3 + w, N);
    b = im(r1, r2, r3);
    b = b .* (b >= 0.5 * max(b(:)));
    [g1, g2, g3] = ndgrid(r1, r2, r3);
    c = [sum(b(:) .* g1(:)) sum(b(:) .* g2(:)) sum(b(:) .* g3(:))] / sum(b(:));
    r = (c - (N / 2 + 1)) / N;

end % imagePosition


function out = runBart(cmd, varargin)

    % BART through the app's own wrapper, which handles Windows and WSL
    if ~isempty(which('retro.defaultRecoParams'))
        p = retro.defaultRecoParams();
        p.bartDetected = true;
        out = bart(p, cmd, varargin{:});
    elseif ~isempty(which('proud.Reporter'))
        out = bart(proud.Reporter(), cmd, varargin{:});
    else
        error('measureUteTrajectory:bart', 'BART is needed for the positions; give Positions instead.');
    end

end % runBart


function k = nominalK(default, x)

    % The default profile in cycles/FOV at profile position x (1 = its first row),
    % 0 before it, and on along the plateau slope after it
    T = numel(default);
    k = T * interp1(1:T, default, x, 'linear', 0);
    gp = T * mean(diff(default(end - 10:end)));
    after = x > T;
    k(after) = T * default(end) + gp * (x(after) - T);

end % nominalK


function k = modelK(mdl, p, x, default, offset, gp)

    % k in cycles/FOV at data samples x for one axis of one model
    switch mdl
        case "shift"
            k = nominalK(default, x - offset - p(1));
        case "stretch"
            % The default gradient delayed by p(1) and its ramp stretched by p(2):
            % g(x) = g_default((x - offset - p(1)) / p(2)) until it reaches the plateau
            s = max(abs(p(2)), 0.2);
            xs = (0:0.25:max(x) + 1)';
            u = (xs - offset - p(1)) / s;
            g = gradientAt(default, u);
            kk = cumtrapz(xs, g);
            k = interp1(xs, kk, x, 'linear', 'extrap');
        case "linear"
            t0 = p(1); R = max(abs(p(2)), 1);
            k = gp * ((x > t0 & x <= t0 + R) .* (x - t0) .^ 2 / (2 * R) + (x > t0 + R) .* (R / 2 + x - t0 - R));
        case "sine"
            t0 = p(1); R = max(abs(p(2)), 1);
            k = gp * ((x > t0 & x <= t0 + R) .* ((x - t0) / 2 - R / (2 * pi) * sin(pi * (x - t0) / R)) + ...
                (x > t0 + R) .* (R / 2 + x - t0 - R));
    end

end % modelK


function g = gradientAt(default, u)

    % The default profile's gradient, cycles/FOV per sample, at profile position u,
    % 0 before it and the plateau after it
    T = numel(default);
    gd = T * diff([0; default(:)]);
    gp = mean(gd(end - 10:end));
    g = interp1((1:T)', gd, u, 'linear', 0);
    g(u > T) = gp;
    g(u < 0) = 0;

end % gradientAt


function writeProfile(file, result)

    % ktraj.txt with comment lines on what it is and how to use it
    fid = fopen(file, 'w');
    assert(fid > 0, 'measureUteTrajectory:write', 'Cannot write %s', file);
    [~, names] = arrayfun(@(s) fileparts(s), string({result.scans.file}), 'UniformOutput', false);
    names = strrep(string(names), '_000_0', '');
    P = result.fits.(result.model).params;
    fprintf(fid, '%% 3D UTE readout profile per axis (x y z), measured with measureUteTrajectory on %s (%s).\n', ...
        strjoin(string(names), ', '), datestr(now, 'yyyy-mm-dd')); %#ok<TNOW1,DATST>
    fprintf(fid, '%% Model %s, parameters per axis %s, rms %s cycles/FOV. Positions from the %s.\n', ...
        result.model, mat2str(round(P, 2)), mat2str(round(result.fits.(result.model).rms, 3)), result.positionsFrom);
    fprintf(fid, '%% Use it with data offset %d and zero Gx, Gy and Gz delays. Delete it to get the default back.\n', ...
        result.dataOffset);
    fprintf(fid, '%.8g %.8g %.8g\n', result.profile');
    fclose(fid);

end % writeProfile


function plotFits(result, fitData, default, offset, gp)

    % The measured k per axis against the fitted models
    figure('Name', 'measureUteTrajectory', 'Color', 'w');
    names = 'xyz';
    models = string(fieldnames(result.fits))';
    for a = 1:3
        subplot(1, 3, a); hold on;
        f = fitData{a};
        scatter(f.t, f.k, 12, f.w / max(f.w), 'filled');
        x = (min(f.t):0.25:max(f.t) + 10)';
        plot(x, nominalK(default, x - offset), 'k:', 'LineWidth', 1);
        for mdl = models
            plot(x, modelK(mdl, result.fits.(mdl).params(a, :), x, default, offset, gp), 'LineWidth', 1 + (mdl == result.model));
        end
        title(sprintf('%s axis', names(a))); xlabel('data sample'); ylabel('k (cycles/FOV)');
        legend(["measured" "default" models], 'Location', 'northwest'); grid on;
    end

end % plotFits
