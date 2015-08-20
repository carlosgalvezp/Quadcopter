#include "MPU6050.h"

uint8_t IMU::init()
{
	uint8_t data = 0;
	// Wake up IMU	
	if (I2C::writeReg(IMU_DEV_ADDR, IMU_REG_PWR_MGMT_1, &data, 1)) return 1;

	// Set accelerometer full scale to +- 8g
	data = 2 << 4;
	if(I2C::writeReg(IMU_DEV_ADDR, IMU_REG_ACCEL_CONFIG, &data, 1)) return 1;
	
	// Set gyro full scale to 2000�/deg
	data = 3 << 4;
	if(I2C::writeReg(IMU_DEV_ADDR, IMU_REG_GYRO_CONFIG, &data, 1)) return 1;

	// Set IMU to pass-through mode to access the magnetometer
	data = 1 << 1;
	if (I2C::writeReg(IMU_DEV_ADDR, IMU_REG_INT_PIN_CFG, &data, 1)) return 1;
	return 0;
}

uint8_t IMU::getData(IMU_data_t * const data)
{
	// Buffer to store the acc (6), gyro (6) and temperature (2) data
	uint8_t rawData[N_BYTES_BURST_READ];

	// Burst read all the registers, starting from ACC_X_MSB
	if (I2C::readReg(IMU_DEV_ADDR, IMU_REG_ACC_X_MSB, rawData, N_BYTES_BURST_READ)) return 1;

	// Store the received data properly
	data->acc.x = int16_t((rawData[0] << 8) | rawData[1]);
	data->acc.y = int16_t((rawData[2] << 8) | rawData[3]);
	data->acc.z = int16_t((rawData[4] << 8) | rawData[5]);

	data->temperature = int16_t((rawData[6] << 8) | rawData[7]);

	data->gyro.x = int16_t((rawData[8] << 8) | rawData[9]);
	data->gyro.y = int16_t((rawData[10] << 8) | rawData[11]);
	data->gyro.z = int16_t((rawData[12] << 8) | rawData[13]);

	return 0;
}