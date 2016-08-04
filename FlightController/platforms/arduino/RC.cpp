#include "RC.h"

namespace RC
{
	volatile unsigned long RC_last_t_rise[NUM_CHANNELS];
	volatile uint16_t RC_readings[NUM_CHANNELS];
	volatile uint16_t rcVal;
	uint8_t prevPortK;
}

void RC::getReadings(RC_data_t * const readings)
{
	readings->throttle = RC_readings[2];
	readings->aileron  = RC_readings[0];
	readings->elevator = RC_readings[1];
	readings->rudder   = RC_readings[3];
	readings->aux1     = RC_readings[4];
	readings->aux2     = RC_readings[5];
	readings->aux3     = RC_readings[6];
	readings->aux4     = RC_readings[7];
}

/* Interruption Service Routine for RX channels */
ISR(PCINT2_vect)
{
	// Identify which bit interrupted by XORing to previous one
	uint8_t pK = PINK;
	uint8_t diff = RC::prevPortK ^ pK;
	uint8_t bitNo = 0;
	diff >>= 1;
	while (diff > 0)
	{
		diff >>= 1;
		++bitNo;
	}
	
	// Update timers
	if (pK & (1 << bitNo)) // Rising edge
	{
		RC::RC_last_t_rise[bitNo] = micros();
	}
	else	// Falling edge
	{
		RC::rcVal = uint16_t(micros() - RC::RC_last_t_rise[bitNo]);
		if (RC_isValid(RC::rcVal))
		{
			RC::RC_readings[bitNo] = RC::rcVal;
		}
	}
	// Store current port K for the next iteration
	RC::prevPortK = pK;
}