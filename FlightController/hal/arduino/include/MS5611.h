#ifndef MS5611_H
#define MS5611_H

#include <stdint.h>

#include "I2C.h"
#include "Arduino.h"

#define BARO_DEV_ADDR		0x77

// Calculation constants
#define BARO_P_MIN			10		// mbar
#define BARO_P_MAX			1200	// mbar
#define BARO_T_MIN			-40		// ºC
#define BARO_T_MAX			85		// ºC
#define BARO_T_REF			20		// ºC

#define BARO_PROM_N_COEFFS	6		// Number of coefficients to be read from PROM
#define BARO_READ_N_BYTES	3		// Number of bytes to be read from either pressure or temperature

#define BARO_REG_PROM				0xA0
#define BARO_REG_D1_OSR_256			0x40
#define BARO_REG_D2_OSR_256			0x50
#define BARO_REG_ADC_READ			0x00

#define BARO_CONVERSION_DELAY_US	1000 // To make sure we read correct values

#define BARO_STATE_IDLE							0
#define BARO_STATE_STARTED_D1_CONVERSION		1
#define BARO_STATE_STARTED_D2_CONVERSION		2

namespace Barometer
{
	uint8_t init();
	uint8_t getData(float& pressure, float& temperature);

	void computeValues(float& pressure, float& temperature);
}
#endif