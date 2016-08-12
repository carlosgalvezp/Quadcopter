#ifndef OUTPUT_H
#define OUTPUT_H

#include "HAL.h"

#define PWM_WRITE(reg, us) reg=us<<3 // Multiply by 8, since 1000 us = 8000 clock ticks

namespace Output
{
	void writePWM(const uint16_t * const pwm_us);
}
#endif