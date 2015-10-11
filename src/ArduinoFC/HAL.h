#ifndef HAL_H
#define HAL_H

#include <Arduino.h>
#include <avr/io.h>
#include "I2C.h"
#include "MPU6050.h"
#include "HMC5883L.h"
#include "MS5611.h"
#include "HC-SR04.h"
#include "GPIO.h"
#include "Config.h"

// ** Definitions ** 
#define CPU_FREQUENCY		16000000L	// Hz
#define ESC_FREQUENCY		400			// Hz
#define TELEMETRY_BAUDRATE	115200		// baud

// PINs
#define PIN_LED_RED				13
#define PIN_LED_BLUE			31
#define PIN_LED_GREEN			30

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

// Motor control registers
#define OUT_M1				OCR3B
#define OUT_M2				OCR3C
#define OUT_M3				OCR3A
#define OUT_M4				OCR4A

// Sonar
#define PIN_SONAR_TRIGGER		PB5
#define PIN_SONAR_ECHO			PB4
#define SONAR_INT_NUMBER		PCINT4
#define SONAR_CLOCK_PRESCALER	64

// LEDS and Buzzer
#define PIN_LEDS_BODY			A6 
#define PIN_BUZZER				A7

// Serial Ports
#define Serial_Telemetry		Serial
#define Serial_GPS				Serial1
#define Serial_Debug			Serial3

namespace HAL
{
	void init();
	void initGPIO();
	void initRC();
	void initMotors();
	void initSonar();
	void initADC();
}
#endif