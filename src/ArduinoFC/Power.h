#pragma once
#ifndef POWER_H
#define POWER_H

#include <stdint.h>

namespace Power
{
	bool readVoltage(uint16_t *voltage);
	bool readCurrent(uint16_t *current);
}

#endif

