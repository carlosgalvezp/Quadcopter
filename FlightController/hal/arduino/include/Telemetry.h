#ifndef TELEMETRY_H
#define TELEMETRY_H

#include "Arduino.h"
#include "Telemetry_Protocol.h"
#include "Config.h"
#include "HAL.h"

#define TELEMETRY_RX_BUFFER_SIZE 100

#define write8(data) Serial_Telemetry.write(data); checksum_ ^= data;

namespace Telemetry
{
	void main(const State& state, Config& config);

	void sendStatus(const State& data);

	void sendIMU(const State& data);
	void sendMagnetometer(const State& data);
	void sendBarometer(const State& data);
	void sendTemperature(const State& data);
	void sendRC(const State& data);
	void sendGPS(const State& data);
	void sendSonar(const State& data);

	void sendAttitude(const State& data);
	void sendControl(const State& data);
	void sendConfig(const Config& data);

	void sendACK();

	void receiveConfig(Config& config);

	void sendCheckSum();

	void write16(uint16_t data);
	void write32(uint32_t data);
	void writeFloat(float data);

	uint16_t read16(uint8_t ptr);
	uint32_t read32(uint8_t ptr);
	float readFloat(uint8_t ptr);
}
#endif
