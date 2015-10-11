#include "GPIO.h"


namespace GPIO
{
	SoftPWM bodyLEDs(PIN_LEDS_BODY, 1000);
	SoftPWM buzzer(PIN_BUZZER, 1000);
}

void GPIO::init()
{
	// Init status LEDs
	pinMode(PIN_LED_GREEN, OUTPUT);
	pinMode(PIN_LED_RED, OUTPUT);
	pinMode(PIN_LED_BLUE, OUTPUT);

	// Init Body LEDs and buzzer
	bodyLEDs.init();
	buzzer.init();
}

SoftPWM &GPIO::getBodyLEDs(){ return bodyLEDs; }
SoftPWM &GPIO::getBuzzer(){ return buzzer; }