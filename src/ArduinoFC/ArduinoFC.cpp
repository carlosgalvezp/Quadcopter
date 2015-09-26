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
	Test::testSonar();
	//Test::testStateEstimation();
	//Test::testTelemetry(&state_);
	//Test::testOutput();
	//Test::testWholeSystem(&state_);
	//Test::Unit::testAtan2();
	//Test::Unit::testAtan2Full();
	//Test::Unit::testQuaternionToRPY();
	//delay(500);
}
