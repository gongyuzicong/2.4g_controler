#ifndef __LED_H__
#define __LED_H__

#include "common_include.h"
#include "stm32f10x.h"
#include "gpio.h"


#define uLED	PBout(12)
#define uLED_T	PB_PIN_Toggle(12)

void LED_Init(void);	//LED IO初始化
void LED_On(void);		//LED亮
void LED_Off(void);		//LED灭
void LED_Toggle(void);//LED状态反转

#endif

