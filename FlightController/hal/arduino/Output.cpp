#include "Output.h"

void Output::writePWM(const uint16_t * const pwm_us)
{
	PWM_WRITE(OUT_M1, pwm_us[0]);
	PWM_WRITE(OUT_M2, pwm_us[1]);
	PWM_WRITE(OUT_M3, pwm_us[2]);
	PWM_WRITE(OUT_M4, pwm_us[3]);
}
