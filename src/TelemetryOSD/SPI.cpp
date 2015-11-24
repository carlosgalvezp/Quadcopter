#include "SPI.h"

void SPI::init()
{
	// Pinmode for SPI pins
	pinMode(SPI_PIN_MOSI, OUTPUT);
	pinMode(SPI_PIN_MISO, INPUT);
	pinMode(SPI_PIN_SCK,  OUTPUT);
	pinMode(SPI_PIN_SS,	  OUTPUT);
	
	// Disable power reduction bit
	PRR &= ~(1 << PRSPI);

	// Configure SPI: enable, master, Fclk/4
	SPCR = (1 << SPE) | (1 << MSTR);

	// Read junk data from registers
	//uint8_t dummy;
	//dummy = SPSR;
	//dummy = SPDR;
}


void SPI::writeByte(uint8_t data)
{
	// Load data into register
	SPDR = data;

	// Wait until transmission is completed
	while (!(SPSR & (1 << SPIF)));
}

uint8_t SPI::readByte()
{
	// Send dummy data to generate clock cycles
	SPDR = SPI_STUFFING_BYTE;

	// Wait until the data is completely received
	while (!(SPSR & (1 << SPIF)));

	// Read 
	return SPDR;
}