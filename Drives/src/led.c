#include "led.h"


/**
  * @brief  LED IO��ʼ��
  * @param  None
  * @retval None
	* @note   LED���ӵ�GPIOB.12���͵�ƽ�����ߵ�ƽ��
  */
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	   
	/* ʹ��GPIOBʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	/* ����GPIOB.12Ϊ�������ģʽ */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_SetBits(GPIOB, GPIO_Pin_12);//����GPIOB.12Ϊ�ߵ�ƽ���ر�LED
}

/**
  * @brief  ����LEDָʾ��
  * @param  None
  * @retval None
	* @note   LED���ӵ�GPIOB.12���͵�ƽ�����ߵ�ƽ��
  */
void LED_On(void)
{
	//GPIO_ResetBits(GPIOB, GPIO_Pin_12);//����GPIOB.12Ϊ�͵�ƽ
	uLED = 0;
}

/**
  * @brief  �ر�LEDָʾ��
  * @param  None
  * @retval None
	* @note   LED���ӵ�GPIOB.12���͵�ƽ�����ߵ�ƽ��
  */
void LED_Off(void)
{
	//GPIO_SetBits(GPIOB, GPIO_Pin_12);//����GPIOB.12Ϊ�͵�ƽ
	uLED = 1;
}

/**
  * @brief  LEDָʾ�Ʒ�ת
  * @param  None
  * @retval None
	* @note   LED���ӵ�GPIOB.12���͵�ƽ�����ߵ�ƽ��
  */
void LED_Toggle(void)
{
	#if 0
	
	uint8_t status;
	
	status = GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_12);//��ȡ��ǰGPIOB.12״̬
	if(status)
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);//���GPIOB.12�Ǹߵ�ƽ��������Ϊ�͵�ƽ
	}
	else
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_12);//���GPIOB.12�ǵ͵�ƽ��������Ϊ�ߵ�ƽ
	}
	
	#else

	uLED_T;

	#endif
}

