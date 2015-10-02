#pragma once
#ifndef GPIO_H
#define GPIO_H

#include "HAL.h"
#include "SoftPWM.h"

namespace GPIO
{
	void init();

	void runBodyLEDs();
	void runBuzzer();

	SoftPWM &getBodyLEDs();
	SoftPWM &getBuzzer();
}

#endif