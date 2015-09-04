#ifndef HAL_H
#define HAL_H

#include <Arduino.h>
#include <avr/io.h>
#include "I2C.h"
#include "MPU6050.h"
#include "HMC5883L.h"
#include "MS5611.h"

// ** Definitions ** 
#define CPU_FREQUENCY		16000000L	// Hz
#define ESC_FREQUENCY		400			// Hz

// PINs
#define PIN_BUZZER

#define PIN_LED_A			13
#define PIN_LED_B			31
#define PIN_LED_C			30

// RX pins are connected to Port K (PCINT16:23). 
// These numbers represent the pin within the port
#define PIN_RC_THROTTLE		0	// Equals to A8
#define PIN_RC_AILERON		1   // Equals to A9
#define PIN_RC_ELEVATOR		2   // Equals to A10
#define PIN_RC_RUDDER		3   // Equals to A11
#define PIN_RC_AUX1			4   // Equals to A12
#define PIN_RC_AUX2			5   // Equals to A13
#define PIN_RC_AUX3			6   // Equals to A13
#define PIN_RC_AUX4			7   // Equals to A13


// Motor pins
#define PIN_M1				PE4		
#define PIN_M2				PE5		
#define PIN_M3				PE3		
#define PIN_M4				PH3		
#define PIN_M5				PH4		
#define PIN_M6				PH5		
#define PIN_M7				PH6		
#define PIN_M8				PB0

// Motor control registers
#define OUT_M1				OCR3B
#define OUT_M2				OCR3C
#define OUT_M3				OCR3A
#define OUT_M4				OCR4A
#define OUT_M5				OCR4B
#define OUT_M6				OCR4C

namespace HAL
{
	void init();
	void initGPIO();
	void initRC();
	void initMotors();
}
#endif