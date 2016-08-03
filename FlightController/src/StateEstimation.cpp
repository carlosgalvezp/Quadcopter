#include "StateEstimation.h"


uint8_t StateEstimation::estimateAttitude(const Sensor_data_t *sensorData, quaternion_t *q, vec_int16_3_t *rpy)
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

