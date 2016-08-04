#include "HAL.h"

void HAL::init()
{
	// Init RC
	HAL::initRC();

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
			
	// Init Sonar
	HAL::initSonar();

	// Init ADC to read voltage and current
	HAL::initADC();

	// Init GPIO
	GPIO::init();

	// Init Serial ports
	Serial_Telemetry.begin(TELEMETRY_BAUDRATE);
	Serial_Debug.begin(TELEMETRY_BAUDRATE);

	// Init GPS
	GPS::init();

	// Enable interrupts globally
	SREG |= (1 << 7);
}

void HAL::initRC()
{
	// ** RX pins as inputs, with pull-up resistors
	DDRK = 0x00;	// Port K as input
	PORTK = 0xFF;   // Pull-up resistors enabled

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

	DDRH |= (1 << PIN_M4);


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

void HAL::initSonar()
{
	// Disable power reduction for Timer 1
	PRR0 &= ~(1 << PRTIM1);

	// Set trigger pin as output, echo as input
	DDRB &= ~(1 << PIN_SONAR_ECHO);		// Echo as input
	PORTB |= (1 << PIN_SONAR_ECHO);		// Enable pull-up for echo pin
	DDRB |= (1 << PIN_SONAR_TRIGGER);	// Trigger as output
		
	// --- Configure Timer 1-A for PWM signal ---
	// Non-inverted output, TOP = ICRn
	TCCR1A = 0b10000010;
	TCCR1B = 0b00011011;

	// Set TOP value to ICR1 to generate correct SONAR_FREQUENCY
	ICR1 = CPU_FREQUENCY / (SONAR_CLOCK_PRESCALER * SONAR_FREQUENCY) - 1;

	// Set OCR1A to generate correct pulse width
	OCR1A = (SONAR_T_TRIGGER_HIGH_US) / (1000000L/(CPU_FREQUENCY / SONAR_CLOCK_PRESCALER));

	// Enable interrupts PCIE0, since the sonar echo pin is connected to PCINT4
	PCICR |= (1 << PCIE0);

	// Enable INT4 within PCIE0
	PCMSK0 = (1 << SONAR_INT_NUMBER);

	// Enable interrupt for Output Compare in Timer 1-A
	TIMSK1 |= (1 << OCIE1A);
}

void HAL::initADC()
{
	// Disable power reduction for ADC
	PRR0 &= ~(1 << PRADC);

	// Select AVCC as source
	ADMUX = (1 << REFS0);

	// Enable ADC, NO Auto-Trigger, Prescaler=128 to keep ADC clock between 50 and 200 kHz, 
	// Enable ADC interrupt. 
	ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADIE) | 
		    (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

void HAL::boardLEDs(bool r, bool g, bool b)
{
	digitalWrite(PIN_LED_RED,   r);
	digitalWrite(PIN_LED_GREEN, g);
	digitalWrite(PIN_LED_BLUE,  b);
}