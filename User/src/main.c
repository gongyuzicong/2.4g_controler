#include "stm32f10x.h"
#include "rcc.h"
#include "led.h"
#include "usart.h"
#include "key.h"
#include "delay.h"
#include "oled.h"
#include "adc.h"
#include "joystick.h"
#include "nrf24l01.h"
#include "spi.h"
#include "exti.h"
#include "my_operator.h"


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
	RCC_Init();					//RCC��ʼ��
	LED_Init();					//LED IO��ʼ��
	COM_Init(COM1, 115200);		//USART1��ʼ��
	OLED_Init();				//OLED��ʼ��
	ADC_Initialize();			//ADC��ʼ��
	JoyStick_Init();			//ҡ�˰���JoyStick��ʼ��
	My_NRF24L01_Init();
	
	
	/* Infinite loop */
	while (1)
	{
		joystickScan_Send_NRF();
		
		//LED_Toggle();	//LED״̬��ת
		
		//delay_ms(250);		//��ʱ250ms
	}

}

