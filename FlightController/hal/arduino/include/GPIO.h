#pragma once
#ifndef GPIO_H
#define GPIO_H

#include "Arduino.h"
#include "HAL.h"
#include "SoftPWM.h"

class SoftPWM;
class GPIO_Digital
{
public:
	GPIO_Digital(uint8_t digitalPinNumber, bool isOutputPin);

	void setState(bool on);
	void blink(uint16_t period_ms, uint16_t t_high_ms = 0);
private:
	uint8_t	port_, bit_;
	volatile uint8_t *out_reg_;
	uint16_t period_ms_, t_high_ms_;
	SoftPWM *soft_pwm_;
};

namespace GPIO
{
	void init();

	void runBodyLEDs();
	void runBuzzer();

	GPIO_Digital &getLedRed();
	GPIO_Digital &getLedGreen();
	GPIO_Digital &getLedBlue();

	GPIO_Digital &getBodyLEDs();
	GPIO_Digital &getBuzzer();
}

#endif