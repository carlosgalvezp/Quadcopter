function idx = binarySearchIterative(array, key, minIdx, maxIdx)
%BINARYSEARCH Summary of this function goes here
%   Detailed explanation goes here

while (maxIdx - minIdx) > 1
    idxMid = (minIdx + maxIdx)/2;
        
    if array(idxMid) > key
        maxIdx = idxMid;
    else
        minIdx = idxMid;
    end        
end

% Base case
if maxIdx == minIdx 
    idx = maxIdx;
else
    if abs(array(minIdx) - key) < abs(array(maxIdx) - key)
        idx = minIdx;
    else
        idx = maxIdx;
    end
end
end
            
