#ifndef STATE_ESTIMATION_H
#define STATE_ESTIMATION_H

#include "Types.h"
#include "Madgwick.h"
#include "Mahony.h"

namespace StateEstimation
{
	uint8_t estimateAttitude(const Sensor_data_t *sensorData, quaternion_t *q, vec_int16_3_t *rpy);
}

#endif
