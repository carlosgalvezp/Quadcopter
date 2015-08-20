#ifndef RC_H
#define RC_H

#include <Arduino.h>

#include "Types.h"
#include "HAL.h"

#define NUM_CHANNELS 8

namespace RC
{
	void init();
	void getReadings(RC_data_t * const readings);
}
#endif

