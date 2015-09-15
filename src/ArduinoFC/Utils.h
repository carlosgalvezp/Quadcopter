#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <math.h>
#include "Types.h"
#include "Arduino.h"

namespace Utils
{
	float invSqrt(float x);
	float atan2(float y, float x);

	void quaternionToRPY(const quaternion_t * q, vec_float_3_t * const rpy);
}
#endif