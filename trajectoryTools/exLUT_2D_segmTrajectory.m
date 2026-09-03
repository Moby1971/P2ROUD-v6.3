% Segmented zig-zag 2D trajectory (exLUT)
%
% Author : Gustav Strijkers
% Date   : 2026-09-02
%
% Purpose:
%   Generate the explicit k-space look-up table for a segmented 2D acquisition:
%   a zig-zag through randomly filled k-space with a fully sampled centre.
%
% How it works:
%   The list is built for 16 repetitions of a 192 line matrix with 12 fully
%   sampled centre lines. The centre is always measured, since the lowest
%   frequencies must be acquired rather than inferred; the remaining lines are
%   drawn at random, so the aliasing is incoherent and a compressed sensing
%   reconstruction can remove it.
%
%   The few lines closest to the centre are excluded from the random draw, so
%   they are covered by the fully sampled block and not measured twice.
%
%   Within a repetition the order is a zig-zag: successive readouts alternate
%   between the two halves of k-space rather than walking steadily from one edge
%   to the other. That spreads any drift through the acquisition over the image
%   instead of letting it accumulate across neighbouring lines.
%
%   The whole construction sits in a loop that retries until a list satisfying
%   the constraints is produced, the random draw not being guaranteed to give
%   one on the first attempt.
%
% Inputs:
%   none - a script; the sizes are set in the code below and are meant to be
%          edited before running
%
% Output:
%   none - the look-up table, in the workspace and written out

clearvars

while true
    
    traj = zeros(16*12,1);
    
    for j = 1:64
        l(j) = j-33;
    end
    l(l==-2) = [];
    l(l==-1) = [];
    l(l==0) = [];
    l(l==1) = [];
    
    
    
    for i = 1:16
        
        while true
        
        traj(1+(i-1)*12) = l(randi(60));
        traj(2+(i-1)*12) = l(randi(60));
        traj(3+(i-1)*12) = l(randi(60));
        traj(4+(i-1)*12) = -2;
        traj(5+(i-1)*12) = -1;
        traj(6+(i-1)*12) = 0;
        traj(7+(i-1)*12) = 1;
        traj(8+(i-1)*12) = l(randi(60));
        traj(9+(i-1)*12) =  l(randi(60));
        traj(10+(i-1)*12) = l(randi(60));
        traj(11+(i-1)*12) = l(randi(60));
        traj(12+(i-1)*12) = l(randi(60));
        
        if length(unique(traj(1+(i-1)*12:12+(i-1)*12))) == 12 break; end
        
        end
        
    end
    
    
    for i = 1:16
        if rem(i, 2)== 0
            trajs((i-1)*12+1 : (i-1)*12 + 12) = sort(traj((i-1)*12+1 : (i-1)*12 + 12),'descend');
        else
            trajs((i-1)*12+1 : (i-1)*12 + 12) = sort(traj((i-1)*12+1 : (i-1)*12 + 12),'ascend');
        end
    end
    
    
    kspace = zeros(11,64,64);
    
    cnt = 1;
    
    for i = 1:16
        for j = 1:12
            kspace(i,trajs(cnt)+33,:) = 1;
            cnt = cnt + 1;
        end
        
    end
    
    kspace(17,:,:) = sum(kspace,1);
    kspace(18,:,:) = sum(kspace(1:4,:,:),1);
    kspace(19,:,:) = sum(kspace(2:6,:,:),1);
    kspace(20,:,:) = sum(kspace(4:8,:,:),1);
    kspace(21,:,:) = sum(kspace(6:10,:,:),1);
    kspace(22,:,:) = sum(kspace(8:12,:,:),1);
    kspace(23,:,:) = sum(kspace(10:14,:,:),1);
    kspace(24,:,:) = sum(kspace(12:16,:,:),1);
    
    b = nnz(~kspace(17,:))/64;
    disp(b);
    
    if b == 0 break; end
    
end

figure(1);
plot(trajs);

figure(2);

for i = 1:24
    subplot(4,6,i),imshow(squeeze(kspace(i,:,:)));
    title(num2str(i));
end



filename = '.\output\per_dimy192_segm16_lines12.txt';
fileID = fopen(filename,'w');

for i = 1:length(trajs)
    
    fprintf(fileID,[num2str(trajs(1,i)),',']);
    fprintf(fileID,'\n');
    
end

fclose(fileID);

