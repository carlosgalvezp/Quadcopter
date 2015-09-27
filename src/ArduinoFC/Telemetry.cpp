#include "Telemetry.h"

// It takes around 9 us / byte transmitted
namespace Telemetry
{
	const char * magic_word_ = TELEMETRY_MAGIC_WORD;
	uint8_t rx_data_buffer_[TELEMETRY_RX_BUFFER_SIZE];
	uint8_t n_bytes_available_;
	uint8_t cmd_;
	uint8_t ptr_;
	uint8_t checksum_;
}

void Telemetry::main(const State_data_t * const state, Config * const config)
{
	// Re-initialize variables
	cmd_ = 0;
	ptr_ = 0;
	checksum_ = 0;

	// Check whether we have a request available
	if ((n_bytes_available_ = Serial.available()) > 0)
	{
		// Read all data
		Serial.readBytes(rx_data_buffer_, n_bytes_available_);

		// Check for the magic word
		if (rx_data_buffer_[ptr_++] == magic_word_[0] && rx_data_buffer_[ptr_++] == magic_word_[1])
		{
			cmd_ = rx_data_buffer_[ptr_++];
		}

		if (cmd_ == TELEMETRY_CMD_IN_CONFIG)
		{
			Telemetry::receiveConfig(config);
		}

		else
		{
			// Send Magic Word
			write8((uint8_t)magic_word_[0]);
			write8((uint8_t)magic_word_[1]);

			// Send cmd
			write8(cmd_);

			// Perform desired operation
			switch (cmd_)
			{
				case TELEMETRY_CMD_OUT_STATUS:
					sendStatus(state);
					break;
				case TELEMETRY_CMD_OUT_IMU:
					sendIMU(state);
					break;
				case TELEMETRY_CMD_OUT_MAG:
					sendMagnetometer(state);
					break;
				case TELEMETRY_CMD_OUT_BARO:
					sendBarometer(state);
					break;
				case TELEMETRY_CMD_OUT_TEMP:
					sendTemperature(state);
					break;
				case TELEMETRY_CMD_OUT_RC:
					sendRC(state);
					break;
				case TELEMETRY_CMD_OUT_BATTERY:
					sendBattery(state);
					break;
				case TELEMETRY_CMD_OUT_GPS:
					sendGPS(state);
					break;
				case TELEMETRY_CMD_OUT_SONAR:
					sendSonar(state);
					break;
				case TELEMETRY_CMD_OUT_ATTITUDE:
					sendAttitude(state);
					break;
				case TELEMETRY_CMD_OUT_CONTROL:
					sendControl(state);
					break;
			}
			// Send checksum
			sendCheckSum();
		}
	}
}

void Telemetry::sendStatus(const State_data_t * const data)
{
	// TimeStamp
	Telemetry::write32(data->status.timeStamp);

	// Cycle time
	Telemetry::write16(data->status.cycleTime);
}

void Telemetry::sendRC(const State_data_t * const data)
{
	Telemetry::write16(data->rc.throttle);
	Telemetry::write16(data->rc.rudder);
	Telemetry::write16(data->rc.elevator);
	Telemetry::write16(data->rc.aileron);
	Telemetry::write16(data->rc.aux1);
	Telemetry::write16(data->rc.aux2);
	Telemetry::write16(data->rc.aux3);
	Telemetry::write16(data->rc.aux4);
}


void Telemetry::sendIMU(const State_data_t * const data)
{
	// Acc
	Telemetry::write16(data->sensorData.imu.acc_raw.x);
	Telemetry::write16(data->sensorData.imu.acc_raw.y);
	Telemetry::write16(data->sensorData.imu.acc_raw.z);

	// Gyro
	Telemetry::write16(data->sensorData.imu.gyro_raw.x);
	Telemetry::write16(data->sensorData.imu.gyro_raw.y);
	Telemetry::write16(data->sensorData.imu.gyro_raw.z);
}

void Telemetry::sendAttitude(const State_data_t * const data)
{
	// Send each component as int16_t, so maximum is +- 32768.
	// Multiply by 10000, since we have normalized quaternion
	Telemetry::write16((int16_t)(10000 * data->attitude.q0));
	Telemetry::write16((int16_t)(10000 * data->attitude.q1));
	Telemetry::write16((int16_t)(10000 * data->attitude.q2));
	Telemetry::write16((int16_t)(10000 * data->attitude.q3));
}

void Telemetry::sendControl(const State_data_t * const data)
{
	Telemetry::write16(data->motors[0]);
	Telemetry::write16(data->motors[1]);
	Telemetry::write16(data->motors[2]);
	Telemetry::write16(data->motors[3]);
}


void Telemetry::sendMagnetometer(const State_data_t * const data){}
void Telemetry::sendBarometer(const State_data_t * const data){}
void Telemetry::sendTemperature(const State_data_t * const data){}
void Telemetry::sendBattery(const State_data_t * const data){}
void Telemetry::sendGPS(const State_data_t * const data){}
void Telemetry::sendSonar(const State_data_t * const data){}

void Telemetry::sendConfig(const Config * const config)
{
	// PID
	Telemetry::write32((uint32_t)config->pid_roll.kp);
	Telemetry::write32((uint32_t)config->pid_roll.kd);
	Telemetry::write32((uint32_t)config->pid_roll.ki);

	Telemetry::write32((uint32_t)config->pid_pitch.kp);
	Telemetry::write32((uint32_t)config->pid_pitch.kd);
	Telemetry::write32((uint32_t)config->pid_pitch.ki);

	Telemetry::write32((uint32_t)config->pid_yaw.kp);
	Telemetry::write32((uint32_t)config->pid_yaw.kd);
	Telemetry::write32((uint32_t)config->pid_yaw.ki);
}

void Telemetry::receiveConfig(Config * const data)
{
	checksum_ = 0;
	// Verify checksum
	uint8_t checksum = 0;
	for (uint8_t i = 0; i < n_bytes_available_; ++i)
	{
		checksum ^= rx_data_buffer_[i];
	}

	if (checksum == 0)
	{
		// PID
		data->pid_roll.kp = (float)Telemetry::read32(3);
		data->pid_roll.kd = (float)Telemetry::read32(7);
		data->pid_roll.ki = (float)Telemetry::read32(11);

		data->pid_pitch.kp = (float)Telemetry::read32(15);
		data->pid_pitch.kd = (float)Telemetry::read32(19);
		data->pid_pitch.ki = (float)Telemetry::read32(23);

		data->pid_yaw.kp = (float)Telemetry::read32(27);
		data->pid_yaw.kd = (float)Telemetry::read32(31);
		data->pid_yaw.ki = (float)Telemetry::read32(35);

		// Store config
		EEPROM::storeConfig(data);

		// Send ACK
		write8((uint8_t)magic_word_[0]);
		write8((uint8_t)magic_word_[1]);
		write8(TELEMETRY_ACK);
	}
	else
	{
		// Send NACK so that we the app will send data again
		write8((uint8_t)magic_word_[0]);
		write8((uint8_t)magic_word_[1]);
		write8(TELEMETRY_NACK);
	}
	// Write checksum
	sendCheckSum();
}

void Telemetry::sendCheckSum()
{
	Serial.write(checksum_);
}

void Telemetry::write16(uint16_t data)
{
	write8((uint8_t)(((data & 0xFF00) >> 8) & 0x00FF));	// MSB
	write8((uint8_t)(( data & 0x00FF)));				// LSB
}

void Telemetry::write32(uint32_t data)
{
	write8((uint8_t)(((data & 0xFF000000) >> 24) & 0x000000FF));	// MSB
	write8((uint8_t)(((data & 0x00FF0000) >> 16) & 0x000000FF));	
	write8((uint8_t)(((data & 0x0000FF00) >>  8) & 0x000000FF));	 
	write8((uint8_t)(( data & 0x000000FF)));						// LSB
}

uint16_t Telemetry::read16(uint8_t ptr)
{
	return (((uint16_t)rx_data_buffer_[ptr    ] << 8) & 0xFF00) |
		   (((uint16_t)rx_data_buffer_[ptr + 1]     ) & 0x00FF);			
}

uint32_t Telemetry::read32(uint8_t ptr)
{
	return (((uint32_t)rx_data_buffer_[ptr    ] << 24) & 0xFF000000) |
		   (((uint32_t)rx_data_buffer_[ptr + 1] << 16) & 0x00FF0000) |
		   (((uint32_t)rx_data_buffer_[ptr + 2] <<  8) & 0x0000FF00) |
		   (((uint32_t)rx_data_buffer_[ptr + 3]      ) & 0x000000FF);
}