#pragma once
#ifndef POWER_H
#define POWER_H

#include <avr/io.h>
#include <stdint.h>

#define ADC_CHANNEL_VOLTAGE		0 // ADC0
#define ADC_CHANNEL_CURRENT		1 // ADC1

#define isADCBusy()		((ADCSRA & (1 << ADSC)) > 0)

namespace Power
{
	bool readVoltage(uint16_t *voltage);
	bool readCurrent(uint16_t *current);
}

#endif

