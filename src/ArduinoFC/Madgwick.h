#ifndef MADGWICK_H
#define MADGWICK_H

#include <math.h>

#include "Utils.h"

#define samplePeriod	0.01		// sample period, in seconds
#define betaDef			0.1f		// 2 * proportional gain

namespace Madgwick
{
	// Function declarations
	void AHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
}

#endif
