#include "OSD.h"


OSD::OSD()
{
}


OSD::~OSD()
{
}

void OSD::displayStaticData()
{
	osdDriver_.displayCharacter(2, 2, CHAR_ADDR_H_BIG);
	osdDriver_.displayCharacter(2, 3, CHAR_ADDR_E_BIG);
	osdDriver_.displayCharacter(2, 4, CHAR_ADDR_L_BIG);
	osdDriver_.displayCharacter(2, 5, CHAR_ADDR_L_BIG);
	osdDriver_.displayCharacter(2, 6, CHAR_ADDR_O_BIG);

	osdDriver_.displayCharacter(2, 8, CHAR_ADDR_W_BIG);
	osdDriver_.displayCharacter(2, 9, CHAR_ADDR_O_BIG);
	osdDriver_.displayCharacter(2, 10, CHAR_ADDR_R_BIG);
	osdDriver_.displayCharacter(2, 11, CHAR_ADDR_L_BIG);
	osdDriver_.displayCharacter(2, 12, CHAR_ADDR_D_BIG);
}

void OSD::displayFloat(float val, uint8_t digitsBeforeComma, uint8_t digitsAfterComma, uint8_t x, uint8_t y)
{
	//// Check sign
	//bool isPositive = val > 0;

	//// Extract digits before comma
	//uint8_t nDigitsBeforeComma = 0;
	//while (val >= 1.0f)
	//{

	//}
}

void OSD::enable()
{
	this->osdDriver_.enableOSD();
}