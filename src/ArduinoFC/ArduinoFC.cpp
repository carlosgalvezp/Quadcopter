#include "ArduinoFC.h"

unsigned long cycleTime;

void setup() 
{
	// Init hardware
	HAL::init();

	// Load configuration
	EEPROM::loadConfig(GlobalVariables::getConfig());
}

void loop() 
{
	//cycleTime = Utils::timeFunction(&MainLoop::run);
	cycleTime = Utils::timeFunction(&Test::run);

	if (cycleTime < CYCLE_TIME_US)
	{
		delayMicroseconds(CYCLE_TIME_US - cycleTime);
	}
}