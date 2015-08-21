#include "MS5611.h"

// Coefficients read from PROM to be used in calculations
uint16_t prom_coefficients[BARO_PROM_N_COEFFS];

uint8_t Barometer::init()
{
	// Read values from PROM and store for future use
	uint8_t data[2];
	for (uint8_t i = 0; i < BARO_PROM_N_COEFFS; ++i)
	{
		if (I2C::readReg(BARO_DEV_ADDR, BARO_REG_PROM | ((i+1) << 1), data, 2)) return 1;
		prom_coefficients[i] = uint16_t(data[0] << 8 | data[1]);
	}
	return 0;
}

uint8_t Barometer::getData(float * const pressure, float * const temperature)
{
	uint8_t data[BARO_READ_N_BYTES];
	uint32_t d1, d2;
	
	// Read raw pressure and temperature
	if (I2C::writeReg(BARO_DEV_ADDR, BARO_REG_D1_OSR_256, NULL, 0)) return 1; // Initiate conversion
	delayMicroseconds(BARO_CONVERSION_DELAY_US);

	if (I2C::readReg(BARO_DEV_ADDR, BARO_REG_ADC_READ, data, BARO_READ_N_BYTES)) return 1; // Read data
	d1 = uint32_t(data[0]) << 16 | uint32_t(data[1]) << 8 | uint32_t(data[2]);

	if (I2C::writeReg(BARO_DEV_ADDR, BARO_REG_D2_OSR_256, NULL, 0)) return 1; // Initiate conversion
	delayMicroseconds(BARO_CONVERSION_DELAY_US);

	if (I2C::readReg(BARO_DEV_ADDR, BARO_REG_ADC_READ, data, BARO_READ_N_BYTES)) return 1; // Read data
	d2 = uint32_t(data[0]) << 16 | uint32_t(data[1]) << 8 | uint32_t(data[2]);

	// Compute pressure and temperature according to datasheet
	int32_t dT = int32_t(d2) - (int32_t(prom_coefficients[4]) << 8);
	*temperature = 0.01f * (int32_t(2000) + ((dT * int32_t(prom_coefficients[5])) >> 23) );

	int64_t off = (int64_t(prom_coefficients[1]) << 16) + ((int64_t(prom_coefficients[3]) * dT) >> 7);
	int64_t sens = (int64_t(prom_coefficients[0]) << 15) + ((int64_t(prom_coefficients[2]) * dT) >> 8);

	*pressure = 0.01f * ((((int64_t(d1) * sens) >> 21) - off) >> 15);
	return 0;
}