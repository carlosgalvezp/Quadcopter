#ifndef TELEMETRY_H
#define TELEMETRY_H

#include "Arduino.h"
#include "ArduinoFC.h"

// ** COMMANDS **
#define TELEMETRY_CMD_STATUS	0
#define TELEMETRY_CMD_IMU		1
#define TELEMETRY_CMD_POSE		2

namespace Telemetry
{
	void sendData(const Telemetry_data_t * const data);

	void sendIMU();

	void write8(uint8_t data);
	void write16(uint16_t data);
}
#endif
