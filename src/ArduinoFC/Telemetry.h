#ifndef TELEMETRY_H
#define TELEMETRY_H

#include "Arduino.h"
#include "ArduinoFC.h"

// ** COMMANDS **
#define TELEMETRY_CMD_STATUS			0
#define TELEMETRY_CMD_IMU				1
#define TELEMETRY_CMD_ATTITUDE			2

namespace Telemetry
{
	void sendData(const Telemetry_data_t * const data);

	void sendIMU();
	void sendAttitude(const quaternion_t * const q);

	void write8(int8_t data);
	void write16(int16_t data);
}
#endif
