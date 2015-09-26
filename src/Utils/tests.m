%% Look-up table for atan2
close all, clc

% Generate look-up table
THETA_MIN =  0;
THETA_MAX =  45;
TABLE_SIZE = 6000; % At least around 5880 elements for 0.01 deg resolution

test_res = 0.001;
x = [-1 : test_res : -test_res, test_res:test_res:1];
y = x;

error = zeros(length(x), length(y));

atan_LUT = atan(linspace(0,1,TABLE_SIZE)) * 180 / pi;

for i = 1: length(x)
    for j = 1 : length(y)
        x_i = x(i);
        y_j = y(j);
        
        val = atan2Fast(y_j,x_i, atan_LUT);
        valReal = atan2(y_j,x_i) * 180 / pi;
        
        error(i,j) = valReal - val;
    end
end

fprintf('Error [deg] --- max: %.10f, min: %.10f, avg: %.10f, std: %.10f\n',...
    max(abs(error(:))), min(abs(error(:))), mean(error(:)), std(error(:)));
