#include "my_operator.h"
#include "joystick.h"
#include "adc.h"
#include "oled.h"
#include "delay.h"
#include "nrf24l01.h"
#include "exti.h"
#include "spi.h"

void joystickScan_View(void)
{
	uint16_t AdcValue;
	float Voltage;
	uint8_t key;
	static uint8_t ciri = 0, cirj = 0;
	
	key = (JoyStick_Scan(0));
	
	
	if(key)
	{
		ciri = 0;
		
		AdcValue = Get_Adc_Average(ADC1, ADC_Channel_0);	//读取摇杆的ADC值
		OLED_ShowxNum(32, 16, AdcValue, 3, 16, 0x03);		//显示ADC的值
		Voltage = (float)AdcValue * (3.3 / 4096);
		AdcValue = Voltage;
		OLED_ShowxNum(64, 16, AdcValue, 1, 16, 0x01);		//显示电压值
		Voltage -= AdcValue;
		Voltage *= 1000;
		OLED_ShowxNum(80, 16, Voltage, 3, 16, 0x81);
		
		switch(key)
		{
			case KEY_CENTER:
				OLED_ShowString(0, 32, "KEY_CENTER");
				break;
			case KEY_UP:
				OLED_ShowString(0, 32, "KEY_UP    ");
				break;
			case KEY_LEFT:
				OLED_ShowString(0, 32, "KEY_LEFT  ");
				break;
			case KEY_DOWN:
				OLED_ShowString(0, 32, "KEY_DOWN    ");
				break;
			case KEY_RIGHT:
				OLED_ShowString(0, 32, "KEY_RIGHT   ");
				break;
			case KEY_NONE:
				break;
				
			default:
				break;
		}
	}

	OLED_Refresh_Gram();
	delay_ms(10);
	ciri++;
	
	if(ciri > 25)
	{
		cirj++;
		
		if(!key && cirj > 4) 
		{
			cirj = 0;
			
			AdcValue = Get_Adc_Average(ADC1, ADC_Channel_0);	//读取摇杆的ADC值
			OLED_ShowxNum(32, 16, AdcValue, 3, 16, 0x03);		//显示ADC的值
			Voltage = (float)AdcValue * (3.3 / 4096);
			AdcValue = Voltage;
			OLED_ShowxNum(64, 16, AdcValue, 1, 16, 0x01);		//显示电压值
			Voltage -= AdcValue;
			Voltage *= 1000;
			OLED_ShowxNum(80, 16, Voltage, 3, 16, 0x81);
			OLED_ShowString(0, 32, "KEY_NONE     ");
		}
		
		ciri = 0;
	}
}


void OLED_DisFormat_For_NRFandAGV(void)
{
	OLED_ShowString(0, 0, "AGV Sta:");
	
	OLED_ShowString(0, 16, "L:");
	OLED_ShowString(47, 16, "EN:");
	OLED_ShowString(87, 16, "FR:");
	
 	OLED_ShowString(0, 32, "R:");
	OLED_ShowString(47, 32, "EN:");
	OLED_ShowString(87, 32, "FR:");
	
 	//OLED_ShowString(0, 32, "***************"); 
 	OLED_ShowString(0, 48, "NRF:");
	OLED_Refresh_Gram();
}

void My_Change_To_RX_Mode_Fast(void)
{
	NRF24L01OptsPtr->RxMode_Fast();
	OLED_ShowString(0,48,"NRF:         ");
	OLED_Refresh_Gram();
}

void My_Change_To_TX_Mode_Fast(void)
{
	NRF24L01OptsPtr->TxMode_Fast();
	OLED_ShowString(0,48,"NRF:         ");
	OLED_Refresh_Gram();
}



void My_NRF24L01_Init(void)
{
	OLED_DisFormat_For_NRFandAGV();
	
	SPI_Initial();
	
	NFR24L01_Init();
	
	EXTI4_Init();
	//My_Change_To_RX_Mode_Fast();
	
	
	//OLED_ShowString(0,48,"NRF: RX Mode ");
	//OLED_Refresh_Gram();
}



