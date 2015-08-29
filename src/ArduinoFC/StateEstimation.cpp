#include "StateEstimation.h"


uint8_t StateEstimation::estimateRPY(const Sensor_data_t * const sensorData, vec_float_3_t * const RPY)
{
	Mahony::IMUupdate(sensorData->imu.gyro.x, sensorData->imu.gyro.y, sensorData->imu.gyro.z, 
					  sensorData->imu.acc.x,  sensorData->imu.acc.y,  sensorData->imu.acc.z);
	Mahony::getRPY(RPY);
	return 0;
}

