#include "key.h"
#include "joystick.h"

/**
  * @brief  按键IO初始化
  * @param  None
  * @retval None
	* @note   按键连接到GPIOA.00，低电平亮，高电平灭
  */
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	   
	/* 使能GPIOA时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	/* 配置GPIOA.00为下拉输入 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}


/**
  * @brief  按键扫描程序
  * @param  polling:按键扫描模式
  *     @arg polling=0,不支持连续按键
  *     @arg polling=1,支持连续按键
  * @retval None
	* @note   
  */
uint8_t KEY_Scan(uint8_t polling)
{
	static uint8_t key_pre = 0;//前一次按键值
	uint8_t key_cur = 0;//当前按键值
	
	/* 读取当前按键IO值 */
	key_cur = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
	
	if(polling) key_pre=0;				//如果支持连续按键，不需要记录前一次按键值
	
	/* 如果检测到有按键按下，并且支持连续按键 */
	if(polling && key_cur) return KEY_CENTER;
	
	if(key_cur == 0)//如果没有检测到按键按下
	{
		if(key_pre > KEY_JITTER_COUNT)	//如果上一次扫描是有按键按下的，说明按键抬起
		{
			key_pre = 0;				//清除上一次按键值
			return KEY_CENTER;			//返回有效按键
		}
		else return KEY_NONE;
	}
	else//检测到按键按下
	{
		if(key_pre<0xff)
		{
			key_pre++;//key_pre累加
		}
	}
	
	return KEY_NONE;
}

