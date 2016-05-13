#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#include "stm32f10x.h"

#define KEY_NONE			0
#define KEY_CENTER 			1
#define KEY_UP				2
#define KEY_LEFT			3
#define KEY_DOWN			4
#define KEY_RIGHT			5

void JoyStick_Init(void);//“°∏À≥ı ºªØ
uint8_t JoyStick_Scan(uint8_t polling);  	//“°∏À…®√Ë	


#endif

