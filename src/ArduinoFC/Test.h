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

namespace Test
{
	void testRC();
	void testI2CScan();
	void testSensorRead();
	void testTelemetry(State_data_t * const state);
	void testCompass();
	void testStateEstimation();
	void testOutput();
	void testSonar();

	void testWholeSystem(State_data_t * const state);

	namespace Unit
	{
		void testEEPROM();
		void testAtan2Full(); 
		void testAtan2();

		void testQuaternionToRPY();
	}
}

#endif
