#pragma once
#ifndef SOFTPWM_H
#define SOFTPWM_H

#include "Arduino.h"
#include <stdint.h>
#include "GPIO.h"

// Used to generate PWM signals on digital pins, especially when no timers
// are available or the desired frequency is too low
class GPIO_Digital;

class SoftPWM
{
public:
	SoftPWM();	
	SoftPWM(GPIO_Digital *digitalPin);
	SoftPWM(GPIO_Digital *digitalPin, unsigned long period_ms);
	SoftPWM(GPIO_Digital *digitalPin, unsigned long period_ms, unsigned long highTime_ms);
	~SoftPWM();

	void run();
	void run(unsigned long period_ms);
	void run(unsigned long period_ms, unsigned long highTime_ms);

	void setPeriod(unsigned long period_ms);
	void setParameters(unsigned long period_ms, unsigned long high_time_ms);
private:
	GPIO_Digital *digitalPin;
	unsigned long high_time_us_;
	unsigned long period_us_;
	unsigned long t_start_;
	uint8_t duty_cycle_;
	bool outHigh_, doChange_;

	void init(GPIO_Digital *digitalPin, unsigned long period_ms, unsigned long highTime_ms);
};

#endif