#include "ArduinoFC.h"

unsigned long cycleTime;

void setup() 
{
	// Init hardware
	HAL::init();

	// Load configuration
	EEPROM::loadConfig(GlobalVariables::getConfig());

	// Init global variables
	GlobalVariables::init();
}

void loop() 
{
	cycleTime = Utils::timeFunction(&MainLoop::run);
	//cycleTime = Utils::timeFunction(&Test::run);

	if (cycleTime < CYCLE_TIME_US)
	{
		delayMicroseconds(CYCLE_TIME_US - cycleTime);
	}
}