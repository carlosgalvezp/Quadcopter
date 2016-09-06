#include "control/pid.h"

PID::PID() :
last_t(0),
last_e(0),
e_sum(0),
deltaT(0)
{
}


PID::~PID()
{
}

void PID::setParameters(float kp, float kd, float ki)
{
	this->kp = kp;
	this->kd = kd;
	this->ki = ki;
}

float PID::computeU(float x, float reference)
{
	// Update cycle time
	if (this->last_t == 0)
	{
		this->last_t = micros();
		return 0;
	}
	this->deltaT = micros() - this->last_t;
	this->last_t = micros();

	// Compute error
	float e = reference - x;

	// Compute PID commands
	u = kp * e + (e - last_e) / this->deltaT + this->e_sum * deltaT;

	// Update e_sum, last_e
	this->last_e = e;
	this->e_sum += e;

	// TO-DO: include anti-wind up

	// Return control signal
	return u;
}
