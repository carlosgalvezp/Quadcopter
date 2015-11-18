#pragma once
#ifndef OSD_H
#define OSD_H

class OSD
{
public:
	OSD();
	~OSD();

	void displayStaticData();
	void displayStatus();
	void displayGPS();
	void displayArtificialHorizon();

private:

};

#endif // OSD_H