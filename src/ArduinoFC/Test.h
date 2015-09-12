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

namespace Test
{
	void testRC();
	void testI2CScan();
	void testSensorRead();
	void testTelemetry(State_data_t * const state);
	void testCompass();
	void testStateEstimation();
	void testOutput();

	void testWholeSystem(State_data_t * const state);

}

#endif
