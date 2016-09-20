#include "control/pid.h"

PID::PID() :
last_t_(0),
last_e(0),
e_sum(0),
delta_t_(0)
{
}


PID::~PID()
{
}

void PID::setParameters(float kp, float kd, float ki)
{
    kp_ = kp;
    kd_ = kd;
    ki_ = ki;
}

float PID::computeU(float x, float reference)
{
	// Update cycle time
    if (last_t_ == 0)
	{
        last_t_ = micros();
		return 0;
	}
    delta_t_ = micros() - last_t_;
    last_t_ = micros();

	// Compute error
	float e = reference - x;

	// Compute PID commands
    u = kp_ * e + (e - last_e) / delta_t_ + e_sum * delta_t_;

	// Update e_sum, last_e
    last_e = e;
    e_sum += e;

	// TO-DO: include anti-wind up

	// Return control signal
	return u;
}
