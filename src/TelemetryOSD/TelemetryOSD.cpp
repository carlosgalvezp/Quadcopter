#include "TelemetryOSD.h"


void setup() 
{
	Serial.begin(115200);
	SPI::init();
}

void loop() 
{
	//Test::testReadCharacter();
	Test::testDisplayText();

	// ** Request data update

	// ** Read serial port

	// ** Update corresponding field in screen
}

