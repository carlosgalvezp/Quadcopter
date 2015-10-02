#include "SoftPWM.h"


SoftPWM::SoftPWM()
{
}


SoftPWM::~SoftPWM()
{
}

SoftPWM::SoftPWM(uint8_t pin, unsigned long period_ms) :
pin_(pin),
high_time_us_(period_ms * 1000 / 2),
period_us_(period_ms * 1000),
duty_cycle_(50)
{
}

SoftPWM::SoftPWM(uint8_t pin, unsigned long high_time_ms, unsigned long period_ms) :
pin_(pin),
high_time_us_(high_time_ms*1000),
period_us_(period_ms*1000),
duty_cycle_(100*high_time_ms/period_ms)
{
}

void SoftPWM::init()
{
	// Init variables
	t_start_ = micros();
	outHigh_ = false;
	doChange_ = false;

	// Set pin as output
	pinMode(pin_, OUTPUT);
}

void SoftPWM::setParameters(unsigned long high_time_ms, unsigned long period_ms)
{
	this->high_time_us_ = high_time_ms * 1000;
	this->period_us_ = period_ms * 1000;
	this->t_start_ = micros();
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
		Serial.println("ASD");
		digitalWrite(A6, outHigh_);
		doChange_ = false;
	}
}

void SoftPWM::setPeriod(unsigned long period_ms)
{
	// The duty cycle is kept constant
	this->period_us_ = period_ms * 1000;
	this->high_time_us_ = this->period_us_ * this->duty_cycle_ / 100;
}