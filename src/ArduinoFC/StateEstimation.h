#ifndef STATE_ESTIMATION_H
#define STATE_ESTIMATION_H

#include "Types.h"
#include "Madgwick.h"
#include "Mahony.h"

namespace StateEstimation
{
	uint8_t estimateAttitude(const SensorData* sensorData, Quaternion* q, Vector3<int16_t>* rpy);
}

#endif
