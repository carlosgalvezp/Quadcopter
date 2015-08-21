#include "HAL.h"

void HAL::init()
{
	// Enable interrupts globally
	SREG |= (1 << 7);

	// Init GPIO
	HAL::initGPIO();

	// Init I2C
	I2C::init();

	// Init IMU
	if (IMU::init())	Serial.println("Failed to init IMU");

	// Init Magnetometer
	if (Magnetometer::init())	Serial.println("Failed to init Magnetometer");

	// Init Barometer
	if (Barometer::init())	Serial.println("Failed to init Barometer");
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
	PCICR |= (1 << PCIE2);

	// Enable all pin interrupts within PCIE2
	PCMSK2 = 0xFF;
}