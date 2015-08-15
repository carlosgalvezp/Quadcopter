#include "HAL.h"

void HAL::init()
{
	// Enable interrupts globally
	SREG |= (1 << 7);

	// Init GPIO
	HAL::initGPIO();
}

void HAL::initGPIO()
{
	// ** RX pins as inputs, with pull-up resistors
	DDRK  = 0x00;	// Port K as input
	PORTK = 0xFF;   // Pull-up resistors enabled
}
void HAL::initRCInterrupts()
{
	// Enable interrupts PCIE2, since the RC channels are connected
	// to PCINT 16:23
	PCICR |= (1 << 2);

	// Enable all pin interrupts within PCIE2
	PCMSK2 = 0xFF;
}