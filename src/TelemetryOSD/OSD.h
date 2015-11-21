#pragma once
#ifndef OSD_H
#define OSD_H

#include "MAX7456.h"

#define OSD_POS_BAT_V_X 1
#define OSD_POS_BAT_V_Y (SCREEN_SIZE_ROWS - 3)

#define OSD_POS_BAT_I_X  OSD_POS_BAT_V_X
#define OSD_POS_BAT_I_Y (OSD_POS_BAT_V_Y + 1)

class OSD
{
public:
	OSD();
	~OSD();

	void enable();

	void displayStaticData();
	void displayStatus();
	void displayGPS();
	void displayArtificialHorizon();

private:
	MAX7456 osdDriver_;

	void displayFloat(float val, uint8_t digitsBeforeComma, uint8_t digitsAfterComma, uint8_t x, uint8_t y);
};

#endif // OSD_H