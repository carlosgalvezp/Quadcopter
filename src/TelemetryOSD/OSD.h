#pragma once
#ifndef OSD_H
#define OSD_H

#include "MAX7456.h"
#include <stdio.h>

#define OSD_POS_BAT_V_X 1
#define OSD_POS_BAT_V_Y (SCREEN_SIZE_ROWS - 3)

#define OSD_POS_BAT_I_X  OSD_POS_BAT_V_X
#define OSD_POS_BAT_I_Y (OSD_POS_BAT_V_Y + 1)

class OSD
{
public:
	OSD();
	~OSD();

	void init();
	void enable();

	void displayStaticData();
	void displayStatus();
	void displayGPS();
	void displayArtificialHorizon();

	inline MAX7456& getDriver(){ return this->osdDriver_; };
	void print(uint8_t rowStart, uint8_t colStart, const char *format, ...);

private:
	MAX7456 osdDriver_;
};

#endif // OSD_H