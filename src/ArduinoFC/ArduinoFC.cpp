#include "ArduinoFC.h"

RCReadings_t rc_;

void setup() 
{
	HAL::init();
	RC::init();

	Serial.begin(115200);
}

void loop() 
{
	// Get readings
	RC::getReadings(&rc_);

	// Print
	String s = "Throttle: " + String(rc_.throttle) +
		" Aileron: " + String(rc_.aileron) +
		" Elevator: " + String(rc_.elevator) +
		" Rudder: " + String(rc_.rudder) +
		" AUX1: " + String(rc_.aux1) +
		" AUX2: " + String(rc_.aux2);

	Serial.println(s);

	//// Sleep until next iteration
	delay(100);
}

