#include "SPI.h"

void SPI::init()
{
	// Pinmode for SPI pins
	pinMode(SPI_PIN_MOSI, OUTPUT);
	pinMode(SPI_PIN_MISO, INPUT);
	pinMode(SPI_PIN_SCK,  OUTPUT);
	pinMode(SPI_PIN_SS,   OUTPUT);

	// Disable power reduction bit
	PRR &= ~(1 << PRSPI);

	// Configure SPI: enable, master, Fclk/4
	SPCR |= (1 << SPE) | (1 << MSTR);
}

void SPI::write(uint8_t *data, unsigned long dataLength)
{
	for (unsigned long i = 0; i < dataLength; ++i)
	{
		SPI::writeByte(data[i]);
	}
}

void SPI::writeByte(uint8_t data)
{
	// Load data into register
	SPDR = data;

	// Wait until transmission is completed
	while (!(SPSR & (1 << SPIF)));
}

