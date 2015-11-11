clear all, close all, clc

%% Atan for output angles between 0º and 45º, 0.01º resolution
TARGET_THETA_RESOLUTION = 0.01;

% First, determine the minimum input resolution so that we obtain
% a minimum resolution of TARGET_THETA_RESOLUTION = 0.01 degrees
step = 0.00001;
res = 0.1 + step;
out_res = 1;

while out_res > TARGET_THETA_RESOLUTION
    res = res - step;
    fprintf('Res = %.10f\n',res);
    t_in = 0 : res : 1;
    lut = atan(t_in) * 180 / pi;
    
    maxDelta = 0;
    for i = 1:length(lut) - 1
        delta = abs(lut(i) - lut(i+1));
        if delta > maxDelta
            maxDelta = delta;
        end
    end
    out_res = maxDelta;
end

fprintf('Minimum input resolution: %.10f, Theta res = %.10f',res, out_res);

N_VALS = 8096;
t = (0 : 1/N_VALS : 1);

fileID = fopen('atanLUT.h','w');
fprintf(fileID, '#define LUT_ATAN2_TABLE_SIZE %d\n',N_VALS);
fprintf(fileID, 'const uint16_t LUT_atan [%d] PROGMEM = {', N_VALS);
for i = 1:N_VALS
    if i < N_VALS
        fprintf(fileID,'%u, ', uint16((18000/pi)*atan(t(i))));
    else
        fprintf(fileID,'%u};', uint16((18000/pi)*atan(t(i))));
    end
end
fclose(fileID);
%% sin
THETA_RES = 0.01 * pi/180;
THETA_MIN = 0;
THETA_MAX = pi/2;

theta = THETA_MIN : THETA_RES : THETA_MAX - THETA_RES;
N_VALS = length(theta)/2;

fileID = fopen('LUT_sin.h','w');
fprintf(fileID, '#define LUT_SIN_TABLE_SIZE %d\n',N_VALS);
% First half
fprintf(fileID, 'const float LUT_sin1 [%d] PROGMEM = {', N_VALS);
for i = 1:N_VALS
    if i < N_VALS
        fprintf(fileID,'%.10ff, ', sin(theta(i)));
    else
        fprintf(fileID,'%.10ff};', sin(theta(i)));
    end
end

% Second half
fprintf(fileID, '\n');
fprintf(fileID, 'const float LUT_sin2 [%d] PROGMEM = {', N_VALS);
for i = 1:N_VALS
    if i < N_VALS
        fprintf(fileID,'%.10ff, ', sin(theta(i+N_VALS)));
    else
        fprintf(fileID,'%.10ff};', sin(theta(i+N_VALS)));
    end
end
fclose(fileID);

%% sin uint16_t
THETA_RES = 0.01 * pi/180;
THETA_MIN = 0;
THETA_MAX = pi/2;

theta = THETA_MIN : THETA_RES : THETA_MAX - THETA_RES;
N_VALS = length(theta)/2;

fileID = fopen('LUT_sin.h','w');
fprintf(fileID, '#define LUT_SIN1_TABLE_SIZE %d\n',N_VALS);
% First half
fprintf(fileID, 'const uint16_t LUT_sin1 [%d] PROGMEM = {', N_VALS);
for i = 1:N_VALS
    if i < N_VALS
        fprintf(fileID,'%d, ', uint16(((2^16)-1)*sin(theta(i))));
    else
        fprintf(fileID,'%d};', uint16(((2^16)-1)*sin(theta(i))));
    end
end

% Second half
fprintf(fileID, '\n');
fprintf(fileID, '#define LUT_SIN2_TABLE_SIZE %d\n',N_VALS+1);
fprintf(fileID, 'const uint16_t LUT_sin2 [%d] PROGMEM = {', N_VALS);
for i = 1:N_VALS
    if i < N_VALS
        fprintf(fileID,'%d, ', uint16(((2^16)-1)*sin(theta(i + N_VALS))));
    else
        fprintf(fileID,'%d};', uint16(((2^16)-1)*sin(theta(i + N_VALS))));
    end
end
fclose(fileID);
