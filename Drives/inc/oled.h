#ifndef __OLED_H__
#define __OLED_H__

//#include "common_include.h"
#include "stm32f10x.h"
#include "stdlib.h"
#include "gpio.h"

typedef struct
{
	void (*OLED_Clear)(void);
	void (*OLED_Refresh_Gram)(void);
	void (*OLED_Display_On)(void);
	void (*OLED_Display_Off)(void);
	void (*OLED_ShowChar)(uint8_t,uint8_t,uint8_t,uint8_t,uint8_t);
	void (*OLED_ShowNum)(uint8_t,uint8_t,uint32_t,uint8_t,uint8_t);
	void (*OLED_ShowxNum)(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size,uint8_t mode);
	void (*OLED_ShowString)(uint8_t,uint8_t,const uint8_t *);
	void (*OLED_ShowString_Plus)(uint8_t,uint8_t,const uint8_t *);
}OLED_OperatorStruct, *OLED_OperatorStruct_P;


//OLEDģʽ����: 4�ߴ���ģʽ
		    						  
//-----------------OLED�˿ڶ���----------------
#define OLED_PWR			GPIOout(GPIOC,13)	//OLED��Դ����IO���ߵ�ƽ�򿪵�Դ
#define OLED_CS				GPIOout(GPIOB,3)	//OLED SPIѡͨ
#define OLED_RST			GPIOout(GPIOB,4)	//OLED��λ
#define OLED_DC				GPIOout(GPIOB,5)	//OLED D/C#
#define OLED_SCLK			GPIOout(GPIOB,6)	//OLED SPIʱ��
#define OLED_SDIN			GPIOout(GPIOB,7)	//OLED SPI����
 		     
#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

//OLED�����ú���
void OLED_WR_Byte(uint8_t dat,uint8_t DC);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);		   
							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t dot);
void OLED_Fill(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t dot);
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size,uint8_t mode);
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size);
void OLED_ShowString(uint8_t x,uint8_t y,const uint8_t *p);
void OLED_ShowString_Plus(uint8_t row,uint8_t col,const uint8_t *p);
void OLED_ShowxNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size,uint8_t mode);

extern OLED_OperatorStruct_P OLED_Opts_Ptr;

#endif  

