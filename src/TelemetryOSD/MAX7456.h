#pragma once
#ifndef MAX7456_H
#define MAX7456_H

#include <stdint.h>

#include "SPI.h"

#define PIN_MAX7456_SS			6
#define PIN_MAX7456_VSYNC		2

#define PIN_MAX7456_SS_PORT_BIT	6

#define max7456_ss_high()		PORTD |=  (1 << PIN_MAX7456_SS_PORT_BIT)
#define max7456_ss_low()		PORTD &= ~(1 << PIN_MAX7456_SS_PORT_BIT)

#define NVM_SIZE		256

#define CHARACTER_SIZE_W		12
#define CHARACTER_SIZE_H		18

#define SCREEN_SIZE_ROWS		16
#define SCREEN_SIZE_COLS		30

#define MAX7456_V_OFFSET		10	// [pixels]
#define MAX7456_H_OFFSET		10	// [pixels]

// NVM
#define OSD_CHAR_SIZE_BYTES		54

// ** Registers (_W stands for Write, _R for read)
#define VM0_W		0x00
#define VM1_W		0x01
#define HOS_W		0X02
#define VOS_W		0X03
#define DMM_W		0x04
#define DMAH_W		0x05
#define DMAL_W		0x06
#define DMDI_W		0x07
#define CMM_W		0x08
#define CMAH_W		0x09
#define CMAL_W		0x0A
#define CMDI_W		0x0B
#define OSDM_W		0x0C
#define RB0_W		0x10
#define RB1_W		0x11
#define RB2_W		0x12
#define RB3_W		0x13
#define RB4_W		0x14
#define RB5_W		0x15
#define RB6_W		0x16
#define RB7_W		0x17
#define RB8_W		0x18
#define RB9_W		0x19
#define RB10_W		0x1A
#define RB11_W		0x1B
#define RB12_W		0x1C
#define RB13_W		0x1D
#define RB14_W		0x1E
#define RB15_W		0x1F
#define OSDBL_W		0x6C

#define VM0_R		0x80
#define VM1_R		0x81
#define HOS_R		0x82
#define VOS_R		0x83
#define DMM_R		0x84
#define DMAH_R		0x85
#define DMAL_R		0x86
#define DMDI_R		0x87
#define CMM_R		0x88
#define CMAH_R		0x89
#define CMAL_R		0x8A
#define CMDI_R		0x8B
#define OSDM_R		0x8C
#define RB0_R		0x90
#define RB1_R		0x91
#define RB2_R		0x92
#define RB3_R		0x93
#define RB4_R		0x94
#define RB5_R		0x95
#define RB6_R		0x96
#define RB7_R		0x97
#define RB8_R		0x98
#define RB9_R		0x99
#define RB10_R		0x9A
#define RB11_R		0x9B
#define RB12_R		0x9C
#define RB13_R		0x9D
#define RB14_R		0x9E
#define RB15_R		0x9F
#define OSDBL_R		0xEC

#define STAT_R		0xA0
#define DMDO_R		0xB0
#define CMDO_R		0xC0

// Special character address. For letters and numbers
// the address is the same as the ASCII number
#define CHAR_ADDR_EMPTY		0
#define CHAR_ADDR_2D		1
#define CHAR_ADDR_3D		2
#define CHAR_ADDR_BAR_1     5
#define CHAR_ADDR_BAR_2     6
#define CHAR_ADDR_BAR_3     7
#define CHAR_ADDR_BAR_4     8
#define CHAR_ADDR_BAR_5     9
#define CHAR_ADDR_BAR_6     10
#define CHAR_ADDR_BAR_7     11
#define CHAR_ADDR_BAR_8     12
#define CHAR_ADDR_BAR_9     13
#define CHAR_ADDR_BAR_10    14
#define CHAR_ADDR_GPS		15
#define CHAR_ADDR_UNLOCK	16
#define CHAR_ADDR_LOCK		17
#define CHAR_ADDR_FIX		23
#define CHAR_ADDR_HOUSE		31
#define CHAR_ADDR_KMH		129
#define CHAR_ADDR_LAT		131
#define CHAR_ADDR_LON		132
#define CHAR_ADDR_ALT		134
#define CHAR_ADDR_VEL		135

// ---> To avoid artifacts, it's good to write to image when VSYNC = 0(interrupt)
class MAX7456
{
public:
	MAX7456();
	~MAX7456();

	void init();

	void enableOSD();
	void disableOSD();

	void writeSymbolToNVM(uint8_t charAddr, const uint8_t *data);
	void readSymbolFromNVM(uint8_t charAddr, uint8_t *data);

	void writeCharToDisplay16(uint16_t displayAddr, uint8_t charAddr);

	void displayCharacter(uint8_t x, uint8_t y, uint8_t charAddr);

	void clearDisplay();
private:

	void displaySymbol(uint8_t symbolID, uint16_t posX, uint16_t posY);
	bool isBusy();
	
	void writeToRegister(uint8_t addr, uint8_t data);
	uint8_t readRegister(uint8_t addr);
};


#endif // MAX7456_H
