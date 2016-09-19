#ifndef MS5611_H
#define MS5611_H

#include <stdint.h>

#include "I2C.h"
#include "Arduino.h"

namespace Barometer
{
    // I2C device address
    const uint8_t kBaroI2CAddr = 0x77U;

    // Calculation constants
    const uint8_t  kBaroPMin  = 10U;		// mbar
    const uint16_t kBaroPMax  = 1200U;	    // mbar
    const int8_t   kBaroTMin  = -40;		// ºC
    const uint8_t  kBaroTMaxX = 85U;		// ºC
    const uint8_t  kBaroTRef  = 20U;		// ºC

    const uint8_t kBaroPromNCoeffs = 6U;  // Number of coefficients to be read from PROM
    const uint8_t kBaroNBytesToRead	= 3U; // Number of bytes to be read from either pressure or temperature

    const uint8_t kBaroRegProm     = 0xA0U;
    const uint8_t kBaroRegD1OSR256 = 0x40U;
    const uint8_t kBaroRegD2OSR256 = 0x50U;
    const uint8_t kBaroRegAdcRead  = 0x00U;

    const uint16_t kBaroConversionDelayUs = 1000U; // To make sure we read correct values

    const uint8_t kBaroStateIdle          = 0U;
    const uint8_t kBaroStateStartedD1Conv = 1U;
    const uint8_t kBaroStateStartedD2Conv = 2U;

	uint8_t init();
	uint8_t getData(float& pressure, float& temperature);

	void computeValues(float& pressure, float& temperature);
}
#endif
