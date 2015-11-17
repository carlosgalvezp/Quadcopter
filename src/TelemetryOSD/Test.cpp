#include "Test.h"

void Test::testReadStatus()
{
	// Activate OSD
	Serial.println("Sending data...");
	digitalWrite(PIN_MAX7456_SS, LOW);
	
	// Transfer byte
	SPI::transferByte(STAT_R);
	uint8_t stat = SPI::transferByte(0xFF);
		
	// Disable OSD
	digitalWrite(PIN_MAX7456_SS, HIGH);

	// Print
	Serial.println(stat);
}