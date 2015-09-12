#include "Telemetry.h"

// It takes around 9 us / byte transmitted
namespace Telemetry
{
	const char * magic_word_ = TELEMETRY_MAGIC_WORD;
	uint8_t rx_data_buffer_[TELEMETRY_RX_BUFFER_SIZE];
	uint8_t n_bytes_available_;
	uint8_t cmd_;
	uint8_t ptr_;
}

void Telemetry::sendData(const State_data_t * const data)
{
	// Re-initialize variables
	cmd_ = 0;
	ptr_ = 0;

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
		
		// Send Magic Word
		Serial.write((uint8_t)magic_word_[0]);
		Serial.write((uint8_t)magic_word_[1]);

		// Send cmd
		Serial.write(cmd_);

		// Perform desired operation
		switch (cmd_)
		{
			case TELEMETRY_CMD_OUT_STATUS:
				sendStatus(data);
				break;
			case TELEMETRY_CMD_OUT_IMU:
				sendIMU(data);
				break;
			case TELEMETRY_CMD_OUT_MAG:
				sendMagnetometer(data);
				break;
			case TELEMETRY_CMD_OUT_BARO:
				sendBarometer(data);
				break;
			case TELEMETRY_CMD_OUT_TEMP:
				sendTemperature(data);
				break;
			case TELEMETRY_CMD_OUT_RC:
				sendRC(data);
				break;
			case TELEMETRY_CMD_OUT_BATTERY:
				sendBattery(data);
				break;
			case TELEMETRY_CMD_OUT_GPS:
				sendGPS(data);
				break;
			case TELEMETRY_CMD_OUT_SONAR:
				sendSonar(data);
				break;
			case TELEMETRY_CMD_OUT_ATTITUDE:
				sendAttitude(data);
				break;
			case TELEMETRY_CMD_OUT_CONTROL:
				sendControl(data);
				break;
		}
	}
}

void Telemetry::sendStatus(const State_data_t * const data)
{
	// TimeStamp
	write32(data->timeStamp);
}


void Telemetry::sendIMU(const State_data_t * const data)
{
	// Acc
	write16(data->imu.acc_raw.x);
	write16(data->imu.acc_raw.y);
	write16(data->imu.acc_raw.z);

	// Gyro
	write16(data->imu.gyro_raw.x);
	write16(data->imu.gyro_raw.y);
	write16(data->imu.gyro_raw.z);
}

void Telemetry::sendAttitude(const State_data_t * const data)
{
	// Send each component as int16_t, so maximum is +- 32768.
	// Multiply by 10000, since we have normalized quaternion
	write16((int16_t)(10000 * data->attitude.q0));
	write16((int16_t)(10000 * data->attitude.q1));
	write16((int16_t)(10000 * data->attitude.q2));
	write16((int16_t)(10000 * data->attitude.q3));
}

void Telemetry::sendMagnetometer(const State_data_t * const data){}
void Telemetry::sendBarometer(const State_data_t * const data){}
void Telemetry::sendTemperature(const State_data_t * const data){}
void Telemetry::sendRC(const State_data_t * const data){}
void Telemetry::sendBattery(const State_data_t * const data){}
void Telemetry::sendGPS(const State_data_t * const data){}
void Telemetry::sendSonar(const State_data_t * const data){}

void Telemetry::sendControl(const State_data_t * const data){}

void Telemetry::receivePID(Config_t * const data){}

void Telemetry::write8(uint8_t data)
{
	Serial.write(data);
}

void Telemetry::write16(uint16_t data)
{
	Serial.write(((data & 0xFF00) >> 8) & 0x00FF);	// MSB
	Serial.write((data & 0x00FF));					// LSB
}

void Telemetry::write32(uint32_t data)
{
	Serial.write(((data & 0xFF000000) >> 24) & 0x000000FF);	// MSB
	Serial.write(((data & 0x00FF0000) >> 16) & 0x000000FF);	
	Serial.write(((data & 0x0000FF00) >>  8) & 0x000000FF);	 
	Serial.write(( data & 0x000000FF));						// LSB
}
