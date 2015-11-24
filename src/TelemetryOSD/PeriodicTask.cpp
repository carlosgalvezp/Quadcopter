#include "PeriodicTask.h"


PeriodicTask::PeriodicTask(unsigned long period_us, callbackFunction_t fCallback)
	: period_us_(period_us)
{
	this->fCallback_ = fCallback;
	lastTime = micros();
}


PeriodicTask::~PeriodicTask()
{
}

void PeriodicTask::run()
{
	if ((micros() - lastTime) > this->period_us_)
	{
		(*this->fCallback_)();
		lastTime = micros();
	}
}