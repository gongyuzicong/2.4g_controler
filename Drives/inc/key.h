#ifndef __KEY_H__
#define __KEY_H__
#include "stm32f10x.h"
#include "gpio.h"	//ʹ��λ������ǰ���Ȱ�����ͷ�ļ�

#define KEY		GPIOin(GPIOA, 0)	//����PA0��λ��ӳ��

//����ȥ������
#define KEY_JITTER_COUNT	2

//���尴����ֵ
//#define KEY_NONE		0
//#define KEY_CENTER	1

void KEY_Init(void);	//����IO��ʼ��
uint8_t KEY_Scan(uint8_t polling);//����ɨ�躯��

#endif

