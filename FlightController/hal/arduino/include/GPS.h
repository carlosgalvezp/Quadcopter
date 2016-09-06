#ifndef GPS_H
#define GPS_H

#include "core/Types.h"
#include "HAL.h"

#define GPS_RX_BUFFER_SIZE		100
#define GPS_RX_BATCH_READ_SIZE	5	   // Number of bytes we read at every iteration, in order not to spend too much time
#define GPS_SERIAL_BAUDRATE		115200

#define GPS_MAGIC_WORD_FIRST	0xB5
#define GPS_MAGIC_WORD_SECOND	0x62

#define GPS_MSG_NAV_SOL			0x0106

#define GPS_HEADER_LENGTH		6
#define GPS_NAV_SOL_LENGTH		52
#define GPS_NAV_FIX_OK_MASK		0x01

namespace GPS
{
	void init();
	bool getGPSData(GPSData& data);

	namespace Internal
	{
		bool receiveSerialData();

		bool readHeader(uint16_t *msg, uint16_t *length);
		bool readPayload(uint16_t payloadLength);
		uint8_t readByteAndComputeCheckSum();

		namespace Decode
		{
			bool decodeNavSol(GPSData& data);

			uint16_t decode16LittleEndian(const uint8_t *buffer);
			uint32_t decode32LittleEndian(const uint8_t *buffer);
		}
	}
}
#endif
