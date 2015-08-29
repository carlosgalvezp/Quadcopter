#include "ArduinoFC.h"

unsigned long t1, t2;


void setup() 
{
	Serial.begin(SERIAL0_BAUDRATE);

	HAL::init();
	RC::init();
}

void loop() 
{
	//Test::testCompass();
	//Test::testSensorRead();
	//Test::testStateEstimation();
	Test::testTelemetry();
	delay(100);
}

