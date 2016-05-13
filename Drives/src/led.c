#include "led.h"


/**
  * @brief  LED IO初始化
  * @param  None
  * @retval None
	* @note   LED链接到GPIOB.12，低电平亮，高电平灭
  */
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	   
	/* 使能GPIOB时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	/* 配置GPIOB.12为推挽输出模式 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_SetBits(GPIOB, GPIO_Pin_12);//设置GPIOB.12为高电平，关闭LED
}

/**
  * @brief  点亮LED指示灯
  * @param  None
  * @retval None
	* @note   LED链接到GPIOB.12，低电平亮，高电平灭
  */
void LED_On(void)
{
	//GPIO_ResetBits(GPIOB, GPIO_Pin_12);//设置GPIOB.12为低电平
	uLED = 0;
}

/**
  * @brief  关闭LED指示灯
  * @param  None
  * @retval None
	* @note   LED链接到GPIOB.12，低电平亮，高电平灭
  */
void LED_Off(void)
{
	//GPIO_SetBits(GPIOB, GPIO_Pin_12);//设置GPIOB.12为低电平
	uLED = 1;
}

/**
  * @brief  LED指示灯反转
  * @param  None
  * @retval None
	* @note   LED链接到GPIOB.12，低电平亮，高电平灭
  */
void LED_Toggle(void)
{
	#if 0
	
	uint8_t status;
	
	status = GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_12);//读取当前GPIOB.12状态
	if(status)
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);//如果GPIOB.12是高电平，则设置为低电平
	}
	else
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_12);//如果GPIOB.12是低电平，则设置为高电平
	}
	
	#else

	uLED_T;

	#endif
}

