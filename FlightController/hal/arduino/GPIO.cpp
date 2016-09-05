#include "GPIO.h"

namespace GPIO
{
	GPIO_Digital ledR(PIN_LED_RED, true);
	GPIO_Digital ledG(PIN_LED_GREEN, true);
	GPIO_Digital ledB(PIN_LED_BLUE, true);
	
	GPIO_Digital bodyLEDs(PIN_LEDS_BODY, true);
	GPIO_Digital buzzer(PIN_BUZZER, true);
}

GPIO_Digital::GPIO_Digital(uint8_t digitalPinNumber, bool isOutputPin)
{
	// ** Pre-compute output register for faster access
	this->bit = digitalPinToBitMask(digitalPinNumber);
	this->port = digitalPinToPort(digitalPinNumber);		
	this->outReg = portOutputRegister(this->port);

	// ** Configure pinmode
	if (isOutputPin)			pinMode(digitalPinNumber, OUTPUT);
	else						pinMode(digitalPinNumber, INPUT);

	// ** Create SoftPWM object, for blinking
	this->softPWM = new SoftPWM(*this);
}

void GPIO_Digital::setState(bool on)
{
	if (on)			*this->outReg &= ~this->bit;	
	else			*this->outReg |=  this->bit;
}

void GPIO_Digital::blink(uint16_t period_ms, uint16_t t_high_ms)
{
	if (this->period_ms_ != period_ms || this->t_high_ms_ != t_high_ms)
	{
		this->period_ms_ = period_ms;
		this->t_high_ms_ = t_high_ms;
		this->softPWM->setParameters(period_ms, t_high_ms);
	}

	this->softPWM->run();
}

void GPIO::init()
{
	// Init status LEDs
	pinMode(PIN_LED_GREEN, OUTPUT);
	pinMode(PIN_LED_RED, OUTPUT);
	pinMode(PIN_LED_BLUE, OUTPUT);
}

GPIO_Digital &GPIO::getBodyLEDs(){ return GPIO::bodyLEDs; }
GPIO_Digital &GPIO::getBuzzer()  { return GPIO::buzzer; }

GPIO_Digital &GPIO::getLedRed()  { return GPIO::ledR; }
GPIO_Digital &GPIO::getLedGreen(){ return GPIO::ledG; }
GPIO_Digital &GPIO::getLedBlue() { return GPIO::ledB; }