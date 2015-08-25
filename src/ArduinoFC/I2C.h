#ifndef I2C_H
#define I2C_H

#include <stdint.h>
#include <stdlib.h>
#include "Arduino.h"

#include "HAL.h"

//#define I2C_DEBUG							

#define I2C_FREQUENCY						400000L
	
#define I2C_STATE_START						0x08
#define I2C_STATE_REPEATED_START			0X10
#define I2C_STATE_SLA_W_ACK					0X18
#define I2C_STATE_SLA_W_NACK			    0x20
#define I2C_STATE_DATA_W_ACK				0x28
#define I2C_STATE_DATA_W_NACK				0x30
#define I2C_STATE_ARBITRATION_LOST			0x38
#define I2C_STATE_SLA_R_ACK					0X40
#define I2C_STATE_SLA_R_NACK				0x48
#define I2C_STATE_DATA_R_ACK				0x50
#define I2C_STATE_DATA_R_NACK				0x58

#define I2C_TWSR_READ_MASK					0xF8

#define I2C_MODE_READ						1
#define I2C_MODE_WRITE						0

#define I2C_READ_SEND_ACK					1
#define I2C_READ_SEND_NACK					0


namespace I2C
{
	void init();
	uint8_t writeReg(uint8_t dev_address, uint8_t reg, const uint8_t * const data, size_t n_bytes);
	uint8_t readReg(uint8_t dev_address, uint8_t reg, uint8_t * const data, size_t n_bytes);

	uint8_t writeByte(uint8_t data);
	uint8_t readByte(uint8_t * const data, uint8_t read_ack);

	uint8_t startCondition();
	uint8_t slaPlusM(uint8_t dev_address, uint8_t mode);
	uint8_t stopCondition();

	uint8_t waitUntilReady();
	uint8_t checkTWSR();
}

#endif
