#include "Telemetry.h"

namespace Telemetry
{
	uint8_t cmd_ = TELEMETRY_CMD_IMU;
	const Telemetry_data_t * data_;

	void sendData(const Telemetry_data_t * const data)
	{
		data_ = data;
		switch (cmd_)
		{
			case TELEMETRY_CMD_IMU:
				sendIMU();
				break;
		}
	}

	void sendIMU()
	{
		// Send telemetry command
		Serial.write(TELEMETRY_CMD_IMU);

		// Acc
		write16(data_->imu.acc_raw.x);
		write16(data_->imu.acc_raw.y);
		write16(data_->imu.acc_raw.z);

		// Gyro
		write16(data_->imu.gyro_raw.x);
		write16(data_->imu.gyro_raw.y);
		write16(data_->imu.gyro_raw.z);

		// Magnetometer

		// Pressure

		// Temperature
	}

	void write8(uint8_t data)
	{
		Serial.write(data);
	}

	void write16(uint16_t data)
	{
		Serial.write((data & 0xFF00) >> 8);	// MSB
		Serial.write((data & 0x00FF));		// LSB
	}
}
