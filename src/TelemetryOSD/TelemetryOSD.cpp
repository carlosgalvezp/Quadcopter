#include "TelemetryOSD.h"


void setup() {
	Serial.begin(115200);
	pinMode(PIN_MAX7456_SS, OUTPUT);
	digitalWrite(PIN_MAX7456_SS, HIGH);

	SPI::init();
}

void loop() {
	// put your main code here, to run repeatedly:
	Test::testReadStatus();

	delay(1000);

	// ** Request data update

	// ** Read serial port

	// ** Update corresponding field in screen
}

