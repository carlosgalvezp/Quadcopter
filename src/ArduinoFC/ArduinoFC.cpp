#include "ArduinoFC.h"

unsigned long t1, t2;
State_data_t state_;

void setup() 
{
	// Init hardware
	HAL::init();
}

void loop() 
{
	//Test::testRC();
	//Test::testCompass();
	//Test::testSensorRead();
	//Test::testStateEstimation();
	//Test::testTelemetry(&state_);
	//Test::testOutput();
	Test::testWholeSystem(&state_);
	//delayMicroseconds(CYCLE_TIME_US);
	//delay(500);
}
