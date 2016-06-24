#include "SoftPWM.h"

SoftPWM::SoftPWM(GPIO_Digital& digital_pin)
	: SoftPWM(digital_pin, 0U, 0U)
{}

SoftPWM::SoftPWM(GPIO_Digital& digital_pin, unsigned long period_ms) 
	: SoftPWM(digital_pin, period_ms, period_ms / 2U)
{}

SoftPWM::SoftPWM(GPIO_Digital& digital_pin, unsigned long period_ms, unsigned long highTime_ms)
	: digital_pin_(digital_pin)
{
	this->init(period_ms, highTime_ms);
}

void SoftPWM::init(unsigned long period_ms, unsigned long highTime_ms)
{
	this->period_us_ = period_ms * 1000;
	this->high_time_us_ = highTime_ms * 1000;
	this->duty_cycle_ = 100 * period_ms / highTime_ms;
	this->t_start_ = micros();
	this->outHigh_ = false;
	this->doChange_ = false;
}

void SoftPWM::setParameters(unsigned long period_ms, unsigned long high_time_ms)
{
	this->period_us_ = period_ms * 1000;
	this->high_time_us_ = high_time_ms == 0? this->period_us_ / 2 : high_time_ms * 1000;	
	this->t_start_ = micros();
	this->outHigh_ = false;
	this->doChange_ = false;
}

void SoftPWM::run()
{
	if (!outHigh_) // Current output = low level
	{
		if ((micros() - this->t_start_) > this->period_us_) // New cycle
		{
			outHigh_ = true;
			doChange_ = true;
			this->t_start_ = micros();
		}
	}
	else	// Current output = high level
	{
		if ((micros() - this->t_start_) > this->high_time_us_)
		{
			outHigh_ = false;
			doChange_ = true;
		}
	}

	// Toggle output if required
	if (doChange_)
	{	
		this->digital_pin_.setState(outHigh_);
		doChange_ = false;
	}
}

void SoftPWM::setPeriod(unsigned long period_ms)
{
	// The duty cycle is kept constant
	this->period_us_ = period_ms * 1000;
	this->high_time_us_ = this->period_us_ * this->duty_cycle_ / 100;
}