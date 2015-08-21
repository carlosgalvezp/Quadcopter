#ifndef MS5611_H
#define MS5611_H

#include <stdint.h>

#define BARO_DEV_ADDR		0x77
namespace Barometer
{
	void init();
	void getData(float * const data);
}
#endif