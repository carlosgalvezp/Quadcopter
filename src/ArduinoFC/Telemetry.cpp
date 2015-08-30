#include "Telemetry.h"

// It takes around 9 us / byte transmitted
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

	void sendAttitude(const quaternion_t * const q)
	{
		Serial.write(TELEMETRY_CMD_ATTITUDE);

		// Send each component as int16_t, so maximum is +- 32768.
		// Multiply by 10000, since we have normalized quaternion
		write16((int16_t)(10000 * q->q0));
		write16((int16_t)(10000 * q->q1));
		write16((int16_t)(10000 * q->q2));
		write16((int16_t)(10000 * q->q3));
	}

	void write8(int8_t data)
	{
		Serial.write(data);
	}

	void write16(int16_t data)
	{
		Serial.write(((data & 0xFF00) >> 8) & 0x00FF);	// MSB
		Serial.write((data & 0x00FF));					// LSB
	}
}
