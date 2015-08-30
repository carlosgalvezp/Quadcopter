#include "StateEstimation.h"


uint8_t StateEstimation::estimateAttitude(const Sensor_data_t * const sensorData, quaternion_t * const q)
{
	Madgwick::IMUupdate(sensorData->imu.gyro.x, sensorData->imu.gyro.y, sensorData->imu.gyro.z, 
				        sensorData->imu.acc.x,  sensorData->imu.acc.y,  sensorData->imu.acc.z);
	Madgwick::getQuaternion(q);
	return 0;
}

