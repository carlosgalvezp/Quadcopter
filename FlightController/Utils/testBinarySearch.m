%% Binary search
array = 0 : 0.01 : 180;
key = 43.3;

idx = binarySearchIterative(array, key, uint32(1), uint32(length(array)));

%%
maxError = -1;
for i = 1 : length(array)
    key = array(i);
    idx = binarySearchIterative(array, key, uint32(1), uint32(length(array)));
    
    e = abs(array(idx) - key);
    if e > maxError
        maxError = e;
        fprintf('Max error: %.3f at i = %d\n', e, i);
    end
end