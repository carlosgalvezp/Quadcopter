#include "MAX7456.h"


MAX7456::MAX7456()
{

}


MAX7456::~MAX7456()
{
}

void MAX7456::setChar(uint8_t charAddr, const uint8_t *data)
{
	// Disable OSD image display
	this->disableOSD();

	// Select character to be written
	this->transferRegister(CMAH_W, charAddr);

	// Send 54 write operations to write the character to the NVM
	for (uint8_t i = 0; i < OSD_CHAR_SIZE_BYTES; ++i)
	{
		this->transferRegister(i, data[i]);
	}

	// Execute transfer from shadow RAM to SVM
	this->transferRegister(CMM_W, 0xC0);

	// Keep reading STAT until the operation is finished
	bool finished(false);
	while (!finished)
	{
		finished = this->transferRegister(STAT_R, SPI_STUFFING_BYTE);
	}

	// Enable OSD
	this->enableOSD();
}

void MAX7456::getChar(uint8_t charAddr, uint8_t *data)
{
	// Disable OSD
	this->disableOSD();

	// Select character to read
	this->transferRegister(CMAH_W, charAddr);

	// Start transfer from NVM to shadow RAM and wait
	this->transferRegister(CMM_W, 0x50);
	while (this->isBusy());

	// Read character
	for (uint8_t i = 0; i < OSD_CHAR_SIZE_BYTES; ++i)
	{
		this->transferRegister(CMAL_W, i);
		data[i] = this->transferRegister(CMDO_R, SPI_STUFFING_BYTE);
	}

	// Enable OSD
	this->enableOSD();
}

void MAX7456::enableOSD()
{
	uint8_t vm0 = this->transferRegister(VM0_R, SPI_STUFFING_BYTE);
	this->transferRegister(VM0_W, vm0 | (1 << 3));
}

void MAX7456::disableOSD()
{
	uint8_t vm0 = this->transferRegister(VM0_R, SPI_STUFFING_BYTE);
	this->transferRegister(VM0_W, vm0 & ~(1 << 3));
}

uint8_t MAX7456::transferRegister(uint8_t addr, uint8_t data)
{
	uint8_t out;

	digitalWrite(PIN_MAX7456_SS, LOW);

	SPI::transferByte(addr);
	out = SPI::transferByte(data);

	digitalWrite(PIN_MAX7456_SS, HIGH);

	return out;
}

bool MAX7456::isBusy()
{
	return (this->transferRegister(STAT_R, 0xFF) & (1 << 5));
}