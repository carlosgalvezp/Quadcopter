#pragma once
#ifndef ADC_H
#define ADC_H

#include <stdint.h>

#define ADC_CHANNEL_VOLTAGE		0 // ADC0
#define ADC_CHANNEL_CURRENT		1 // ADC1

#define N_ADC_CHANNELS			2 // Number of channels in use
#define MUX_MASK_INV			0b11100000

namespace Adc
{
	namespace Power
	{
		void readVoltage(uint16_t *voltage);
		void readCurrent(uint16_t *current);
	}

    void init();
}

#endif

