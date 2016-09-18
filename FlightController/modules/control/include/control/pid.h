#ifndef PID_H
#define PID_H

#include "Arduino.h"
class PID
{
public:
	PID();
	~PID();

	float computeU(float x, float reference);
	void setParameters(float kp_, float kd_, float ki_);

private:
	unsigned long last_t_;
	float kp_, kd_, ki_;
	float last_e, e_sum;
	float delta_t_;
	float u;
};


#endif
