#ifndef __USART_H__
#define __USART_H__
#include "stm32f10x.h"

#define COMn			3				//定义STM32支持的串口数	

//定义print从哪个串口输出，如果不使用printf，则注释掉这一行
#define PRINTF_SUPPORT		USART1	
#ifdef PRINTF_SUPPORT
#include <stdio.h>
#endif

#define COM_RX_LEN			128							//串口接收缓冲长度
#if COM_RX_LEN
extern uint16_t COM_RX_STA;							//串口接收状态字
extern uint8_t COM_RX_BUF[COM_RX_LEN];	//串口接收缓冲
#endif

/**
 * @brief 定义COM PORT1，连接到USART1
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
 * @brief 定义COM PORT2，连接到USART2
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
 * @brief 定义COM PORT3，连接到USART3
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

//定义串口端口
typedef enum 
{
	COM1 = 0,
	COM2 = 1,
	COM3 = 2
} COM_TypeDef;

void COM_Init(COM_TypeDef COM, uint32_t BaudRate); //串口初始化

#endif

