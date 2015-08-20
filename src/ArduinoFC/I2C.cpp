#include "I2C.h"
#include "Arduino.h"

void I2C::init()
{
	// Enable pull-ups
	PORTD |= (1 << 0) | (1 << 1);

	// Disable power reduction
	PRR0 &= ~(1 << PRTWI);

	// Set I2C speed
	TWSR &= 0b11111100;		// TWSP = 0 -> Prescaler = 1
	TWBR = ((CPU_FREQUENCY / I2C_FREQUENCY) - 16) / 2;

	// No interruptions (we poll TWINT)
	TWCR &= ~(1 << TWIE);
}

uint8_t I2C::startCondition()
{
	// Send start
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	// Wait for TWINT flag
	I2C::waitUntilReady();

	// Check for correct status on the bus
	uint8_t twsr = checkTWSR();
	if (twsr != I2C_STATE_START && twsr != I2C_STATE_REPEATED_START)
	{
		#ifdef I2C_DEBUG 
			Serial.println("Start condition failed"); 
		#endif
		return 1;
	}
#ifdef I2C_DEBUG
	Serial.println("Start condition OK");
#endif
	return 0;
}

uint8_t I2C::stopCondition()
{
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
	return 0;
}

uint8_t I2C::slaPlusM(uint8_t dev_addr, uint8_t mode)
{
	// Put device address + mode into TWDR
	TWDR = dev_addr << 1 | mode;

	// Clear TWINT
	TWCR = (1 << TWINT) | (1 << TWEN);

	// Wait for TWINT flag
	I2C::waitUntilReady();

	// Check status code
	uint8_t status = checkTWSR();
	switch (status)
	{
		case I2C_STATE_SLA_W_ACK:
#ifdef I2C_DEBUG
			Serial.println("Transmitted SLA+W, received ACK");
#endif
			return 0;

		case I2C_STATE_SLA_W_NACK:
#ifdef I2C_DEBUG
			Serial.println("Transmitted SLA+W, but received NACK");
#endif
			return 1;

		case I2C_STATE_SLA_R_ACK:
#ifdef I2C_DEBUG
			Serial.println("Transmitted SLA+R, received ACK");
#endif
			return 0;
		case I2C_STATE_SLA_R_NACK:
#ifdef I2C_DEBUG
			Serial.println("Transmitted SLA+R, received NACK");
#endif
			return 1;

		case I2C_STATE_ARBITRATION_LOST:
#ifdef I2C_DEBUG
			Serial.println("Transmitted SLA+W, but arbitration lost");
#endif
			return 1;
		default:
#ifdef I2C_DEBUG
			Serial.println("Transmitted SLA+W, unknown state");
#endif
			return 1;
	}
}

uint8_t I2C::writeByte(uint8_t data)
{	
	// Put data on TWDR
	TWDR = data;

	// Clear TWINT to transmit 
	TWCR = (1 << TWINT) | (1 << TWEN);

	// Wait for TWINT flag
	I2C::waitUntilReady();

	// Check status
	switch (I2C::checkTWSR())
	{
		case I2C_STATE_DATA_W_ACK:
#ifdef I2C_DEBUG
			Serial.println("Data write, received ACK");
#endif
			return 0;
		case I2C_STATE_DATA_W_NACK:
#ifdef I2C_DEBUG
			Serial.println("Data write, received NACK");
#endif
			return 1;
		default:
#ifdef I2C_DEBUG
			Serial.println("Data write, unknown state");
#endif
			return 1;
	}
}

uint8_t I2C::readByte(uint8_t * const data, uint8_t read_ack)
{
	// Clear TWINT and send NACK by setting TWEA to 1
	TWCR = (1 << TWINT) | (read_ack << TWEA) | (1 << TWEN);

	// Wait until ready and check status
	I2C::waitUntilReady();

	// Read data
	*data = TWDR;

	if (read_ack == I2C_READ_SEND_ACK)
	{
		if (I2C::checkTWSR() != I2C_STATE_DATA_R_ACK)
		{
#ifdef I2C_DEBUG
			Serial.println("Read byte, sent ACK, but something failed");
#endif
			return 1;
		}
#ifdef I2C_DEBUG
		Serial.println("Read byte, sent ACK");
#endif
		return 0;
	}
	else if (read_ack == I2C_READ_SEND_NACK)
	{
		if (I2C::checkTWSR() != I2C_STATE_DATA_R_NACK)
		{
#ifdef I2C_DEBUG
			Serial.println("Read byte, sent NACK, but something failed");
#endif
			return 1;
		}
#ifdef I2C_DEBUG
		Serial.println("Read byte, sent NACK");
#endif
		return 0;
	}
	return 1;
}

uint8_t I2C::writeReg(uint8_t dev_address, uint8_t reg, const uint8_t * const data, size_t n_bytes)
{

	// Start
	if(I2C::startCondition()) return 1;
	if(I2C::slaPlusM(dev_address, I2C_MODE_WRITE)) return 1 ;
	
	// Write register we want to modify
	if (I2C::writeByte(reg)) return 1;

	// Write data to the register
	for (size_t i = 0; i < n_bytes; ++i)
	{
		if(I2C::writeByte(data[i])) return 1;
	}

	if(I2C::stopCondition()) return 1;

	return 0;
}

uint8_t I2C::readReg(uint8_t dev_address, uint8_t reg, uint8_t * data, size_t n_bytes)
{
	// Start
	if(I2C::startCondition()) return 1;

	// Write register that we want to read
	if(I2C::slaPlusM(dev_address, I2C_MODE_WRITE)) return 1;
	if(I2C::writeByte(reg)) return 1;

	// Repeated start condition
	if(I2C::startCondition()) return 1;
	if(I2C::slaPlusM(dev_address, I2C_MODE_READ)) return 1;

	// Read all but the last bytes, sending ACK
	for (size_t i = 0; i < n_bytes - 1; ++i)
	{
		if(I2C::readByte(data + i, I2C_READ_SEND_ACK)) return 1;
	}

	// Read last one sending NACK
	if(I2C::readByte(data + n_bytes - 1, I2C_READ_SEND_NACK)) return 1;

	// Stop
	if(I2C::stopCondition()) return 1;

	return 0;
}


uint8_t I2C::waitUntilReady()
{
	uint8_t counter = -1; // Will be the maximum value
	while (!(TWCR & (1 << TWINT)) && counter -- > 0);

	return (counter == 0);  // Timeout
}

uint8_t I2C::checkTWSR()
{
	return TWSR & I2C_TWSR_READ_MASK;
}