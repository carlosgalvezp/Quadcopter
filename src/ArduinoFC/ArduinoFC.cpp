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
	//Test::run();
	MainLoop::run();	
}