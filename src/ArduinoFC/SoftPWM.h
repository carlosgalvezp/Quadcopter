#pragma once
#ifndef SOFTPWM_H
#define SOFTPWM_H

#include "Arduino.h"
#include <stdint.h>


// Used to generate PWM signals on digital pins, especially when no timers
// are available or the desired frequency is too low
class SoftPWM
{
public:
	SoftPWM();	
	SoftPWM(uint8_t pin, unsigned long period_ms);
	SoftPWM(uint8_t pin, unsigned long high_time_ms, unsigned long period_ms);
	~SoftPWM();

	void setPeriod(unsigned long period_ms);
	void setParameters(unsigned long high_time_ms, unsigned long period_ms);
	void init();
	void run();
private:
	uint8_t pin_;
	unsigned long high_time_us_;
	unsigned long period_us_;
	unsigned long t_start_;
	uint8_t duty_cycle_;
	bool outHigh_, doChange_;
};

#endif