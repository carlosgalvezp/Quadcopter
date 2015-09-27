#pragma once

#ifndef EEPROM_H
#define EEPROM_H

#include <stdint.h>
#include <avr\eeprom.h>

// Max EEEPROM SIZE
#define EEPROM_MAX_SIZE_BYTES	4096

// Base address for the EEPROM
#define EEPROM_ADDR_BASE	0x0000

// --- Memory positions for data storage, defined as offsets w.r.t. the base address ---

// PID coefficients (floats, 4 bytes each)
#define EEPROM_OFF_PID_ROLL_KP		0
#define EEPROM_OFF_PID_ROLL_KD		4
#define EEPROM_OFF_PID_ROLL_KI		8
#define EEPROM_OFF_PID_PITCH_KP		12
#define EEPROM_OFF_PID_PITCH_KD		16
#define EEPROM_OFF_PID_PITCH_KI		20
#define EEPROM_OFF_PID_YAW_KP		24
#define EEPROM_OFF_PID_YAW_KD		28
#define EEPROM_OFF_PID_YAW_KI		32

class EEPROM
{
public:
	static uint8_t		read  (uint16_t addr);
	static uint16_t		read16(uint16_t addr);
	static uint32_t		read32(uint16_t addr);

	static void			write  (uint16_t addr, uint8_t data);
	static void			write16(uint16_t addr, uint16_t data);
	static void			write32(uint16_t addr, uint32_t data);
};

#endif
