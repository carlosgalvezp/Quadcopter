#ifndef MS5611_H
#define MS5611_H

#include <stdint.h>

#define BARO_DEV_ADDR		0x77 << 1
namespace Barometer
{
	void getData(uint16_t * const data);
}
#endif