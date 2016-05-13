#ifndef __KEY_H__
#define __KEY_H__
#include "stm32f10x.h"
#include "gpio.h"	//使用位带操作前，先包含此头文件

#define KEY		GPIOin(GPIOA, 0)	//定义PA0的位带映射

//按键去抖次数
#define KEY_JITTER_COUNT	2

//定义按键码值
//#define KEY_NONE		0
//#define KEY_CENTER	1

void KEY_Init(void);	//按键IO初始化
uint8_t KEY_Scan(uint8_t polling);//按键扫描函数

#endif

