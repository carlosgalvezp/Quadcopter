#include "StateEstimation.h"


uint8_t StateEstimation::estimateAttitude(const Sensor_data_t * const sensorData, quaternion_t * const q, vec_float_3_t * const rpy)
{
	unsigned long t1, t2;
	Mahony::IMUupdate(sensorData->imu.gyro.x, sensorData->imu.gyro.y, sensorData->imu.gyro.z,
					  sensorData->imu.acc_raw.x, sensorData->imu.acc_raw.y, sensorData->imu.acc_raw.z);
	Mahony::getQuaternion(q);
	//t1 = micros();
	Utils::quaternionToRPY(q, rpy);
	//t2 = micros();
	//Serial.println("RPY: " + String(t2 - t1));
	return 0;
}

