#include "HAL.h"

void HAL::init()
{
	// Init GPIO
	HAL::initGPIO();

	// Init motors
	HAL::initMotors();

	// Init I2C
	I2C::init();

	// Init IMU
	if (IMU::init())	Serial.println("Failed to init IMU");

	// Init Magnetometer
	if (Magnetometer::init())	Serial.println("Failed to init Magnetometer");

	// Init Barometer
	if (Barometer::init())	Serial.println("Failed to init Barometer");

	// Init RC
	HAL::initRC();

	// Enable interrupts globally
	SREG |= (1 << 7);
}

void HAL::initGPIO()
{
	// ** RX pins as inputs, with pull-up resistors
	DDRK  = 0x00;	// Port K as input
	PORTK = 0xFF;   // Pull-up resistors enabled
}
void HAL::initRC()
{
	// Enable interrupts PCIE2, since the RC channels are connected
	// to PCINT 16:23
	PCICR |= (1 << PCIE2);

	// Enable all pin interrupts within PCIE2
	PCMSK2 = 0xFF;
}

void HAL::initMotors()
{
	// Disable power reduction for timers
	PRR1 &= ~((1 << PRTIM3) | (1 << PRTIM4));

	// Init pins as output
	DDRE |= (1 << PIN_M1) | 
			(1 << PIN_M2) |
			(1 << PIN_M3);

	DDRH |= (1 << PIN_M4) |
			(1 << PIN_M5) |
			(1 << PIN_M6) |
			(1 << PIN_M7);

	DDRB |= (1 << PIN_M8);

	// --- Configure Timers 3 and 4 ---
	// Non-inverted output, TOP = ICRn
	TCCR3A = 0b10101000; 
	TCCR4A = 0b10101000;

	// PWM Phase and Frequency Correct, f_timer = f_cpu (no prescaling)
	TCCR3B = 0b00010001; 
	TCCR4B = 0b00010001;

	// Set TOP value to ICRn to generate correct ESC_FREQUENCY
	ICR3 = CPU_FREQUENCY / (2 * ESC_FREQUENCY); 
	ICR4 = CPU_FREQUENCY / (2 * ESC_FREQUENCY);
}