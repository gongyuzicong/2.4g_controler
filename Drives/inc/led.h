#ifndef __LED_H__
#define __LED_H__

#include "common_include.h"
#include "stm32f10x.h"
#include "gpio.h"


#define uLED	PBout(12)
#define uLED_T	PB_PIN_Toggle(12)

void LED_Init(void);	//LED IO��ʼ��
void LED_On(void);		//LED��
void LED_Off(void);		//LED��
void LED_Toggle(void);//LED״̬��ת

#endif

