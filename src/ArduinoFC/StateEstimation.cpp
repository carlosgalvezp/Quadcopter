#include "StateEstimation.h"


uint8_t StateEstimation::estimateAttitude(const Sensor_data_t * const sensorData, quaternion_t * const q, vec_float_3_t * const rpy)
{
	// Mahony filter
	Mahony::IMUupdate(sensorData->imu.gyro.x,    sensorData->imu.gyro.y,    sensorData->imu.gyro.z,
					  sensorData->imu.acc_raw.x, sensorData->imu.acc_raw.y, sensorData->imu.acc_raw.z);

	// Retrieve quaternion
	Mahony::getQuaternion(q);

	// Transform into fixed-point RPY
	Utils::quaternionToRPY(q, rpy);
	return 0;
}

