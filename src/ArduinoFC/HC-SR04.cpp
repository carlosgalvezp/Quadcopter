#include "HC-SR04.h"

bool sentTrigger(false);
bool measurementReady(false);
unsigned long tTrigger(0);
unsigned long tEcho(0);
float distance_(0);
uint8_t prevPortB(0);

bool Sonar::getDistance(float *distance)
{
	if (measurementReady)
	{
		*distance = distance_;
		return true;
	}
	return false;
}

ISR(PCINT0_vect) 
{
	// Identify which bit interrupted by XORing to previous one
	uint8_t currentPortB = PINB;
	uint8_t diff = prevPortB ^ currentPortB;
	uint8_t bitNo = 0;
	diff >>= 1;
	while (diff > 0)
	{
		diff >>= 1;
		++bitNo;
	}

	if (sentTrigger && bitNo == SONAR_INT_NUMBER)
	{
		// Read current value
		bool val = (currentPortB & (1 << bitNo)) > 0;
		
		// Update timers
		if (val) // Rising edge
		{
			tEcho = micros();
		}
		else	// Falling edge
		{
			distance_ = 0.5f * SOUND_SPEED_CM_US * (micros() - tEcho);
			measurementReady = true;
			sentTrigger = false; 
		}
	}
	// Store current port K for the next iteration
	prevPortB = currentPortB;
}

// This is executed whenever we finish sending the trigger
ISR(TIMER1_COMPA_vect)
{
	sentTrigger = true;
}