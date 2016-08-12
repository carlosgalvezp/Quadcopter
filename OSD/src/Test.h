#pragma once
#ifndef TEST_H
#define TEST_H

#include "OSD.h"
#include "defines.h"

namespace Test
{
	void main(OSD &osd);

	namespace Internal
	{
		void testReadStatus();
		void testReadCharacter(OSD &osd);
		void testDisplayText(OSD &osd);

		void displayOSDSymbol(const uint8_t *data);
	}
}

#endif // TEST_H
