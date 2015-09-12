#include "ArduinoFC.h"

unsigned long t1, t2;


void setup() 
{
	Serial.begin(SERIAL0_BAUDRATE);

	HAL::init();
}

void loop() 
{
	//Test::testRC();
	//Test::testCompass();
	//Test::testSensorRead();
	//Test::testStateEstimation();
	Test::testTelemetry();
	//Test::testOutput();
	delayMicroseconds(CYCLE_TIME_US);
}

