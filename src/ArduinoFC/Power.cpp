#include "Power.h"

namespace Power
{
	bool requestedVoltage(false);
	bool requestedCurrent(false);
}

bool Power::readVoltage(uint16_t *voltage)
{
	if (!requestedVoltage)
	{
		if (!requestedCurrent)
		{
			requestedVoltage = true;

			// Select chanel
			ADMUX = (ADMUX & 0b11100000) | ADC_CHANNEL_VOLTAGE;

			// Start conversion
			ADCSRA |= (1 << ADSC);
		}
	}
	else
	{
		if (!isADCBusy()) // Requested ADC and finished
		{
			*voltage = ((((uint16_t)ADCH) << 8) & 0x0300) | (((uint16_t)ADCL) & 0x00FF);
			requestedVoltage = false;
			return true;
		}
	}
	return false;
}

bool Power::readCurrent(uint16_t *current)
{
	if (!requestedCurrent)
	{
		if (!requestedVoltage)
		{
			requestedCurrent = true;

			// Select chanel
			ADMUX = (ADMUX & 0b11100000) | ADC_CHANNEL_VOLTAGE;

			// Start conversion
			ADCSRA |= (1 << ADSC);
		}
	}
	else
	{
		if (!isADCBusy()) // Requested ADC and finished
		{
			*current = ((((uint16_t)ADCH) << 8) & 0x0300) | (((uint16_t)ADCL) & 0x00FF);
			requestedCurrent = false;
			return true;
		}
	}
	return false;
}
