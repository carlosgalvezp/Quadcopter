#include "Telemetry.h"

namespace Telemetry
{
	uint8_t i = 0;
	void sendData()
	{
		Serial.write(i++);
	}
}
