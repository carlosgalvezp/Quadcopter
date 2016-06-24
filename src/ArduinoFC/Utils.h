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

namespace Utils
{
	void quaternionToRPY(const Quaternion& q, Vector3<int16_t>& rpy);

	namespace FastMath
	{
		float invSqrt(float x);
		int16_t atan2(float x, float y);
		float cos(int16_t x);
		float sin(int16_t x);
		int16_t acos(float x);
		int16_t asin(float x);

		uint16_t atanFP(float x);

	}

	uint16_t binarySearchProgMemUint16(const uint16_t *data, uint16_t minIdx, uint16_t maxIdx, uint16_t key);
};

//void foo();

#endif