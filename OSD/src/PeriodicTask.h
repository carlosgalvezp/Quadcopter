#pragma once
#ifndef PERIODIC_TASK_H
#define PERIODIC_TASK_H

#include "Arduino.h"

typedef void(*callbackFunction_t)(void);

class PeriodicTask
{
public:
	PeriodicTask(unsigned long period_us, callbackFunction_t fCallback);
	~PeriodicTask();

	void run();

private:
	unsigned long period_us_, lastTime;
	callbackFunction_t fCallback_;
};

#endif

