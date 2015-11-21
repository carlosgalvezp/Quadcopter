#pragma once
#ifndef TEST_H
#define TEST_H

#include "MAX7456.h"
#include "defines.h"

namespace Test
{
	void testReadStatus();
	void testReadCharacter();

	void testDisplayText();
}

#endif // TEST_H
