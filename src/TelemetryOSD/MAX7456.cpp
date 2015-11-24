#include "MAX7456.h"

MAX7456::MAX7456()
{
}


MAX7456::~MAX7456()
{
}

void MAX7456::init()
{
	// Pinmode for the SS pin
	pinMode(PIN_MAX7456_SS, OUTPUT);
	max7456_ss_high();

	// Enable OSD
	this->enableOSD();

	// Set PAL mode
	uint8_t vm0 = this->readRegister(VM0_R);
	this->writeToRegister(VM0_W, (vm0 | (1 << 6)));

	// Set automatic OSD Black level
	uint8_t osdbl = this->readRegister(OSDBL_R);
	this->writeToRegister(OSDBL_W, (osdbl | (1 << 4)));	

	// Set vertical and horizontal offset
	this->writeToRegister(VOS_W, MAX7456_V_OFFSET);
	this->writeToRegister(HOS_W, MAX7456_H_OFFSET);
}

void MAX7456::writeSymbolToNVM(uint8_t charAddr, const uint8_t *data)
{
	// Disable OSD image display
	this->disableOSD();

	// Select character to be written
	this->writeToRegister(CMAH_W, charAddr);

	// Send 54 write operations to write the character to the NVM
	for (uint8_t i = 0; i < OSD_CHAR_SIZE_BYTES; ++i)
	{
		this->writeToRegister(CMAL_W, i);
		this->writeToRegister(CMDI_W, data[i]);
	}

	// Execute transfer from shadow RAM to SVM
	this->writeToRegister(CMM_W, 0xC0);

	// Keep reading STAT until the operation is finished
	while (this->isBusy());

	// Enable OSD
	this->enableOSD();
}

void MAX7456::readSymbolFromNVM(uint8_t charAddr, uint8_t *data)
{
	// Disable OSD
	this->disableOSD();

	// Select character to read
	this->writeToRegister(CMAH_W, charAddr);

	// Start transfer from NVM to shadow RAM and wait
	this->writeToRegister(CMM_W, 0x50);
	while (this->isBusy());

	// Read character
	for (uint8_t i = 0; i < OSD_CHAR_SIZE_BYTES; ++i)
	{
		this->writeToRegister(CMAL_W, i);
		data[i] = this->readRegister(CMDO_R);
	}

	// Enable OSD
	this->enableOSD();
}

void MAX7456::enableOSD()
{
	uint8_t vm0 = this->readRegister(VM0_R);
	this->writeToRegister(VM0_W, vm0 | (1 << 3));
}

void MAX7456::disableOSD()
{
	uint8_t vm0 = this->readRegister(VM0_R);
	this->writeToRegister(VM0_W, vm0 & ~(1 << 3));
}

void MAX7456::clearDisplay()
{
	// Set DMM[2] = 1
	uint8_t dmm = this->readRegister(DMM_R);
	this->writeToRegister(DMM_W, dmm | (1 << 2));

	// Wait until finished
	bool finished(false);
	while (!finished)
	{
		dmm = this->readRegister(DMM_R);
		finished = ((dmm & (1 << 2)) == 0);
	}
}

void MAX7456::writeCharToDisplay16(uint16_t displayAddr, uint8_t charAddr)
{
	// By default, DMM is 16-bit and desired byte attributes
	// Set display address
	this->writeToRegister(DMAH_W, (displayAddr & 0x0100) > 0);
	this->writeToRegister(DMAL_W,  displayAddr & 0x00FF);

	// Write character addr
	this->writeToRegister(DMDI_W, charAddr);
}

void MAX7456::displayCharacter(uint8_t x, uint8_t y, uint8_t charAddr)
{
	if (x < SCREEN_SIZE_COLS && y < SCREEN_SIZE_ROWS)
	{
		// Compute linear index
		uint16_t idx = ((uint16_t)y) * SCREEN_SIZE_COLS + (uint16_t)x;

		// Display character
		this->writeCharToDisplay16(idx, charAddr);
	}
}

uint8_t MAX7456::readRegister(uint8_t addr)
{
	uint8_t out;
	max7456_ss_low();

	SPI::writeByte(addr);
	out = SPI::readByte();

	max7456_ss_high();
	return out;
}

void MAX7456::writeToRegister(uint8_t addr, uint8_t data)
{
	max7456_ss_low();

	SPI::writeByte(addr);
	SPI::writeByte(data);

	max7456_ss_high();
}

bool MAX7456::isBusy()
{
	return (this->readRegister(STAT_R) & (1 << 5));
}