#include "MS5611.h"

namespace Barometer
{

// Coefficients read from PROM to be used in calculations
uint16_t prom_coefficients[kBaroPromNCoeffs];

// Buffer to read I2C data
uint8_t data[kBaroNBytesToRead];

// Memory of values in case we don't have time to read
float old_pressure, old_temperature;
uint32_t d1, d2;

// Conversion state
uint8_t state;
unsigned long last_t;

uint8_t init()
{
	// Read values from PROM and store for future use
	uint8_t data[2];
    for (uint8_t i = 0; i < kBaroPromNCoeffs; ++i)
	{
        if (I2C::readReg(kBaroI2CAddr, kBaroRegProm | ((i+1) << 1), data, 2)) return 1;
		prom_coefficients[i] = (uint16_t)data[0] << 8 | (uint16_t)data[1];
	}

	state = 0;
	return 0;
}

uint8_t getData(float& pressure, float& temperature)
{
	pressure = old_pressure;
	temperature = old_temperature;
	
	// State machine in order to avoid active wait when reading the sensor registers
	switch (state)
	{
        case kBaroStateIdle: // Start D1 conversion
            if (I2C::writeReg(kBaroI2CAddr, kBaroRegD1OSR256, NULL, 0)) return 1;
			last_t = micros();
            state = kBaroStateStartedD1Conv;
			return 1;

        case kBaroStateStartedD1Conv: // Read D1 and start D2 conversion
            if ( (micros() - last_t) > kBaroConversionDelayUs)
			{
                if (I2C::readReg(kBaroI2CAddr, kBaroRegAdcRead, data, kBaroNBytesToRead)) return 1; // Read D1 data
				d1 = (uint32_t)data[0] << 16 | (uint32_t)data[1] << 8 | (uint32_t)data[2];
				
                if (I2C::writeReg(kBaroI2CAddr, kBaroRegD2OSR256, NULL, 0)) return 1; // Initiate D2 conversion
				last_t = micros();
                state = kBaroStateStartedD2Conv;
			}
			return 1;
			

        case kBaroStateStartedD2Conv:
            if ((micros() - last_t) > kBaroConversionDelayUs)
			{
                if (I2C::readReg(kBaroI2CAddr, kBaroRegAdcRead, data, kBaroNBytesToRead)) return 1; // Read data
				d2 = (uint32_t)data[0] << 16 | (uint32_t)data[1] << 8 | (uint32_t)data[2];

				// After reading all the data, we can compute
				computeValues(pressure, temperature);
				old_pressure = pressure;
				old_temperature = temperature;
                state = kBaroStateIdle;
				return 0; 
			}
			return 1;
		default:
			return 1;
	}
}

void computeValues(float& pressure, float& temperature)
{
	// Compute pressure and temperature according to datasheet
	int32_t dT = (int32_t)d2 - ((int32_t)prom_coefficients[4] << 8);
	//*temperature = 0.01f * (2000 + ((dT * (int32_t)prom_coefficients[5]) >> 23));
	temperature = 0; // Not interested in computing temperature, let's save some CPU cycles!

	int64_t off = ((int64_t)prom_coefficients[1] << 16) + (((int64_t)prom_coefficients[3] * dT) >> 7);
	int64_t sens = ((int64_t)prom_coefficients[0] << 15) + (((int64_t)prom_coefficients[2] * dT) >> 8);

	pressure = 0.01f * (((((int64_t)d1 * sens) >> 21) - off) >> 15);
}

}  // namespace Barometer
