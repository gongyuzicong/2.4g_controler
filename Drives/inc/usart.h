#ifndef __USART_H__
#define __USART_H__
#include "stm32f10x.h"

#define COMn			3				//����STM32֧�ֵĴ�����	

//����print���ĸ���������������ʹ��printf����ע�͵���һ��
#define PRINTF_SUPPORT		USART1	
#ifdef PRINTF_SUPPORT
#include <stdio.h>
#endif

#define COM_RX_LEN			128							//���ڽ��ջ��峤��
#if COM_RX_LEN
extern uint16_t COM_RX_STA;							//���ڽ���״̬��
extern uint8_t COM_RX_BUF[COM_RX_LEN];	//���ڽ��ջ���
#endif

/**
 * @brief ����COM PORT1�����ӵ�USART1
 */ 
#define STM_COM1					USART1
#define STM_COM1_CLK				RCC_APB2Periph_USART1
#define STM_COM1_TX_PIN				GPIO_Pin_9
#define STM_COM1_TX_GPIO_PORT		GPIOA
#define STM_COM1_TX_GPIO_CLK		RCC_APB2Periph_GPIOA
#define STM_COM1_RX_PIN				GPIO_Pin_10
#define STM_COM1_RX_GPIO_PORT		GPIOA
#define STM_COM1_RX_GPIO_CLK		RCC_APB2Periph_GPIOA
#define STM_COM1_IRQn				USART1_IRQn

/**
 * @brief ����COM PORT2�����ӵ�USART2
 */ 
#define STM_COM2					USART2
#define STM_COM2_CLK				RCC_APB1Periph_USART2
#define STM_COM2_TX_PIN				GPIO_Pin_2
#define STM_COM2_TX_GPIO_PORT		GPIOA
#define STM_COM2_TX_GPIO_CLK		RCC_APB2Periph_GPIOA
#define STM_COM2_RX_PIN				GPIO_Pin_3
#define STM_COM2_RX_GPIO_PORT		GPIOA
#define STM_COM2_RX_GPIO_CLK		RCC_APB2Periph_GPIOA
#define STM_COM2_IRQn				USART2_IRQn

/**
 * @brief ����COM PORT3�����ӵ�USART3
 */ 
#define STM_COM3					USART3
#define STM_COM3_CLK				RCC_APB1Periph_USART3
#define STM_COM3_TX_PIN				GPIO_Pin_10
#define STM_COM3_TX_GPIO_PORT		GPIOB
#define STM_COM3_TX_GPIO_CLK		RCC_APB2Periph_GPIOB
#define STM_COM3_RX_PIN				GPIO_Pin_11
#define STM_COM3_RX_GPIO_PORT		GPIOB
#define STM_COM3_RX_GPIO_CLK		RCC_APB2Periph_GPIOB
#define STM_COM3_IRQn				USART3_IRQn

//���崮�ڶ˿�
typedef enum 
{
	COM1 = 0,
	COM2 = 1,
	COM3 = 2
} COM_TypeDef;

void COM_Init(COM_TypeDef COM, uint32_t BaudRate); //���ڳ�ʼ��

#endif

