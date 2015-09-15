#include "StateEstimation.h"


uint8_t StateEstimation::estimateAttitude(const Sensor_data_t * const sensorData, quaternion_t * const q, vec_float_3_t * const rpy)
{
	//Madgwick::IMUupdate(sensorData->imu.gyro.x, sensorData->imu.gyro.y, sensorData->imu.gyro.z, 
	//			        sensorData->imu.acc.x,  sensorData->imu.acc.y,  sensorData->imu.acc.z);
	//Madgwick::getQuaternion(q);
	Mahony::IMUupdate(sensorData->imu.gyro.x, sensorData->imu.gyro.y, sensorData->imu.gyro.z,
		sensorData->imu.acc.x, sensorData->imu.acc.y, sensorData->imu.acc.z);
	Mahony::getQuaternion(q);
	Utils::quaternionToRPY(q, rpy);
	return 0;
}

