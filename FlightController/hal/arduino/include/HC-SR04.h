#ifndef HC_SR04_H
#define HC_SR04_H

#include <stdint.h>
#include "HAL.h"
#include "Utils.h"
#include "Arduino.h"

namespace Sonar
{
    const uint8_t kSonarTriggerTHighUs  = 20U;      // Time in us that the trigger signal is held high
    const uint8_t kSonarSampleFrequency	= 10U;      // Frequency in Hz at which we take sonar measurements
    const float kSoundSpeedCmS_2        = 0.017F;   // Speed of sound, in cm/us, divided by two

	bool getDistance(float& distance);
}

#endif
