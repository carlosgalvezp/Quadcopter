function deg = atan2Fast(y,x, LUT)
%ATAN2FAST Summary of this function goes here
%   Detailed explanation goes here
% Def
M_PI_2_DEG = 90;
M_PI_DEG = 180;

	% Determine octant and compute angle
	if (x > 0)	
		if (y > 0)		
			if (x > y)						% 1st octant			
				deg = atanFast(y / x, LUT);
            else							% 2nd octant			
				deg = M_PI_2_DEG - atanFast(x / y, LUT);
            end
        else                                % y < 0		
			y = -y;
			if (x > y)						% 8th octant			
				deg = -atanFast(y / x, LUT);
            else							% 7th octant			
				deg = -M_PI_2_DEG + atanFast(x / y, LUT);
            end
        end	
	else % x < 0	
		x = -x;
		if (y > 0)
			if (x > y)			% 4th octant
				deg = M_PI_DEG - atanFast(y / x, LUT);
			else				% 3rd octant			
				deg = M_PI_2_DEG + atanFast(x / y, LUT);
            end		
		else % y < 0		
			y = -y;
			if (x > y)		    % 5th octant			
				deg = -M_PI_DEG + atanFast(y / x, LUT);                
			else				% 6th octant			
				deg = -M_PI_2_DEG - atanFast(x / y, LUT);
            end
        end
    end    
end


function deg = atanFast(t, LUT)
% Compute index in table
idx = min(round(t * length(LUT)+1), length(LUT));

% Read from it
deg = LUT(idx);
end

