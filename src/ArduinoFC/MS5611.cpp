#include "MS5611.h"

// Coefficients read from PROM to be used in calculations
uint16_t prom_coefficients[BARO_PROM_N_COEFFS];

// Memory of values in case we don't have time to read
float old_pressure, old_temperature;
uint32_t d1, d2;

uint8_t state;
unsigned long last_t;

uint8_t Barometer::init()
{
	// Read values from PROM and store for future use
	uint8_t data[2];
	for (uint8_t i = 0; i < BARO_PROM_N_COEFFS; ++i)
	{
		if (I2C::readReg(BARO_DEV_ADDR, BARO_REG_PROM | ((i+1) << 1), data, 2)) return 1;
		prom_coefficients[i] = uint16_t(data[0] << 8 | data[1]);
	}

	state = 0;
	return 0;
}

uint8_t Barometer::getData(float * const pressure, float * const temperature)
{
	*pressure = old_pressure;
	*temperature = old_temperature;
	uint8_t data[BARO_READ_N_BYTES];
	
	// State machine in order to avoid active wait when reading the sensor registers
	switch (state)
	{
		case BARO_STATE_IDLE: // Start D1 conversion
			if (I2C::writeReg(BARO_DEV_ADDR, BARO_REG_D1_OSR_256, NULL, 0)) return 1; 
			last_t = micros();
			state = BARO_STATE_STARTED_D1_CONVERSION;
			return 1;

		case BARO_STATE_STARTED_D1_CONVERSION: // Read D1 and start D2 conversion
			if ( (micros() - last_t) > BARO_CONVERSION_DELAY_US)
			{
				if (I2C::readReg(BARO_DEV_ADDR, BARO_REG_ADC_READ, data, BARO_READ_N_BYTES)) return 1; // Read D1 data
				d1 = (uint32_t)data[0] << 16 | (uint32_t)data[1] << 8 | (uint32_t)data[2];
				
				if (I2C::writeReg(BARO_DEV_ADDR, BARO_REG_D2_OSR_256, NULL, 0)) return 1; // Initiate D2 conversion
				last_t = micros();
				state = BARO_STATE_STARTED_D2_CONVERSION;
			}
			return 1;
			

		case BARO_STATE_STARTED_D2_CONVERSION:
			if ((micros() - last_t) > BARO_CONVERSION_DELAY_US)
			{
				if (I2C::readReg(BARO_DEV_ADDR, BARO_REG_ADC_READ, data, BARO_READ_N_BYTES)) return 1; // Read data
				d2 = (uint32_t)data[0] << 16 | (uint32_t)data[1] << 8 | (uint32_t)data[2];

				// After reading all the data, we can compute
				computeValues(pressure, temperature);
				old_pressure = *pressure;
				old_temperature = *temperature;
				state = BARO_STATE_IDLE;
				return 0; 
			}
			return 1;
		default:
			Serial.println("Barometer in unknown state!");
			return 1;
	}
}

void Barometer::computeValues(float * const pressure, float * const temperature)
{
	// Compute pressure and temperature according to datasheet
	int32_t dT = (int32_t)d2 - ((int32_t)prom_coefficients[4] << 8);
	*temperature = 0.01f * (2000 + ((dT * (int32_t)prom_coefficients[5]) >> 23));

	int64_t off = ((int64_t)prom_coefficients[1] << 16) + (((int64_t)prom_coefficients[3] * dT) >> 7);
	int64_t sens = ((int64_t)prom_coefficients[0] << 15) + (((int64_t)prom_coefficients[2] * dT) >> 8);

	*pressure = 0.01f * (((((int64_t)d1 * sens) >> 21) - off) >> 15);
}
