% file to analyse gvs data and compute cop
clear
close all
clc
sample_rate=960; % [Hz]
d=dir(cd); % file listing of current directory (cd)
names=d.name; % names of files
n=size(d);
range=0.07; % [m]

%loads the data from testdata into an array called 's'
rtrial = xlsread('thomas_reaching.xlsx');

%splits 'rtrial' into two separate arrays (different conditions); trial1 =
%no vision no GVS; 2 = vision; 3 = no vision; 4 = vision, weight; 5 = no
%vision, weight
trial1 = rtrial(:,1:2)
trial2 = rtrial(:,3:4) 
trial3 = rtrial(:,5:6)
trial4 = rtrial(:,7:8)
trial5 = rtrial(:,9:10)


col={'ko', 'k.', 'k*', 'k.', 'k+', 'k.', 'kd', 'k.', 'k^'};
figure
ax=axes;
for iTrial=1:2:9
        tmp=rtrial(:,iTrial:iTrial+1);
        p = plot(tmp(:,1),tmp(:,2), col{iTrial})
        if iTrial==1, hold on, end 
        %'o','linewidth',3); hold on
        grid on; hold on
        %yline(0); hold on
        %xline(0); hold on
        xticks([-5.0 -4.0 -3.0 -2.0 -1.0 0 1.0 2.0 3.0 4.0 5.0 6.0 7.0 8.0 9.0 10.0 11.0 12.0 13.0 14.0])
        %xticks([-5.0 -4.5 -4.0 -3.5 -3.0 -2.5 -2.0 -1.5 -1.0 -0.5 0 0.5 1.0 1.5 2.0 2.5 3.0 3.5 4.0 4.5 5.0 5.5 6.0 6.5 7.0 7.5 8.0 8.5 9.0 9.5 10.0 10.5 11.0 11.5 12.0 12.5 13.0 13.5 14.0 14.5])
        yticks([-10 -9.0 -8.0 -7.0 -6.0 -5.0 -4.0 -3.0 -2.0 -1.0 0 1.0 2.0 3.0 4.0 5.0 6.0 7.0 8.0 9.0])
        xlabel('Error in x-Coordinate (cm)', 'FontSize', 18);
        ylabel('Error in y-Coordinate (cm)', 'FontSize', 18);
        title('Summary of Planar Error from the Target in Various Reaching Conditions', 'FontSize',20)
        axis equal; hold all
%         % covariance of x with y
%         n=100; % Number of points around ellipse
%         p=0:pi/n:2*pi; % angles around a circle
%         C_t = cov([tmp(:,1) tmp(:,2)]); % covariance of rx and ry
%         [eigvec,eigval] = eig(C_t) % Compute eigen-stuff
%         xy = [cos(p'),sin(p')] * sqrt(eigval) * eigvec'; % Transformation
%         x_ellips = xy(:,1) + mean(tmp(:,1));
%         y_ellips = xy(:,2) + mean(tmp(:,2));
%         plot(x_ellips,y_ellips,'k-');
end
% ax = gca;
% labels = string(ax.XAxis.TickLabels); % extract
% labels(2:2:end) = nan; % remove every other one
% ax.XAxis.TickLabels = labels;

%legend('NV','Cov NV','VNW','Cov VNW','NVNW','Cov NVNW','VW','Cov VW','NVW','Cov NVW');
%legend('No vision, no GVS','Vision, no weight','No vision, no weight','Vision, weight','No vision, weight')
xline(0);
yline(0);

% tix=get(gca,'xticks')';
% tix=get(gca,'yticks')';
% set(gca,'xticklabel',num2str(tix,'%.1f'))
% set(gca,'yticklabel',num2str(tix,'%.1f'))
%ax.YAxisLocation='origin';
%ax.XAxisLocation='origin';

% covariance of x with y
n=100; % Number of points around ellipse
p=0:pi/n:2*pi; % angles around a circle
C_t1 = cov([trial1(:,1) trial1(:,2)]); % covariance of rx and ry
[eigvec,eigval] = eig(C_t1) % Compute eigen-stuff
xy = [cos(p'),sin(p')] * sqrt(eigval) * eigvec'; % Transformation
x_ellips = xy(:,1) + mean(trial1(:,1));
y_ellips = xy(:,2) + mean(trial1(:,2));
plot(x_ellips,y_ellips,'k:');

% covariance of x with y
n=100; % Number of points around ellipse
p=0:pi/n:2*pi; % angles around a circle
C_t2 = cov([trial2(:,1) trial2(:,2)]); % covariance of rx and ry
[eigvec,eigval] = eig(C_t2) % Compute eigen-stuff
xy = [cos(p'),sin(p')] * sqrt(eigval) * eigvec'; % Transformation
x_ellips = xy(:,1) + mean(trial2(:,1));
y_ellips = xy(:,2) + mean(trial2(:,2));
plot(x_ellips,y_ellips,'ko');

% covariance of x with y
n=100; % Number of points around ellipse
p=0:pi/n:2*pi; % angles around a circle
C_t3 = cov([trial3(:,1) trial3(:,2)]); % covariance of rx and ry
[eigvec,eigval] = eig(C_t3) % Compute eigen-stuff
xy = [cos(p'),sin(p')] * sqrt(eigval) * eigvec'; % Transformation
x_ellips = xy(:,1) + mean(trial3(:,1));
y_ellips = xy(:,2) + mean(trial3(:,2));
plot(x_ellips,y_ellips,'k-');

% covariance of x with y
n=100; % Number of points around ellipse
p=0:pi/n:2*pi; % angles around a circle
C_t4 = cov([trial4(:,1) trial4(:,2)]); % covariance of rx and ry
[eigvec,eigval] = eig(C_t4) % Compute eigen-stuff
xy = [cos(p'),sin(p')] * sqrt(eigval) * eigvec'; % Transformation
x_ellips = xy(:,1) + mean(trial4(:,1));
y_ellips = xy(:,2) + mean(trial4(:,2));
plot(x_ellips,y_ellips,'ko');

% covariance of x with y
n=100; % Number of points around ellipse
p=0:pi/n:2*pi; % angles around a circle
C_t5 = cov([trial5(:,1) trial5(:,2)]); % covariance of rx and ry
[eigvec,eigval] = eig(C_t5) % Compute eigen-stuff
xy = [cos(p'),sin(p')] * sqrt(eigval) * eigvec'; % Transformation
x_ellips = xy(:,1) + mean(trial5(:,1));
y_ellips = xy(:,2) + mean(trial5(:,2));
plot(x_ellips,y_ellips,'k-.');



for i=1:max(n)%i=max(n)-2 %
    fileName=d(i).name;
    fileType=finfo(fileName);
    %if strcmp(fileType,'mat')
    if strcmp(fileName,'thomaspilot_05_02.mat')
        [forcesAndMoments] = loadForcesFromHBCLBertecTreadmillMatFile(fileName,'forceFrequency',[sample_rate],'shouldFilter',[1],'filterCutoffFrequency',[30]);
        groundReactionMoments=forcesAndMoments.left.groundReactionMoments; % [Nm], measured at 1000 Hz, maybe ??
        groundReactionForces=forcesAndMoments.left.groundReactionForces; % [N], measured at 1000 Hz, maybe ??
        t=(0:length(groundReactionForces)-1)/sample_rate;
        idx_cut=t>520 | t<60; % indexing every sample after t=500 and before t=60
        t(idx_cut)=[];
        t=t-t(1); % to make sure time axis starts at 0
        groundReactionForces(idx_cut,:)=[]; % trow away everything after 525 seconds
        groundReactionMoments(idx_cut,:)=[]; % trow away everything after 525 seconds
        % cop position wrt back left side of treadmill. positive x-direction in the
        % walking direction. positive y-direction towards middle
        ry=groundReactionMoments(:,1)./groundReactionForces(:,3); % [m]
        rx=-groundReactionMoments(:,2)./groundReactionForces(:,3); % [m]
        
        % COP velocity profile (looking at this to find start of GVS
        ryd=diff(ry)*sample_rate; % [m/s] velocity of cop in y direction. delta y / delta time (1/sf)
        rxd=diff(rx)*sample_rate;
        v_r=sqrt(ryd.^2+rxd.^2); %computes the magnitude of the velocity coordinates (pythagoras)
        
        % find peaks in v_cop
        figure; subplot(212)
        [~,LOCS] = findpeaks(v_r,'MinPeakDistance',58*sample_rate,'MinPeakHeight',0.1, 'NPeaks',6);
        findpeaks(v_r,sample_rate,'MinPeakDistance',58,'MinPeakHeight',0.1,'NPeaks',6)
        xticks([0 60 120 180 240 300 360 420])
        xlabel('Time (s)')
        ylabel('COP velocity (m/s)')
        
        %add a corresponding plot with the COPx above the findpeaks output
        subplot(211);plot(t,rx,'k')
        xticks([0 60 120 180 240 300 360 420])
        title('COP x-Coordinate and Magnitude of Velocity as a Function of Time')
        xlabel('Time (s)')
        ylabel('COPx (m)')
        axis([0 400 -0.40 -0.20]);
        %export_fig shaine_cop_x_velocity -transparent -TIFF
        

        
        % make pretty pictures
        % animation!! Cool stuff!!
        %         for iPeak=1:length(LOCS) % we are gonna do something for every peak
        %             figure
        %             %axis equal; hold on
        %             axis([-0.40 -0.2 0.35 0.55]); hold on %this will ensure axis are in similar proportions. NEED TO ALTER THE LIMITS BASED ON TRIAL
        %             xlabel('left-right sway [m]')
        %             ylabel('front-back sway [m]')
        %             time_span=20*sample_rate; % nr of samples to look at round peak
        %             idx_tmp=LOCS(iPeak)-time_span:LOCS(iPeak)+time_span;
        %             comet(rx(idx_tmp),ry(idx_tmp),0.2);
        %             %comet3(rx(idx_tmp),ry(idx_tmp),t(idx_tmp)); %add temporality
        
        
        %         end
        %
        
        %CUSTOM LOCATION SETTING
        %LOCScustom = [90000;147600;205200;262800;320400;350000]; %total time (from beginning of forceplate measurement) x sample rate; (60s x 960 = 57600); first one = X seconds + 1min increments
        %look at groundReactionForces/Moments for the number of total
        %samples; ensure that the final value you pic is consistent with
        %the time_span function for the animations. (eg.
        %time_span=20*sample_rate and thus 20*960 = 19600. THEREFORE, the
        %top value must be 19600 below the total samples or else it cannot
        %be indexed
        
        
        %         %ANIMATIONS AT CUSTOM LOCATIONS
        %         for iPeak=1:length(LOCScustom) % we are gonna do something for every peak
        %             figure
        %             %axis equal; hold on
        %             axis([-0.40 -0.2 0.35 0.55]); hold on %this will ensure axis are in similar proportions. NEED TO ALTER THE LIMITS BASED ON TRIAL
        %             xlabel('left-right sway [m]')
        %             ylabel('front-back sway [m]')
        %             time_span=20*sample_rate; % nr of samples to look at round peak
        %             idx_tmp=LOCScustom(iPeak)-time_span:LOCScustom(iPeak)+time_span;
        %             comet(rx(idx_tmp),ry(idx_tmp),0.2);
        %             %comet3(rx(idx_tmp),ry(idx_tmp),t(idx_tmp)); %add temporality
        %         end
        
        
        %make general COP plots for each software detected peak
        for iPeak=1:length(LOCS) % we are gonna do something for every peak
            figure
            axis equal; hold on %this will ensure axis are in similar proportions. NEED TO ALTER THE LIMITS BASED ON TRIAL
            xlabel('Left-Right Sway (m)', 'FontSize', 20)
            ylabel('Front-Back sway (m)', 'FontSize', 20)
            title('x- and y-Coordinate COP Profile During Constant Current GVS', 'FontSize', 24)
            time_span=10*sample_rate; % nr of samples to look at round peak
            time_gvs=3*sample_rate;
            idx_tmp=LOCS(iPeak)-time_span:LOCS(iPeak)+time_span;
            idx_gvs=LOCS(iPeak)-time_gvs:LOCS(iPeak)+time_gvs;
            plot(rx(idx_tmp),ry(idx_tmp),'k.'); hold on
            plot(rx(idx_gvs),ry(idx_gvs),'r-','linewidth',2); hold on
            %legend('Constant Current','GVS ON/OFF Switch');
            
            % covariance of x with y
%             n=100; % Number of points around ellipse
%             p=0:pi/n:2*pi; % angles around a circle
%             C = cov([rx(idx_tmp) ry(idx_tmp)]); % covariance of rx and ry
%             [eigvec,eigval] = eig(C) % Compute eigen-stuff
%             xy = [cos(p'),sin(p')] * sqrt(eigval) * eigvec'; % Transformation
%             x_ellips = xy(:,1) + mean(rx(idx_tmp));
%             y_ellips = xy(:,2) + mean(ry(idx_tmp));
%             plot(x_ellips,y_ellips,'ro')
%             axis equal
        end
        
        
        %make general COP plots @ CUSTOM LOCATIONS as indicated by the
        %CUSTOM LOCATIONS SETTINGS
        %          for iPeak=1:length(LOCScustom) % we are gonna do something for every peak
        %              figure
        %              axis([-0.36 -0.21 0.40 0.55]); hold on %this will ensure axis are in similar proportions. NEED TO ALTER THE LIMITS BASED ON TRIAL
        %              xlabel('left-right sway [m]')
        %              ylabel('front-back sway [m]')
        %              time_span=20*sample_rate; % nr of samples to look at round peak
        %              idx_tmp=LOCScustom(iPeak)-time_span:LOCScustom(iPeak)+time_span;
        %              plot(rx(idx_tmp),ry(idx_tmp));
        %          end
        
        
        %we are plotting the forces over time for all coordinates
        %         figure;subplot(211);plot(t,groundReactionForces(:,3))
        %         ylim ([810 870]) %this is set holistically based on subject body mass. look at groundReactionForces 3rd column (:,3) for estimated z-Force
        %         xticks([0 60 120 180 240 300 360 420 480 540]) %better to see in terms of minutes
        %         title('z axis')
        %         xlabel('Time [s]')
        %         ylabel('Force [N]')
        %
        %         subplot(212);plot(t,groundReactionForces(:,1:2))
        %         ylim ([-65 15]) %holistically set
        %         xticks([0 60 120 180 240 300 360 420 480 540])
        %         title('x and y axis')
        %         xlabel('Time [s]')
        %         ylabel('Force [N]')
        
        
        %COPx and y over time to see effect
%         figure;plot(t,rx)
%         xticks([0 60 120 180 240 300 360 420 480 540])
%         title('x coordinate over time')
%         xlabel('time [s]')
%         ylabel('COPx [m]')
        
        figure;plot(t,ry)
        xticks([0 60 120 180 240 300 360 420 480 540])
        title('y coordinate over time')
        xlabel('Time (s)')
        ylabel('COPy (m)')
        
%         figure;plot(t(2:end),rxd)
%         xticks([0 60 120 180 240 300 360 420 480 540])
%         title('x coordinate over time')
%         xlabel('time [s]')
%         ylabel('COPx [m]')
        
        
        %         for iPeak=1:length(LOCS) % we are gonna do something for every peak
        %             figure
        %             time_span=2*sample_rate; % nr of samples to look at round peak
        %             idx_tmp=LOCS(iPeak)-time_span:LOCS(iPeak)+time_span;
        %             plot(rx(idx_tmp),ry(idx_tmp),'.'); hold on
        %             delay_tmp=LOCS(iPeak)-0.5*sample_rate;
        %             %plot(rx(delay_tmp),ry(delay_tmp),'ro'); %hold on
        %             plot([rx(delay_tmp) rx(delay_tmp)+rxd(delay_tmp)],[ry(delay_tmp) ry(delay_tmp)+ryd(delay_tmp)],'r'); %hold on
        %             xlabel('fore-aft [m]')
        %             ylabel('left-right [m]')
        %             axis equal
        %         end
        %         %xlim([mean(rx)-.5*range mean(rx)+.5*range])
        %ylim([mean(ry)-.5*range mean(ry)+.5*range])
        
    end
end

