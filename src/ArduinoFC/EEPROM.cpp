#include "EEPROM.h"


uint8_t	EEPROM::read(uint16_t addr)
{
	return eeprom_read_byte( (uint8_t *) addr);
}

uint16_t EEPROM::read16(uint16_t addr)
{
	return ((((uint16_t) read(addr    )) << 8) & 0xFF00) | 
		   ((((uint16_t) read(addr + 1))     ) & 0x00FF);
}

uint32_t EEPROM::read32(uint16_t addr)
{
	return ((((uint32_t) read(addr    )) << 24) & 0xFF000000) | 
		   ((((uint32_t) read(addr + 1)) << 16) & 0x00FF0000) |
		   ((((uint32_t) read(addr + 2)) <<  8) & 0x0000FF00) |
		   ((((uint32_t) read(addr + 3))      ) & 0x000000FF);
}

void EEPROM::write(uint16_t addr, uint8_t data)
{
	return eeprom_write_byte((uint8_t *) addr, data);
}

void EEPROM::write16(uint16_t addr, uint16_t data)
{
	write(addr    , (uint8_t)(((data & 0xFF00) >> 8) & 0x00FF));
	write(addr + 1, (uint8_t)(((data & 0x00FF)     ) & 0x00FF));
}


void EEPROM::write32(uint16_t addr, uint32_t data)
{
	write(addr,     (uint8_t)(((data & 0xFF000000) >> 24) & 0x000000FF));
	write(addr + 1, (uint8_t)(((data & 0x00FF0000) >> 16) & 0x000000FF));
	write(addr + 2, (uint8_t)(((data & 0x0000FF00) >>  8) & 0x000000FF));
	write(addr + 3, (uint8_t)(((data & 0x000000FF)      ) & 0x000000FF));
}
