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

void Telemetry::sendData(const State_data_t * const data)
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
		
		// Send Magic Word
		write8((uint8_t)magic_word_[0]);
		write8((uint8_t)magic_word_[1]);

		// Send cmd
		write8(cmd_);

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

		// Send checksum
		sendCheckSum();
	}
}

void Telemetry::sendStatus(const State_data_t * const data)
{
	// TimeStamp
	write32(data->status.timeStamp);

	// Cycle time
	write16(data->status.cycleTime);
}

void Telemetry::sendRC(const State_data_t * const data)
{
	write16(data->rc.throttle);
	write16(data->rc.rudder);
	write16(data->rc.elevator);
	write16(data->rc.aileron);
	write16(data->rc.aux1);
	write16(data->rc.aux2);
	write16(data->rc.aux3);
	write16(data->rc.aux4);
}


void Telemetry::sendIMU(const State_data_t * const data)
{
	// Acc
	write16(data->sensorData.imu.acc_raw.x);
	write16(data->sensorData.imu.acc_raw.y);
	write16(data->sensorData.imu.acc_raw.z);

	// Gyro
	write16(data->sensorData.imu.gyro_raw.x);
	write16(data->sensorData.imu.gyro_raw.y);
	write16(data->sensorData.imu.gyro_raw.z);
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

void Telemetry::sendControl(const State_data_t * const data)
{
	write16(data->motors[0]);
	write16(data->motors[1]);
	write16(data->motors[2]);
	write16(data->motors[3]);
}


void Telemetry::sendMagnetometer(const State_data_t * const data){}
void Telemetry::sendBarometer(const State_data_t * const data){}
void Telemetry::sendTemperature(const State_data_t * const data){}
void Telemetry::sendBattery(const State_data_t * const data){}
void Telemetry::sendGPS(const State_data_t * const data){}
void Telemetry::sendSonar(const State_data_t * const data){}


void Telemetry::receivePID(Config * const data){}

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
