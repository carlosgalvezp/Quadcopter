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

T_RESOLUTION = 0.000125;
LUT_CONVERSION_FACTOR = 0.001;

t = (0 : T_RESOLUTION : 1);
N_VALS = length(t);

fileID = fopen('atanLUT.h','w');
fprintf(fileID, '#define LUT_ATAN2_RESOLUTION_DEG %.5ff\n',LUT_CONVERSION_FACTOR);
fprintf(fileID, '#define LUT_ATAN2_TABLE_SIZE %d\n',N_VALS);
fprintf(fileID, 'const uint16_t LUT_atan [%d] PROGMEM = {', N_VALS);
for i = 1:N_VALS
    if i < N_VALS
        fprintf(fileID,'%u, ', uint16((180/pi)*atan(t(i))/LUT_CONVERSION_FACTOR));
    else
        fprintf(fileID,'%u};', uint16((180/pi)*atan(t(i))/LUT_CONVERSION_FACTOR));
    end
end
fclose(fileID);

%% asin
THETA_MIN =  0.0 * pi/180;
THETA_MAX =  90.0 * pi/180;
RESOLUTION = 0.01;

% First, determine the minimum input resolution so that we obtain
% a minimum resolution of RESOLUTION degrees
step = 0.00001;
res = 0.1 + step;
out_res = 1;

while out_res > RESOLUTION
    res = res - step;
    t_in = sin(THETA_MIN) : res : sin(THETA_MAX);
    lut = asin(t_in) * 180 / pi;
    
    maxDelta = 0;
    for i = 1:length(lut) - 1
        delta = abs(lut(i) - lut(i+1));
        if delta > maxDelta
            maxDelta = delta;
            if maxDelta > RESOLUTION
                break;
            end
        end
    end
    fprintf('Res = %.10f, MaxDelta = %.10f deg, Table Size: %d\n',res, maxDelta, (THETA_MAX - THETA_MIN)/res);
    out_res = maxDelta;
end

%% cos
% LUT_COS_CONVERSION_FACTOR = 1.0 / (2^16 -1);
% COS_IN_RESOLUTION = 0.01;

% theta = 0 : COS_IN_RESOLUTION * pi/180 : pi/2;
N_VALS = 8096; %length(theta);
theta = linspace(0, pi/2, N_VALS);

fileID = fopen('LUT_cos.h','w');
fprintf(fileID, '#define LUT_COS_INDEX_FACTOR %d\n',1.0/(theta(end) - (theta(end-1))));
fprintf(fileID, '#define LUT_COS_TABLE_SIZE %d\n',N_VALS);
fprintf(fileID, 'const float LUT_cos [%d] PROGMEM = {', N_VALS);
for i = 1:N_VALS
    if i < N_VALS
        fprintf(fileID,'%.10ff, ', cos(theta(i)));
    else
        fprintf(fileID,'%.10ff};', cos(theta(i)));
    end
end
fclose(fileID);

