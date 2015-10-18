#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include "Types.h"
#include "Arduino.h"
#include <avr/pgmspace.h>


#define M_PI_DEG	180.0f
#define M_PI_2_DEG	 90.0f

#define RAD_TO_DEG_F	57.295779513082320876798154814105f

#define write0(reg, pin)	reg |=  (1 << pin)
#define write1(reg, pin)	reg &= ~(1 << pin)
#define _abs(x) x > 0 ? x : -x)

class Utils
{
public:
	static void quaternionToRPY(const quaternion_t * q, vec_float_3_t * const rpy);
	//static float normalizeAngle(float x);

	class FastMath
	{
	public:
		static float invSqrt(float x);
		static float atan2(float x, float y);		
		static float cos(float x);
		static float sin(float x);
	private:
		static float atanFP(float x);
		static float readCosLUT(float x);
	};
};
#endif