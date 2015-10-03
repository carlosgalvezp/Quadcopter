#ifndef TEST_H
#define TEST_H

#include "Arduino.h"

#include "Types.h"
#include "RC.h"
#include "HAL.h"
#include "I2C.h"
#include "StateEstimation.h"
#include "Telemetry.h"
#include "Output.h"
#include "Control.h"
#include "EEPROM.h"
#include "ADC.h"
#include "SoftPWM.h"
#include "GPIO.h"

namespace Test
{
	void run();
	void testRC();
	void testI2CScan();
	void testSensorRead();
	void testTelemetry(State_t * const state, Config_t * const config);
	void testCompass();
	void testStateEstimation();
	void testOutput();
	void testADC();
	void testSonar();
	void testSoftPWM();

	namespace Unit
	{
		void testEEPROM();
		void testAtan2Full(); 
		void testAtan2();

		void testQuaternionToRPY();
	}
}

#endif
