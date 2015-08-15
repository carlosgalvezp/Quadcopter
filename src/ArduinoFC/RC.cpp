#include "RC.h"

volatile unsigned long RC_times[NUM_CHANNELS];
volatile RCReadings_t rc_readings;
volatile uint8_t prevPortK;

void RC::init()
{
	HAL::initRCInterrupts();
}

void RC::getReadings(RCReadings_t * const readings)
{
	readings->throttle = rc_readings.throttle;
	readings->aileron  = rc_readings.aileron;
	readings->elevator = rc_readings.elevator;
	readings->rudder = rc_readings.rudder;
	readings->aux1 = rc_readings.aux1;
	readings->aux2 = rc_readings.aux2;
	readings->aux3 = rc_readings.aux3;
	readings->aux4 = rc_readings.aux4;
}

/* Interruption Service Routine for RX channels */
ISR(PCINT2_vect)
{
	// Identify which bit interrupted by XORing to previous one
	uint8_t pK = PINK;
	uint8_t diff = prevPortK ^ pK;
	uint8_t bitNo = 0;
	diff >>= 1;
	while (diff > 0)
	{
		diff >>= 1;
		++bitNo;
	}

	// Read current value
	bool val = (pK & (1 << bitNo)) > 0;

	// Update timers
	if (val) // Rising edge
	{
		RC_times[bitNo] = micros();
	}
	else	// Falling edge
	{
		unsigned long pulseWidth = micros() - RC_times[bitNo];
		switch (bitNo)
		{
			case 0: // Throttle
				rc_readings.throttle = pulseWidth;
				break;
			case 1: // Aileron
				rc_readings.aileron  = pulseWidth;
				break;
			case 2: // Elevator
				rc_readings.elevator = pulseWidth;
				break;
			case 3: // Rudder
				rc_readings.rudder   = pulseWidth;
				break;
			case 4: // AUX1
				rc_readings.aux1     = pulseWidth;
				break;
			case 5: // AUX2
				rc_readings.aux2	 = pulseWidth;
				break;
			case 6: // AUX3
				rc_readings.aux3	 = pulseWidth;
				break;
			case 7: // AUX4
				rc_readings.aux4	 = pulseWidth;
				break;
		}
	}

	// Store current port K for the next iteration
	prevPortK = pK;
}