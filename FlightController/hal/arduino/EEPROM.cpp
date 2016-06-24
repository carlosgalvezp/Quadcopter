#include "EEPROM.h"


void EEPROM::loadConfig(Config* config)
{
	config->pid_roll.kp = EEPROM::readFloat(EEPROM_ADDR_PID_ROLL_KP);
	config->pid_roll.kd = (float)EEPROM::read32(EEPROM_ADDR_PID_ROLL_KD);
	config->pid_roll.ki = (float)EEPROM::read32(EEPROM_ADDR_PID_ROLL_KI);

	config->pid_pitch.kp = (float)EEPROM::read32(EEPROM_ADDR_PID_PITCH_KP);
	config->pid_pitch.kd = EEPROM::readFloat(EEPROM_ADDR_PID_PITCH_KD);
	config->pid_pitch.ki = (float)EEPROM::read32(EEPROM_ADDR_PID_PITCH_KI);

    config->pid_yaw.kp = (float)EEPROM::read32(EEPROM_ADDR_PID_YAW_KP);
	config->pid_yaw.kd = (float)EEPROM::read32(EEPROM_ADDR_PID_YAW_KD);
	config->pid_yaw.ki = (float)EEPROM::read32(EEPROM_ADDR_PID_YAW_KI);
}

void EEPROM::storeConfig(const Config* config)
{
	// PID configuration
	EEPROM::write32(EEPROM_ADDR_PID_ROLL_KP, (uint32_t *) &config->pid_roll.kp);
	EEPROM::write32(EEPROM_ADDR_PID_ROLL_KD, (uint32_t *) &config->pid_roll.kd);
	EEPROM::write32(EEPROM_ADDR_PID_ROLL_KI, (uint32_t *) &config->pid_roll.ki);

	EEPROM::write32(EEPROM_ADDR_PID_PITCH_KP, (uint32_t *) &config->pid_pitch.kp);
	EEPROM::write32(EEPROM_ADDR_PID_PITCH_KD, (uint32_t *) &config->pid_pitch.kd);
	EEPROM::write32(EEPROM_ADDR_PID_PITCH_KI, (uint32_t *) &config->pid_pitch.ki);

	EEPROM::write32(EEPROM_ADDR_PID_YAW_KP, (uint32_t *) &config->pid_yaw.kp);
	EEPROM::write32(EEPROM_ADDR_PID_YAW_KD, (uint32_t *) &config->pid_yaw.kd);
	EEPROM::write32(EEPROM_ADDR_PID_YAW_KI, (uint32_t *) &config->pid_yaw.ki);
}

void EEPROM::clear()
{
	for (uint16_t i = 0; i < EEPROM_MAX_SIZE_BYTES; ++i)
	{
		EEPROM::write(i, 0x00);
	}
}

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

float EEPROM::readFloat(uint16_t addr)
{
	u_float_u32 dataUnion;
	dataUnion.xu = EEPROM::read32(addr);

	return dataUnion.xf;
}

void EEPROM::write(uint16_t addr, uint8_t data)
{
	return eeprom_write_byte((uint8_t *) addr, data);
}

void EEPROM::write16(uint16_t addr, uint16_t *data)
{
	write(addr    , (uint8_t)(((*data & 0xFF00) >> 8) & 0x00FF));
	write(addr + 1, (uint8_t)(((*data & 0x00FF)     ) & 0x00FF));
}


void EEPROM::write32(uint16_t addr, uint32_t *data)
{
	write(addr,     (uint8_t)(((*data & 0xFF000000) >> 24) & 0x000000FF));
	write(addr + 1, (uint8_t)(((*data & 0x00FF0000) >> 16) & 0x000000FF));
	write(addr + 2, (uint8_t)(((*data & 0x0000FF00) >>  8) & 0x000000FF));
	write(addr + 3, (uint8_t)(((*data & 0x000000FF)      ) & 0x000000FF));
}
