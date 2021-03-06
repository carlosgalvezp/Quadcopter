#ifndef EEPROM_H
#define EEPROM_H

#include <stdint.h>
#include <avr/eeprom.h>

#include "core/Config.h"

// Max EEEPROM SIZE
#define EEPROM_MAX_SIZE_BYTES	4096

// Base address for the EEPROM
#define EEPROM_ADDR_BASE			0x0000
#define EEPROM_ADDR_PID_BASE		(EEPROM_ADDR_BASE + 100)

// PID coefficients (floats, 4 bytes each)
#define EEPROM_ADDR_PID_ROLL_KP		(EEPROM_ADDR_PID_BASE + 0)
#define EEPROM_ADDR_PID_ROLL_KD		(EEPROM_ADDR_PID_BASE + 4)
#define EEPROM_ADDR_PID_ROLL_KI		(EEPROM_ADDR_PID_BASE + 8)
#define EEPROM_ADDR_PID_PITCH_KP	(EEPROM_ADDR_PID_BASE + 12)
#define EEPROM_ADDR_PID_PITCH_KD	(EEPROM_ADDR_PID_BASE + 16)
#define EEPROM_ADDR_PID_PITCH_KI	(EEPROM_ADDR_PID_BASE + 20)
#define EEPROM_ADDR_PID_YAW_KP		(EEPROM_ADDR_PID_BASE + 24)
#define EEPROM_ADDR_PID_YAW_KD		(EEPROM_ADDR_PID_BASE + 28)
#define EEPROM_ADDR_PID_YAW_KI		(EEPROM_ADDR_PID_BASE + 32)

class EEPROM
{
public:
	static void clear();

	static void loadConfig(Config& config);
	static void storeConfig(const Config& config);

	static uint8_t		read  (uint16_t addr);
	static uint16_t		read16(uint16_t addr);
	static uint32_t		read32(uint16_t addr);
	static float		readFloat(uint16_t addr);


	static void			write  (uint16_t addr, uint8_t data);
	static void			write16(uint16_t addr, uint16_t *data);
	static void			write32(uint16_t addr, uint32_t *data);
};

#endif
