#pragma once
#ifndef MAX7456_H
#define MAX7456_H

#define PIN_MAX7456_SS			6
#define PIN_MAX7456_VSYNC		2

#include <stdint.h>

#include "SPI.h"

#define NVM_SIZE		256

#define CHARACTER_SIZE_W		12
#define CHARACTER_SIZE_H		18

#define SCREEN_SIZE_ROWS		16
#define SCREEN_SIZE_COLS		30

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

// Character address
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
#define CHAR_ADDR_DOT		46
#define CHAR_ADDR_0			48
#define CHAR_ADDR_1			49
#define CHAR_ADDR_2			50
#define CHAR_ADDR_3			51
#define CHAR_ADDR_4			52
#define CHAR_ADDR_5			53
#define CHAR_ADDR_6			54
#define CHAR_ADDR_7			55
#define CHAR_ADDR_8			56
#define CHAR_ADDR_9			57
#define CHAR_ADDR_COLON		58
#define CHAR_ADDR_A_BIG		65
#define CHAR_ADDR_B_BIG		66
#define CHAR_ADDR_C_BIG		67
#define CHAR_ADDR_D_BIG		68
#define CHAR_ADDR_E_BIG		69
#define CHAR_ADDR_F_BIG		70
#define CHAR_ADDR_G_BIG		71
#define CHAR_ADDR_H_BIG		72
#define CHAR_ADDR_I_BIG		73
#define CHAR_ADDR_J_BIG		74
#define CHAR_ADDR_K_BIG		75
#define CHAR_ADDR_L_BIG		76
#define CHAR_ADDR_M_BIG		77
#define CHAR_ADDR_N_BIG		78
#define CHAR_ADDR_O_BIG		79
#define CHAR_ADDR_P_BIG		80
#define CHAR_ADDR_Q_BIG		81
#define CHAR_ADDR_R_BIG		82
#define CHAR_ADDR_S_BIG		83
#define CHAR_ADDR_T_BIG		84
#define CHAR_ADDR_U_BIG		85
#define CHAR_ADDR_V_BIG		86
#define CHAR_ADDR_W_BIG		87
#define CHAR_ADDR_X_BIG		88
#define CHAR_ADDR_Y_BIG		89
#define CHAR_ADDR_Z_BIG		90
#define CHAR_ADDR__		    95
#define CHAR_ADDR_A_SMALL	97
#define CHAR_ADDR_B_SMALL	98
#define CHAR_ADDR_C_SMALL	99
#define CHAR_ADDR_D_SMALL	100
#define CHAR_ADDR_E_SMALL	101
#define CHAR_ADDR_F_SMALL	102
#define CHAR_ADDR_G_SMALL	103
#define CHAR_ADDR_H_SMALL	104
#define CHAR_ADDR_I_SMALL	105
#define CHAR_ADDR_J_SMALL	106
#define CHAR_ADDR_K_SMALL	107
#define CHAR_ADDR_L_SMALL	108
#define CHAR_ADDR_M_SMALL	109
#define CHAR_ADDR_N_SMALL	110
#define CHAR_ADDR_O_SMALL	111
#define CHAR_ADDR_P_SMALL	112
#define CHAR_ADDR_Q_SMALL	113
#define CHAR_ADDR_R_SMALL	114
#define CHAR_ADDR_S_SMALL	115
#define CHAR_ADDR_T_SMALL	116
#define CHAR_ADDR_U_SMALL	117
#define CHAR_ADDR_V_SMALL	118
#define CHAR_ADDR_W_SMALL	119
#define CHAR_ADDR_X_SMALL	120
#define CHAR_ADDR_Y_SMALL	121
#define CHAR_ADDR_Z_SMALL	122
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

	void enableOSD();
	void disableOSD();

	void updateCharSet(uint8_t *data);
	void setChar(uint8_t charAddr, const uint8_t *data);
	void getChar(uint8_t charAddr, uint8_t *data);

	void writeCharToDisplay16(uint16_t displayAddr, uint8_t charAddr);

	void displayCharacter(uint8_t x, uint8_t y, uint8_t charAddr);

	void clearDisplay();
private:

	void init();
	void displaySymbol(uint8_t symbolID, uint16_t posX, uint16_t posY);

	bool isBusy();

	void readSymbolFromNVM(uint8_t symboldID, uint8_t *data);
	void writeSymbolToNVM(uint8_t symbolID, const uint8_t *data);

	uint8_t transferRegister(uint8_t addr, uint8_t data);
};


#endif // MAX7456_H
