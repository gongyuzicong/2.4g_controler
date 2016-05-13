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
	RCC_Init();					//RCC初始化
	LED_Init();					//LED IO初始化
	COM_Init(COM1, 115200);		//USART1初始化
	OLED_Init();				//OLED初始化
	ADC_Initialize();			//ADC初始化
	JoyStick_Init();			//摇杆按键JoyStick初始化
	My_NRF24L01_Init();
	
	
	/* Infinite loop */
	while (1)
	{
		joystickScan_Send_NRF();
		
		//LED_Toggle();	//LED状态反转
		
		//delay_ms(250);		//延时250ms
	}

}

