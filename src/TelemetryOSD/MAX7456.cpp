#include "MAX7456.h"


MAX7456::MAX7456()
{
	this->init();
}


MAX7456::~MAX7456()
{
}

void MAX7456::init()
{
	// Pinmode for the SS pin
	pinMode(PIN_MAX7456_SS, OUTPUT);
	digitalWrite(PIN_MAX7456_SS, HIGH);

	// Enable OSD
	this->enableOSD();

	// Set PAL mode
	uint8_t vm0 = this->transferRegister(VM0_R, SPI_STUFFING_BYTE);
	this->transferRegister(VM0_W, (vm0 | (1 << 6)));

	// Set automatic OSD Black level
	uint8_t osdbl = this->transferRegister(OSDBL_R, SPI_STUFFING_BYTE);
	this->transferRegister(OSDBL_W, (osdbl | (1 << 4)));	
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
		this->transferRegister(CMAL_W, i);
		this->transferRegister(CMDI_W, data[i]);
	}

	// Execute transfer from shadow RAM to SVM
	this->transferRegister(CMM_W, 0xC0);

	// Keep reading STAT until the operation is finished
	while (this->isBusy());

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

void MAX7456::clearDisplay()
{
	// Set DMM[2] = 1
	uint8_t dmm = this->transferRegister(DMM_R, SPI_STUFFING_BYTE);
	this->transferRegister(DMM_W, dmm | (1 << 2));

	// Wait until finished
	bool finished(false);
	while (!finished)
	{
		dmm = this->transferRegister(DMM_R, SPI_STUFFING_BYTE);
		finished = ((dmm & (1 << 2)) == 0);
	}
}

void MAX7456::writeCharToDisplay16(uint16_t displayAddr, uint8_t charAddr)
{
	// By default, DMM is 16-bit and desired byte attributes
	// Set display address
	this->transferRegister(DMAH_W, (displayAddr & 0x0100) > 0);
	this->transferRegister(DMAL_W,  displayAddr & 0x00FF);

	// Write character addr
	this->transferRegister(DMDI_W, charAddr);
}

void MAX7456::displayCharacter(uint8_t x, uint8_t y, uint8_t charAddr)
{
	// Compute linear index
	uint16_t idx = ((uint16_t) y) * SCREEN_SIZE_COLS + (uint16_t)x;

	// Display character
	this->writeCharToDisplay16(idx, charAddr);
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