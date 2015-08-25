#ifndef TEST_H
#define TEST_H

#include "Arduino.h"

#include "Types.h"
#include "RC.h"
#include "HAL.h"
#include "I2C.h"
#include "StateEstimation.h"
#include "Telemetry.h"

namespace Test
{
	void testRC();
	void testI2CScan();
	void testSensorRead();
	void testTelemetry();
	void testCompass();
	void testStateEstimation();

	void testWholeSystem();

}

#endif
