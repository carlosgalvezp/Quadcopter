#include "TelemetryOSD.h"

OSD osd_;
TaskManager taskManager_;

void setup() 
{
	Serial.begin(115200);
	SPI::init();
	osd_.init();
}

void loop() 
{
	//Test::main(osd_);
	taskManager_.runTasks();

	// ** Request data update

	// ** Read serial port

	// ** Update corresponding field in screen
}

