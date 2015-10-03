#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <math.h>
#include "Types.h"
#include "Arduino.h"
#include <avr/pgmspace.h>


#define M_PI_DEG	180.0f
#define M_PI_2_DEG	 90.0f

#define RAD_TO_DEG_F	57.295779513082320876798154814105f

#define write0(reg, pin)	reg |=  (1 << pin)
#define write1(reg, pin)	reg &= ~(1 << pin)


namespace Utils
{
	namespace FastMath
	{
		float atanFP(float x);
		float atan2(float x, float y);
	}

	float invSqrt(float x);
	float atan2(float y, float x);

	void quaternionToRPY(const quaternion_t * q, vec_float_3_t * const rpy);

	unsigned long timeFunction(void (*f)(void));
}
#endif