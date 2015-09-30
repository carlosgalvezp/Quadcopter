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

namespace Test
{
	void testRC();
	void testI2CScan();
	void testSensorRead();
	void testTelemetry(State_data_t * const state, Config * const config);
	void testCompass();
	void testStateEstimation();
	void testOutput();
	void testADC();
	void testSonar();

	void testWholeSystem(State_data_t * const state, Config * const config);

	namespace Unit
	{
		void testEEPROM();
		void testAtan2Full(); 
		void testAtan2();

		void testQuaternionToRPY();
	}
}

#endif
