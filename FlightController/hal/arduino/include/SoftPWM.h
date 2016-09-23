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
	explicit SoftPWM(GPIO_Digital& digital_pin);
	SoftPWM(GPIO_Digital& digital_pin, unsigned long period_ms);
	SoftPWM(GPIO_Digital& digital_pin, unsigned long period_ms, unsigned long highTime_ms);

	void run();
	void run(unsigned long period_ms);
	void run(unsigned long period_ms, unsigned long highTime_ms);

	void setPeriod(unsigned long period_ms);
	void setParameters(unsigned long period_ms, unsigned long high_time_ms);
private:
	GPIO_Digital& digital_pin_;
	unsigned long high_time_us_;
	unsigned long period_us_;
	unsigned long t_start_;
	uint8_t duty_cycle_;
	bool out_high_, do_change_;

	void init(unsigned long period_ms, unsigned long highTime_ms);
};

#endif
