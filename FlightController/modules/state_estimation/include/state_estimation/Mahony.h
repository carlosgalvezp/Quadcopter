#ifndef MAHONY_H
#define MAHONY_H

#include "Utils.h"
#include "core/Types.h"
#include "Arduino.h"
#include <math.h>

#define twoKpDef	(2.0f * 20.0f)	// 2 * proportional gain
#define twoKiDef	(2.0f * 0.0f)	// 2 * integral gain

namespace Mahony
{
	void MARGupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
	void IMUupdate(float gx, float gy, float gz, float ax, float ay, float az);
	void getRPY(Vector3<float>* const rpy);
	
	void getQuaternion(Quaternion& q);
}

#endif
