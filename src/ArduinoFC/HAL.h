#ifndef HAL_H
#define HAL_H

#include <Arduino.h>

// ** Definitions ** 
// PINs
#define PIN_BUZZER

#define PIN_LED_A			13
#define PIN_LED_B			31
#define PIN_LED_C			30

#define PIN_M1
#define PIN_M2
#define PIN_M3
#define PIN_M4

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



//

namespace HAL
{
	void init();
	void initGPIO();
	void initRCInterrupts();
}
#endif