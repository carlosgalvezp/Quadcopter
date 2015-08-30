#ifndef STATE_ESTIMATION_H
#define STATE_ESTIMATION_H

#include "Types.h"
#include "Madgwick.h"
#include "Mahony.h"


namespace StateEstimation
{
	uint8_t estimateAttitude(const Sensor_data_t * const sensorData, quaternion_t * const q);
}

#endif
