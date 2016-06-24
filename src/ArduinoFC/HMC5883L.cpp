#include "HMC5883L.h"

namespace Magnetometer
{
	uint8_t rawData[MAGNETOMETER_N_READ_BYTES];

	uint8_t init()
	{
		uint8_t data;

		// Set output rate to 15 Hz, 8 measurements average, standard measurement
		data = 0b01110000;
		if (I2C::writeReg(MAGNETOMETER_DEV_ADDR, MAGNETOMETER_REG_CONF_A, &data, 1)) return 1;

		// Set gain to 1090 Ga/LSB (default value)
		data = 0b00100000;
		if (I2C::writeReg(MAGNETOMETER_DEV_ADDR, MAGNETOMETER_REG_CONF_B, &data, 1)) return 1;

		// Set to continuous measurement mode
		data = 0x00;
		if (I2C::writeReg(MAGNETOMETER_DEV_ADDR, MAGNETOMETER_REG_MODE, &data, 1)) return 1;

		return 0;
	}

	uint8_t getData(Vector3<float>* const data)
	{
		// Burst-read all the registers, starting from X_MSB
		if (I2C::readReg(MAGNETOMETER_DEV_ADDR, MAGNETOMETER_REG_DATA, rawData, MAGNETOMETER_N_READ_BYTES)) return 1;

		// Convert and output the data
		data->x = MAGNETOMETER_SENSITIVITY * (float)((((int16_t)rawData[0]) << 8) | rawData[1]);
		data->y = MAGNETOMETER_SENSITIVITY * (float)((((int16_t)rawData[4]) << 8) | rawData[5]);
		data->z = MAGNETOMETER_SENSITIVITY * (float)((((int16_t)rawData[2]) << 8) | rawData[3]);

		return 0;
	}
}