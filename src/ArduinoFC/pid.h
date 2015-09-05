#ifndef PID_H
#define PID_H

#include "Arduino.h"
class PID
{
public:
	PID();
	~PID();

	float computeU(float x, float reference);
	void setParameters(float kp, float kd, float ki);

private:
	unsigned long last_t;
	float kp, kd, ki;
	float last_e, e_sum;
	float deltaT;
	float u;
};


#endif
