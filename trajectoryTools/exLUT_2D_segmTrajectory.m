%% ---------------------------
%
% Zig-zag trajectory with random k-space filling and fully sampled k-space center
% Fill 16s repetitions of a 192 matrix
% K-space center = 12 fully sampled lines
% 
%
% Gustav Strijkers
% July 2025
%
%
%
%

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

