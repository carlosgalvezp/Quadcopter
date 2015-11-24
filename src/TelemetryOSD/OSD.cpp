#include "OSD.h"


OSD::OSD()
{
}


OSD::~OSD()
{
}

void OSD::init()
{
	this->osdDriver_.init();
}

void OSD::displayStaticData()
{
}

void OSD::enable()
{
	this->osdDriver_.enableOSD();
}

void OSD::print(uint8_t rowStart, uint8_t colStart, const char *format, ...)
{
	// Get a string representation using snprintf - a safe sprintf
	char data[SCREEN_SIZE_COLS];
	va_list arguments;

	va_start(arguments, format); // Get the actual arguments by parsing the format and variable input
	snprintf(data, SCREEN_SIZE_COLS, format, arguments);	// Create the string
	va_end(arguments);										// Required when using va_start

	// Display characters
	uint8_t i = 0;
	uint8_t cData;
	while ( (i < SCREEN_SIZE_COLS) && ((cData = data[i++]) != '\0') )
	{
		this->osdDriver_.displayCharacter(rowStart, colStart++, cData);
	}
}