#include "MPU6050.h"

namespace IMU
{
	// Buffer to store the acc (6), gyro (6) and temperature (2) data
	uint8_t rawData[N_BYTES_BURST_READ];

	uint8_t init()
	{
		uint8_t data = 0;
		// Wake up IMU	
		if (I2C::writeReg(IMU_DEV_ADDR, IMU_REG_PWR_MGMT_1, &data, 1)) return 1;

		// Set accelerometer full scale to +- 8g
		data = 2 << 3;
		if (I2C::writeReg(IMU_DEV_ADDR, IMU_REG_ACCEL_CONFIG, &data, 1)) return 1;

		// Set gyro full scale to 2000º/deg
		data = 3 << 3;
		if (I2C::writeReg(IMU_DEV_ADDR, IMU_REG_GYRO_CONFIG, &data, 1)) return 1;

		// Set IMU to pass-through mode to access the magnetometer
		data = 1 << 1;
		if (I2C::writeReg(IMU_DEV_ADDR, IMU_REG_INT_PIN_CFG, &data, 1)) return 1;
		return 0;
	}

	uint8_t getData(IMUData& data)
	{
		// Burst read all the registers, starting from ACC_X_MSB
		if (I2C::readReg(IMU_DEV_ADDR, IMU_REG_ACC_X_MSB, rawData, N_BYTES_BURST_READ)) return 1;

		// Store the raw data
		data.acc_raw.x = ((int16_t)rawData[0]) << 8 | rawData[1];
		data.acc_raw.y = ((int16_t)rawData[2]) << 8 | rawData[3];
		data.acc_raw.z = ((int16_t)rawData[4]) << 8 | rawData[5];

		data.gyro_raw.x = ((int16_t)rawData[8]) << 8 | rawData[9];
		data.gyro_raw.y = ((int16_t)rawData[10]) << 8 | rawData[11];
		data.gyro_raw.z = ((int16_t)rawData[12]) << 8 | rawData[13];

		// Convert to real values
		//data.acc.x = ACC_SENSITIVITY * data.acc_raw.x; // Not needed, the filter already normalizes
		//data.acc.y = ACC_SENSITIVITY * data.acc_raw.y;
		//data.acc.z = ACC_SENSITIVITY * data.acc_raw.z;

		data.gyro.x = GYRO_SENSITIVITY * data.gyro_raw.x;
		data.gyro.y = GYRO_SENSITIVITY * data.gyro_raw.y;
		data.gyro.z = GYRO_SENSITIVITY * data.gyro_raw.z;

		return 0;
	}
}
