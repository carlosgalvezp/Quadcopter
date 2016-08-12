#include "Test.h"

void Test::main(OSD &osd)
{
	Test::Internal::testReadCharacter(osd);
	//Test::Internal::testDisplayText(osd);
}

void Test::Internal::testReadStatus()
{
	// Activate OSD
	Serial.println("Sending data...");
	digitalWrite(PIN_MAX7456_SS, LOW);
	
	// Transfer byte
	SPI::writeByte(STAT_R);
	uint8_t stat = SPI::readByte();
		
	// Disable OSD
	digitalWrite(PIN_MAX7456_SS, HIGH);

	// Print
	Serial.println(stat);

	delay(1000);
}

void Test::Internal::testReadCharacter(OSD &osd)
{
	MAX7456& osdDriver = osd.getDriver();
	uint8_t charAddr;
	uint8_t charData[OSD_CHAR_SIZE_BYTES];

	for (uint8_t i = 0; i < NVM_SIZE; ++i)
	{
		charAddr = i;

		Serial.print("Reading character "); Serial.print(i); Serial.println("...");
		
		osdDriver.readSymbolFromNVM(charAddr, charData);
		Test::Internal::displayOSDSymbol(charData);

		delay(2000);
	}
}

void Test::Internal::testDisplayText(OSD &osd)
{		
	uint8_t x0 = 5;
	uint8_t y0 = 10;

	//osdDriver.displayCharacter(x0++, y0, CHAR_ADDR_D_BIG);
	//osdDriver.displayCharacter(x0++, y0, CHAR_ADDR_O_BIG);
	//osdDriver.displayCharacter(x0++, y0, CHAR_ADDR_N_BIG);
	//osdDriver.displayCharacter(x0++, y0, 39);
	//osdDriver.displayCharacter(x0++, y0, CHAR_ADDR_T_BIG);
	//
	//osdDriver.displayCharacter(x0++, y0, CHAR_ADDR_EMPTY);

	//osdDriver.displayCharacter(x0++, y0, CHAR_ADDR_J_BIG);
	//osdDriver.displayCharacter(x0++, y0, CHAR_ADDR_U_BIG);
	//osdDriver.displayCharacter(x0++, y0, CHAR_ADDR_D_BIG);
	//osdDriver.displayCharacter(x0++, y0, CHAR_ADDR_G_BIG);
	//osdDriver.displayCharacter(x0++, y0, CHAR_ADDR_E_BIG);

	//osdDriver.displayCharacter(x0++, y0, CHAR_ADDR_EMPTY);

	//osdDriver.displayCharacter(x0++, y0, CHAR_ADDR_M_BIG);
	//osdDriver.displayCharacter(x0++, y0, CHAR_ADDR_E_BIG);

	//osdDriver.displayCharacter(x0++, y0, CHAR_ADDR_C_BIG);
	//osdDriver.displayCharacter(x0++, y0, CHAR_ADDR_A_BIG);
	//osdDriver.displayCharacter(x0++, y0, CHAR_ADDR_L_BIG);
	//osdDriver.displayCharacter(x0++, y0, CHAR_ADDR_I_BIG);

	//osdDriver.displayCharacter(x0++, y0, CHAR_ADDR_EMPTY);

	//osdDriver.displayCharacter(x0++, y0, CHAR_ADDR_C_BIG);
	//osdDriver.displayCharacter(x0++, y0, CHAR_ADDR_A_BIG);
	//osdDriver.displayCharacter(x0++, y0, CHAR_ADDR_L_BIG);
	//osdDriver.displayCharacter(x0++, y0, CHAR_ADDR_I_BIG);

	//osdDriver.displayCharacter(x0++, y0, CHAR_ADDR_EMPTY);

	//osdDriver.displayCharacter(x0++, y0, CHAR_ADDR_C_BIG);
	//osdDriver.displayCharacter(x0++, y0, CHAR_ADDR_O_BIG);
	//osdDriver.displayCharacter(x0++, y0, CHAR_ADDR_O_BIG);
	//osdDriver.displayCharacter(x0++, y0, CHAR_ADDR_P_BIG);
	//osdDriver.displayCharacter(x0++, y0, CHAR_ADDR_O_BIG);
	//osdDriver.displayCharacter(x0++, y0, CHAR_ADDR_N_BIG);

	osd.print(x0, y0, "GITAANO");
	delay(1000);	
}

void Test::Internal::displayOSDSymbol(const uint8_t *data)
{
	uint8_t mask = 0b00000011; // Used to read the value of a single pixel
	for (uint8_t j = 0; j < CHARACTER_SIZE_H; ++j)
	{
		for (uint8_t i = 0; i < 3; ++i)
		{
			uint8_t pixelData = data[j * 3 + i];
			for (uint8_t k = 0; k < 4; ++k)
			{
				uint8_t displacement = (3 - k) * 2;

				uint8_t val = ((pixelData & (mask << displacement)) >> displacement) & mask;
				if (val == 0)					// Black
					Serial.print('_');
				else if (val == 2)				// White
					Serial.print('*');
				else if (val == 1 || val == 3)	// Gray
					Serial.print('-');

			}
		}
		Serial.println();
	}
}