#include "GPIO.h"


namespace GPIO
{
	SoftPWM bodyLEDs(PIN_LEDS_BODY, 1000);
	SoftPWM buzzer(PIN_BUZZER, 1000);
}

void GPIO::init()
{
	bodyLEDs.init();
	buzzer.init();
}

SoftPWM &GPIO::getBodyLEDs(){ return bodyLEDs; }
SoftPWM &GPIO::getBuzzer(){ return buzzer; }