#ifndef MADGWICK_H
#define MADGWICK_H

#include <math.h>

#include "Utils.h"
#include "Types.h"

#include "Arduino.h"

#define betaDef			0.25f		// 2 * proportional gain

namespace Madgwick
{
	// Function declarations
	void MARGupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
	void IMUupdate(float gx, float gy, float gz, float ax, float ay, float az);

	void getQuaternion(quaternion_t * const q);
}

#endif
