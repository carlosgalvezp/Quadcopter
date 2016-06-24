#pragma once

#ifndef HC_SR04_H
#define HC_SR04_H

#include <stdint.h>
#include "HAL.h"
#include "Utils.h"
#include "Arduino.h"

#define SONAR_T_TRIGGER_HIGH_US		20		// Time in us that the trigger signal is held high
#define SONAR_FREQUENCY				10		// Frequency in Hz at which we take sonar measurements 
#define SOUND_SPEED_CM_US_2			0.017f	// Speed of sound, in cm/us, divided by two

namespace Sonar
{
	bool getDistance(float& distance);
}

#endif