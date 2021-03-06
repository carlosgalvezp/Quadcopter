#ifndef TEST_H
#define TEST_H

#include "Arduino.h"

#include "Types.h"
#include "RC.h"
#include "HAL.h"
#include "I2C.h"
#include "state_estimation/StateEstimation.h"
#include "Telemetry.h"
#include "Output.h"
#include "control/Control.h"
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
	void testTelemetry(State& state, Config& config);
	void testCompass();
	void testStateEstimation();
	void testOutput();
	void testADC();
	void testSonar();
	void testGPS();
	void testSoftPWM();

	namespace Unit
	{
		void testEEPROM();
		void testAtan2Full(); 
		void testAtan2();
		void testCos();
		void testSin();
		void testAsin();
		void testAcos();

		void testQuaternionToRPY();
	}

	namespace Performance
	{
		void testSin();
		void testAsin();
	}
}


#endif
