#include "Telemetry.h"

// It takes around 9 us / byte transmitted
namespace Telemetry
{
	const char * magic_word_ = TELEMETRY_MAGIC_WORD;
	uint8_t rx_data_buffer_[TELEMETRY_RX_BUFFER_SIZE];
	uint8_t n_bytes_available_;
	uint8_t cmd_;
	uint8_t ptr_ = 0;
	uint8_t checksum_;
}

void Telemetry::main(const State_t * const state, Config_t * const config)
{
	// Re-initialize variables
	cmd_ = 0;
	checksum_ = 0;

	// Check whether we have a request available
	if ((n_bytes_available_ = Serial_Telemetry.available()) > 0)
	{
		// Read all data to tmp buffer. It is possible that not all the data has arrived yet
		Serial_Telemetry.readBytes(&(rx_data_buffer_[ptr_]), n_bytes_available_);
		ptr_ += n_bytes_available_;
	}
	else	// No more data to receive 
	{
		if(ptr_ > 0)	// We have data to process
		{
			// Check for the magic word
			if (rx_data_buffer_[0] == magic_word_[0] && rx_data_buffer_[1] == magic_word_[1])
			{
				cmd_ = rx_data_buffer_[2];
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
					case TELEMETRY_CMD_OUT_CONFIG:
						sendConfig(config);
						break;
				} // switch cmd
				sendCheckSum();
			} // config_in
			ptr_ = 0; // Prepare for next package
		} // ptr_ > 0
	} // n_bytes > 0
}

void Telemetry::sendStatus(const State_t * const data)
{
	// TimeStamp
	Telemetry::write32(data->status.timeStamp);

	// Cycle time
	Telemetry::write16(data->status.cycleTime);

	// Battery
	Telemetry::write16(data->status.battery.voltage);
	Telemetry::write16(data->status.battery.current);

	// Flight mode
	write8(data->status.flightMode);
}

void Telemetry::sendRC(const State_t * const data)
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


void Telemetry::sendIMU(const State_t * const data)
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

void Telemetry::sendAttitude(const State_t * const data)
{
	// Send each component as int16_t, so maximum is +- 32768.
	// Multiply by 10000, since we have normalized quaternion
	Telemetry::write16((int16_t)(10000 * data->attitude.q0));
	Telemetry::write16((int16_t)(10000 * data->attitude.q1));
	Telemetry::write16((int16_t)(10000 * data->attitude.q2));
	Telemetry::write16((int16_t)(10000 * data->attitude.q3));
}

void Telemetry::sendControl(const State_t * const data)
{
	Telemetry::write16(data->motors[0]);
	Telemetry::write16(data->motors[1]);
	Telemetry::write16(data->motors[2]);
	Telemetry::write16(data->motors[3]);
}


void Telemetry::sendMagnetometer(const State_t * const data){}
void Telemetry::sendBarometer(const State_t * const data){}
void Telemetry::sendTemperature(const State_t * const data){}
void Telemetry::sendGPS(const State_t * const data){}
void Telemetry::sendSonar(const State_t * const data){}

void Telemetry::sendConfig(const Config_t * const config)
{
	// PID
	Telemetry::writeFloat(config->pid_roll.kp);
	Telemetry::writeFloat(config->pid_roll.kd);
	Telemetry::writeFloat(config->pid_roll.ki);

	Telemetry::writeFloat(config->pid_pitch.kp);
	Telemetry::writeFloat(config->pid_pitch.kd);
	Telemetry::writeFloat(config->pid_pitch.ki);

	Telemetry::writeFloat(config->pid_yaw.kp);
	Telemetry::writeFloat(config->pid_yaw.kd);
	Telemetry::writeFloat(config->pid_yaw.ki);
}

void Telemetry::receiveConfig(Config_t * const data)
{		
	// Verify checksum
	uint8_t checksum = 0;
	for (uint8_t i = 0; i < ptr_; ++i)
	{
		checksum ^= rx_data_buffer_[i];
	}
	
	if (checksum == 0)
	{
		// PID
		data->pid_roll.kp = Telemetry::readFloat(3);
		data->pid_roll.kd = Telemetry::readFloat(7);
		data->pid_roll.ki = Telemetry::readFloat(11);

		data->pid_pitch.kp = Telemetry::readFloat(15);
		data->pid_pitch.kd = Telemetry::readFloat(19);
		data->pid_pitch.ki = Telemetry::readFloat(23);
		
		data->pid_yaw.kp = Telemetry::readFloat(27);
		data->pid_yaw.kd = Telemetry::readFloat(31);
		data->pid_yaw.ki = Telemetry::readFloat(35);

		// Store config
		EEPROM::storeConfig(data);

		// Send ACK
		sendACK();
	}
}

void Telemetry::sendACK()
{
	checksum_ = 0;
	write8((uint8_t)magic_word_[0]);
	write8((uint8_t)magic_word_[1]);
	write8(TELEMETRY_ACK);

	// Write checksum
	sendCheckSum();
}

void Telemetry::sendCheckSum()
{
	Serial_Telemetry.write(checksum_);
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

void Telemetry::writeFloat(float data)
{
	u_float_u32 dataUnion;
	dataUnion.xf = data;
	Telemetry::write32(dataUnion.xu);
}

uint16_t Telemetry::read16(uint8_t ptr)
{
	return (((uint16_t)(rx_data_buffer_[ptr    ]) << 8) & 0xFF00) |
		   (((uint16_t)(rx_data_buffer_[ptr + 1])     ) & 0x00FF);			
}

uint32_t Telemetry::read32(uint8_t ptr)
{
	return (((uint32_t)(rx_data_buffer_[ptr    ]) << 24) & 0xFF000000) |
		   (((uint32_t)(rx_data_buffer_[ptr + 1]) << 16) & 0x00FF0000) |
		   (((uint32_t)(rx_data_buffer_[ptr + 2]) <<  8) & 0x0000FF00) |
		   (((uint32_t)(rx_data_buffer_[ptr + 3])      ) & 0x000000FF);
}

float Telemetry::readFloat(uint8_t ptr)
{
	u_float_u32 dataUnion;
	dataUnion.xu = Telemetry::read32(ptr);
	return dataUnion.xf;
}
