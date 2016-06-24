#ifndef TELEMETRY_H
#define TELEMETRY_H

#include "Arduino.h"
#include "ArduinoFC_2.h"
#include "Telemetry_Protocol.h"
#include "Config.h"
#include "HAL.h"

#define TELEMETRY_RX_BUFFER_SIZE 100

#define write8(data) Serial_Telemetry.write(data); checksum_ ^= data;

namespace Telemetry
{
	void main(const State* const state, Config* const config);

	void sendStatus(const State* const data);

	void sendIMU(const State* const data);
	void sendMagnetometer(const State* const data);
	void sendBarometer(const State* const data);
	void sendTemperature(const State* const data);
	void sendRC(const State* const data);
	void sendGPS(const State* const data);
	void sendSonar(const State* const data);

	void sendAttitude(const State* const data);
	void sendControl(const State* const data);
	void sendConfig(const Config* const data);

	void sendACK();

	void receiveConfig(Config* const config);

	void sendCheckSum();

	void write16(uint16_t data);
	void write32(uint32_t data);
	void writeFloat(float data);

	uint16_t read16(uint8_t ptr);
	uint32_t read32(uint8_t ptr);
	float readFloat(uint8_t ptr);
}
#endif
