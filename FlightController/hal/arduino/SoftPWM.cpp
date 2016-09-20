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
    init(period_ms, highTime_ms);
}

void SoftPWM::init(unsigned long period_ms, unsigned long highTime_ms)
{
    period_us_ = period_ms * 1000;
    high_time_us_ = highTime_ms * 1000;
    duty_cycle_ = 100 * period_ms / highTime_ms;
    t_start_ = micros();
    out_high_ = false;
    do_change_ = false;
}

void SoftPWM::setParameters(unsigned long period_ms, unsigned long high_time_ms)
{
    period_us_ = period_ms * 1000;
    high_time_us_ = high_time_ms == 0 ? period_us_ / 2 : high_time_ms * 1000;
    t_start_ = micros();
    out_high_ = false;
    do_change_ = false;
}

void SoftPWM::run()
{
    if (!out_high_) // Current output = low level
	{
        if ((micros() - t_start_) > period_us_) // New cycle
		{
            out_high_ = true;
            do_change_ = true;
            t_start_ = micros();
		}
	}
	else	// Current output = high level
	{
        if ((micros() - t_start_) > high_time_us_)
		{
            out_high_ = false;
            do_change_ = true;
		}
	}

	// Toggle output if required
    if (do_change_)
	{	
        digital_pin_.setState(out_high_);
        do_change_ = false;
	}
}

void SoftPWM::setPeriod(unsigned long period_ms)
{
	// The duty cycle is kept constant
    period_us_ = period_ms * 1000;
    high_time_us_ = period_us_ * duty_cycle_ / 100;
}
