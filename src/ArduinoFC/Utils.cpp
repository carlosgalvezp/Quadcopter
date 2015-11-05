#include "Utils.h"

#include "LUT_atan.h"
#include "LUT_sin.h"

// Fast inverse square-root
// See: http://en.wikipedia.org/wiki/Fast_inverse_square_root
// Optimized: http://www.multiwii.com/forum/viewtopic.php?f=8&t=4246&p=51412
float Utils::FastMath::invSqrt(float x)
{
	union
	{
		float f;
		uint32_t u;
	} y = { x };
	y.u = 0x5F1FFFF9 - (y.u >> 1);
	return y.f * (1.68191409f - 0.703952253f * x * y.f * y.f);
}

void Utils::quaternionToRPY(const quaternion_t * const q, vec_float_3_t * const rpy)
{
	rpy->x = Utils::FastMath::atan2(2.0f * (q->q0 * q->q1 + q->q2 * q->q3), 1.0f - 2.0f * (q->q1 * q->q1 + q->q2 * q->q2));
	//rpy->x = atan2(2.0f * (q->q0 * q->q1 + q->q2 * q->q3), 1.0f - 2.0f * (q->q1 * q->q1 + q->q2 * q->q2));
	rpy->y = asin(2.0f * (q->q0 * q->q2 - q->q3 * q->q1));
	//rpy->z = 0;// atan2(2.0*(q->q0*q->q3 + q->q1*q->q2), 1.0 - 2.0*(q->q2*q->q2 + q->q3*q->q3)); yaw is obtained from compass
}

float Utils::FastMath::atan2(float y, float x)
{
	// Determine octant and compute angle
	if (x > 0)
	{
		if (y > 0)
		{
			if (x > y)						// 1st octant
			{
				return Utils::FastMath::atanFP(y / x);
			}
			else							// 2nd octant
			{
				return M_PI_2_DEG - Utils::FastMath::atanFP(x / y);
			}
		}
		else // y < 0
		{
			y = -y;
			if (x > y)						// 8th octant
			{
				return -Utils::FastMath::atanFP(y / x);
			}
			else							// 7th octant
			{
				return -M_PI_2_DEG + Utils::FastMath::atanFP(x / y);
			}
		}
	}
	else // x < 0
	{
		x = -x;
		if (y > 0)
		{
			if (x > y)			// 4th octant
			{
				return M_PI_DEG - Utils::FastMath::atanFP(y / x);
			}
			else				// 3rd octant
			{
				return M_PI_2_DEG + Utils::FastMath::atanFP(x / y);
			}
		}
		else // y < 0
		{
			y = -y;
			if (x > y)		    // 5th octant
			{
				return -M_PI_DEG + Utils::FastMath::atanFP(y / x);
			}
			else				// 6th octant
			{
				return -M_PI_2_DEG - Utils::FastMath::atanFP(x / y);
			}
		}
	}
}

/*
Computes atan(x) using a look-up table (LUT)
Input: t \in [0, 1] i.e.: first octant
Output: angle in degrees \in [0, 45]
It takes around 48 us
*/
float Utils::FastMath::atanFP(float t)
{
	// Compute index in LUT
	uint16_t idx = (uint16_t)(t * (LUT_ATAN2_TABLE_SIZE - 1));
	
	// Read value from LUT
	uint16_t val = pgm_read_word_near(LUT_atan + idx);	// 12 us

	// Transform to actual degrees by multiplying by the resolution
	return LUT_ATAN2_RESOLUTION_DEG * val;
}

/*
	Assumptions:
	-x is expressed in 0.01 degrees. For example: x = 10000 == 100 deg
	-180 <= x <= 180
*/
float Utils::FastMath::sin(int16_t x)
{
	if (x < 0)		// sin(x) = -sin(x)
	{
		x = -x;

		if (x > 9000) x = 18000 - x;

		if (x < 4500)
			return -pgm_read_float_near(LUT_sin1 + x);
		else
			return -pgm_read_float_near(LUT_sin2 + x - 4500);
	}
	else
	{
		if (x > 9000) x = 18000 - x;

		if (x < 4500)
			return pgm_read_float_near(LUT_sin1 + x);
		else
			return pgm_read_float_near(LUT_sin2 + x - 4500);

	}
}


/*
Assumptions:
-x is expressed in 0.01 degrees. For example: x = 10000 == 100 deg
-180 <= x <= 180
*/
float Utils::FastMath::cos(int16_t x)
{
	if (x < 0)	x = -x; // cos(x) = cos(-x)
	
	return Utils::FastMath::sin(9000 - x);
}



// ** Assumptions:
// x is in DEGREES
// 0 <= x <= 90 
float Utils::FastMath::readCosLUT(float x)
{
	//if (x >= 0 && x <= 90)
	//{
	//	// Compute index in LUT
	//	uint16_t idx = (uint16_t)(x * LUT_COS_INDEX_FACTOR);

	//	// Read value from LUT
	//	uint16_t val = pgm_read_word_near(LUT_cos + idx);

	//	// Transform to actual degrees by multiplying by the resolution
	//	return LUT_COS_CONVERSION_FACTOR * val;
	//}
	//else
	//{
	//	return 0;
	//}
	return 0;
}
