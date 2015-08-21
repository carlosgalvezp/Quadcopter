#include "HMC5883L.h"

uint8_t Magnetometer::init()
{
	uint8_t data;

	// Set output rate to 75 Hz, no sample average, standard measurement
	data = 0b00011000;
	if(I2C::writeReg(MAGNETOMETER_DEV_ADDR, MAGNETOMETER_REG_CONF_A, &data, 1)) return 1;
	
	// Set gain to 1090
	data = 0x00;
	if (I2C::writeReg(MAGNETOMETER_DEV_ADDR, MAGNETOMETER_REG_CONF_B, &data, 1)) return 1;
	
	// Set to continuous measurement mode
	data = 0x00;
	if (I2C::writeReg(MAGNETOMETER_DEV_ADDR, MAGNETOMETER_REG_MODE, &data, 1)) return 1;

	return 0;
}

uint8_t Magnetometer::getData(vec_float_3_t * data)
{
	// Buffer to store the data (2 bytes per axis)
	uint8_t rawData[MAGNETOMETER_N_READ_BYTES];

	// Burst read all the registers, starting from X_MSB
	if (I2C::readReg(MAGNETOMETER_DEV_ADDR, MAGNETOMETER_REG_DATA, rawData, MAGNETOMETER_N_READ_BYTES)) return 1;

	// Store the received data properly
	data->x = (float)(MAGNETOMETER_SENSITIVITY * ((int16_t)rawData[0] << 8 | rawData[1]));
	data->y = (float)(MAGNETOMETER_SENSITIVITY * ((int16_t)rawData[2] << 8 | rawData[3]));
	data->z = (float)(MAGNETOMETER_SENSITIVITY * ((int16_t)rawData[4] << 8 | rawData[5]));

	return 0;
}
