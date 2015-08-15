#ifndef RC_H
#define RC_H

#include <Arduino.h>

#include "Types.h"
#include "HAL.h"

#define NUM_CHANNELS 8

namespace RC
{
	void init();
	void getReadings(RCReadings_t * const readings);
}
#endif

