#pragma once
#ifndef SPI_H
#define SPI_H

#include <Arduino.h>
#include <avr/io.h>
#include <stdint.h>

#define SPI_PIN_SS		10
#define SPI_PIN_MOSI	11
#define SPI_PIN_MISO	12
#define SPI_PIN_SCK		13

#define SPI_STUFFING_BYTE	0xFF

namespace SPI
{
	void init();
	void write(const uint8_t *data, unsigned long dataLength);
	void read(uint8_t *data, unsigned long dataLength);

	uint8_t transferByte(uint8_t data);
	uint8_t readByte();
	void writeByte(uint8_t data);
}

#endif
