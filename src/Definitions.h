#ifndef __B100BC_Definitions__
#define __B100BC_Definitions__

	// Include Arduino Library
	#ifndef __Arduino__
		#include <Arduino.h>
	#endif

	// Define LED Colors
	#define	__WHITE__					0
	#define	__RED__						1
	#define	__GREEN__					2
	#define	__BLUE__					3
	#define	__PURPLE__					4

	// Define Relay States
	#define	__START__					1
	#define	__STOP__					2
	#define	__ALARM__					3
	#define	__STOP_LOCK__				4
	#define	__STOP_UNLOCK__				5

	// EEPROM Address Table
	#define EEPROM_Online_Interval		0x00
	#define EEPROM_Offline_Interval		0x02
	#define EEPROM_Alarm_Duration		0x04
	#define EEPROM_V_Min				0x0A
	#define EEPROM_V_Max				0x0C
	#define EEPROM_I_Max				0x0E
	#define EEPROM_FQ_Min				0x10
	#define EEPROM_FQ_Max				0x12
	#define EEPROM_VIMB_Max				0x14
	#define EEPROM_IIMB_Max				0x16
	#define EEPROM_P_Regression			0x1E
	#define EEPROM_PMAX					0x20
	#define EEPROM_Current_Ratio		0x28
	#define EEPROM_Fault_Control		0x2A

	#define Terminal_BLACK				(uint8_t)30
	#define Terminal_RED				(uint8_t)31
	#define Terminal_GREEN				(uint8_t)32
	#define Terminal_YELLOW				(uint8_t)33
	#define Terminal_BLUE				(uint8_t)34
	#define Terminal_MAGENTA			(uint8_t)35
	#define Terminal_CYAN				(uint8_t)36
	#define Terminal_WHITE				(uint8_t)37
	#define Terminal_GRAY				(uint8_t)90

	// Text Format Definitions
	#define Terminal_RST				(uint8_t)0
	#define Terminal_BRIGHT				(uint8_t)1
	#define Terminal_DIM				(uint8_t)2
	#define Terminal_UNDERSCORE			(uint8_t)4
	#define Terminal_BLINK				(uint8_t)5
	#define Terminal_REVERSE			(uint8_t)7
	#define Terminal_HIDDEN				(uint8_t)8

#endif