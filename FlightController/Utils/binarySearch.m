function idx = binarySearch(array, key, minIdx, maxIdx)
%BINARYSEARCH Summary of this function goes here
%   Detailed explanation goes here

% Base case
if (maxIdx - minIdx) < 2
    if maxIdx == minIdx 
        idx = maxIdx;
    else
        if abs(array(minIdx) - key) < abs(array(maxIdx) - key)
            idx = minIdx;
        else
            idx = maxIdx;
        end
    end
% Recursion
else    
    idxMid = (minIdx + maxIdx)/2;
        
    if array(idxMid) > key
        idx = binarySearch(array, key, minIdx, idxMid);        
    else
        idx = binarySearch(array, key, idxMid, maxIdx);
    end    
end

end
            
