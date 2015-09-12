#ifndef TELEMETRY_H
#define TELEMETRY_H

#include "Arduino.h"
#include "ArduinoFC.h"
#include "Telemetry_Protocol.h"

#define TELEMETRY_RX_BUFFER_SIZE 50

namespace Telemetry
{
	void sendData(const State_data_t * const data);

	void sendStatus(const State_data_t * const data);

	void sendIMU(const State_data_t * const data);
	void sendMagnetometer(const State_data_t * const data);
	void sendBarometer(const State_data_t * const data);
	void sendTemperature(const State_data_t * const data);
	void sendRC(const State_data_t * const data);
	void sendBattery(const State_data_t * const data);
	void sendGPS(const State_data_t * const data);
	void sendSonar(const State_data_t * const data);

	void sendAttitude(const State_data_t * const data);
	void sendControl(const State_data_t * const data);

	void receivePID(Config_t * const data);

	void write8(uint8_t data);
	void write16(uint16_t data);
	void write32(uint32_t data);
}
#endif
