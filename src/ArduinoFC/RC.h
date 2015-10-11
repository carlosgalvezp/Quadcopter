#ifndef RC_H
#define RC_H

#include <avr/io.h>
#include <avr/interrupt.h>

#include "Types.h"
#include "HAL.h"

#define NUM_CHANNELS 8
#define RC_MIN_IN	 1200
#define RC_MAX_IN	 1800
#define RC_IDDLE_IN  1500
#define RC_EPS		 100

#define RC_isValid(x)		(x > 0)
#define RC_isAtMax(x)		(RC_isValid(x) && x > RC_MAX_IN)
#define RC_isAtMin(x)		(RC_isValid(x) && x < RC_MIN_IN)
#define RC_isIddle(x)		(RC_isValid(x) && (abs(x) - RC_IDDLE_IN) < RC_EPS)

namespace RC
{
	void getReadings(RC_data_t * const readings);
}
#endif

