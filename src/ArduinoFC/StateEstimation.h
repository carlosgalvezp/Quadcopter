#ifndef STATE_ESTIMATION_H
#define STATE_ESTIMATION_H

#include "Types.h"
#include "Madgwick.h"
#include "Mahony.h"


namespace StateEstimation
{
	uint8_t estimateRPY(const SensorFusion_data_t * const sensorData, vec_float_3_t * const RPY);
}

#endif
