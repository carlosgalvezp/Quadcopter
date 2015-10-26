#include "GPS.h"

namespace GPS
{
	uint8_t gps_payload_buffer[GPS_RX_BUFFER_SIZE];
	uint8_t gps_payload_buffer_ptr = 0;

	bool headerIsRead = false;

	uint8_t checksum_a = 0;
	uint8_t checksum_b = 0;

	uint16_t msgToRead = 0;
	uint16_t payloadLengthToRead = 0;
}

void GPS::init()
{
	Serial_GPS.begin(GPS_SERIAL_BAUDRATE);
}

bool GPS::getGPSData(GPS_Data_t *data)
{
	// Receive serial data
	if (GPS::Internal::receiveSerialData())
	{
		switch (GPS::msgToRead)
		{
			case GPS_MSG_NAV_SOL:
				return GPS::Internal::Decode::decodeNavSol(data);
		}
	}
	return false;
}

bool GPS::Internal::receiveSerialData()
{
	// Check if we have data in the Serial port
	if (Serial_GPS.available())
	{
		// First, read the header in case we haven't started storing the payload
		if (!GPS::headerIsRead)
		{
			GPS::headerIsRead = GPS::Internal::readHeader(&GPS::msgToRead, &GPS::payloadLengthToRead);
		}
		// Then, read the payload
		else
		{
			if (GPS::Internal::readPayload(GPS::payloadLengthToRead))
			{
				// Prepare for next frame
				GPS::headerIsRead = false;

				// Validate checksum
				if (gps_payload_buffer[GPS::payloadLengthToRead    ] == checksum_a &&
					gps_payload_buffer[GPS::payloadLengthToRead + 1] == checksum_b)
				{
					return true;
				}
				
			}
		}
	}
	return false;
}

bool GPS::Internal::readHeader(uint16_t *msg, uint16_t *length)
{
	if (Serial_GPS.available() > GPS_HEADER_LENGTH)
	{
		// Look for first character of magic word
		uint8_t nBytesRead(0);
		while (nBytesRead < GPS_RX_BATCH_READ_SIZE && Serial_GPS.read() != GPS_MAGIC_WORD_FIRST)
		{
			++nBytesRead;
		}
	
		if (nBytesRead == GPS_RX_BATCH_READ_SIZE) return false;

		// Check if the next character is the second byte of the magic word
		if (Serial_GPS.read() == GPS_MAGIC_WORD_SECOND)
		{
			// Reset checksums and pointer
			checksum_a = 0;
			checksum_b = 0;
			gps_payload_buffer_ptr = 0;
			// Read class, ID and payload length
			*msg =  ((((uint16_t)readByteAndComputeCheckSum())   << 8) & 0xFF00) |
					((((uint16_t)readByteAndComputeCheckSum())       ) & 0x00FF);
		
			*length = ((((uint16_t)readByteAndComputeCheckSum())     ) & 0x00FF) |
					  ((((uint16_t)readByteAndComputeCheckSum()) << 8) & 0xFF00);

			return *length <= GPS_RX_BUFFER_SIZE;		
		}
	}
	return false;
}

bool GPS::Internal::readPayload(uint16_t payloadLength)
{
	uint8_t nBytesRead(0);
	// Store payload in buffer
	while (nBytesRead < GPS_RX_BATCH_READ_SIZE          && 
		   gps_payload_buffer_ptr < (payloadLength + 2) &&
		   Serial_GPS.available())
	{
		++nBytesRead;
		if (gps_payload_buffer_ptr < 0 || gps_payload_buffer_ptr> GPS_RX_BUFFER_SIZE)
		{
			Serial.println("================= EPIC FAIL ===============");
			Serial.println(gps_payload_buffer_ptr);
			delay(2000);
		}

		// Read payload
		if (gps_payload_buffer_ptr < payloadLength)
		{
			gps_payload_buffer[gps_payload_buffer_ptr++] = readByteAndComputeCheckSum();
		}
		else // Read checksum
		{
			gps_payload_buffer[gps_payload_buffer_ptr++] = Serial_GPS.read();
		}
	}
	return gps_payload_buffer_ptr == payloadLength + 2; // Return true if we have read all the bytes: payload + checksum(2)
}

bool GPS::Internal::Decode::decodeNavSol(GPS_Data_t *data)
{
	// Check if the GPS has a good fix by reading the "flags" byte, fixOK bit
	if (gps_payload_buffer[11] & GPS_NAV_FIX_OK_MASK)
	{
		// Fix type
		data->fix = gps_payload_buffer[10];

		// Number of satellites
		data->nSatellites = gps_payload_buffer[47];

		// Position
		data->position_ecef.x = (int32_t)GPS::Internal::Decode::decode32LittleEndian(&gps_payload_buffer[12]);
		data->position_ecef.y = (int32_t)GPS::Internal::Decode::decode32LittleEndian(&gps_payload_buffer[16]);
		data->position_ecef.z = (int32_t)GPS::Internal::Decode::decode32LittleEndian(&gps_payload_buffer[20]);

		// Velocity
		data->velocity_ecef.x = (int32_t)GPS::Internal::Decode::decode32LittleEndian(&gps_payload_buffer[28]);
		data->velocity_ecef.y = (int32_t)GPS::Internal::Decode::decode32LittleEndian(&gps_payload_buffer[32]);
		data->velocity_ecef.z = (int32_t)GPS::Internal::Decode::decode32LittleEndian(&gps_payload_buffer[36]);

		return true;
	}
	return false;
}

uint8_t GPS::Internal::readByteAndComputeCheckSum()
{
	uint8_t data = Serial_GPS.read();

	checksum_a += data;
	checksum_b += checksum_a;

	return data;
}

uint16_t GPS::Internal::Decode::decode16LittleEndian(const uint8_t *buffer)
{
	return ((((uint16_t) buffer[0])     ) & 0x00FF) |
		   ((((uint16_t) buffer[1]) << 8) & 0xFF00);
}

uint32_t GPS::Internal::Decode::decode32LittleEndian(const uint8_t *buffer)
{
	return ((((uint32_t) buffer[0])      ) & 0x000000FF) |
		   ((((uint32_t) buffer[1]) <<  8) & 0x0000FF00) |
		   ((((uint32_t) buffer[2]) << 16) & 0x00FF0000) |
		   ((((uint32_t) buffer[3]) << 24) & 0xFF000000);
}