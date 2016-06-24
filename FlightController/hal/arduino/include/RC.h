#ifndef RC_H
#define RC_H

#include <avr/io.h>
#include <avr/interrupt.h>

#include "Types.h"
#include "HAL.h"

#define NUM_CHANNELS	8
#define RC_MIN_IN		1200
#define RC_MAX_IN		1800
#define RC_IDDLE_IN		1500
#define RC_EPS			100
#define RC_RANGE_MIN	900
#define RC_RANGE_MAX    2100

#define RC_isValid(x)		(x > RC_RANGE_MIN && x < RC_RANGE_MAX)
#define RC_isAtMax(x)		(x > RC_MAX_IN)
#define RC_isAtMin(x)		(x < RC_MIN_IN)
#define RC_isIddle(x)		((abs(x) - RC_IDDLE_IN) < RC_EPS)

namespace RC
{
	void getReadings(RCData* const readings);
}

#endif

