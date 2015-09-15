#include "Utils.h"


// Fast inverse square-root
// See: http://en.wikipedia.org/wiki/Fast_inverse_square_root
// Optimized: http://www.multiwii.com/forum/viewtopic.php?f=8&t=4246&p=51412
float Utils::invSqrt(float x)
{
	union
	{
		float f;
		uint32_t u;
	} y = { x };
	y.u = 0x5F1FFFF9 - (y.u >> 1);
	return y.f * (1.68191409f - 0.703952253f * x * y.f * y.f);
}

float Utils::atan2(float x, float y)
{
	float a = min(abs(x), abs(y)) / max(abs(x), abs(y));
	float s = a * a;
	float r = ((-0.0464964749f * s + 0.15931422f) * s - 0.327622764f) * s * a + a;
	if (abs(y) > abs(x)) r = 1.57079637f - r;
	if (x < 0) r = 3.14159274f - r;
	if (y < 0) r = -r;

	return r;
}

void Utils::quaternionToRPY(const quaternion_t * const q, vec_float_3_t * const rpy)
{
	rpy->x = atan2(2.0*(q->q0*q->q1 + q->q2*q->q3), 1.0 - 2.0*(q->q1*q->q1 + q->q2*q->q2));
	rpy->y = asin(2.0*(q->q0*q->q2 - q->q3*q->q1));
	rpy->z = atan2(2.0*(q->q0*q->q3 + q->q1*q->q2), 1.0 - 2.0*(q->q2*q->q2 + q->q3*q->q3));
}