#include "joystick.h"
#include "delay.h"

/**
  * @brief 摇杆按键（JoyStick）初始化
	* @param none
  * @retval none
  * @note  初始化PA.00为ADC1_CH1，单次转换，软件触发ADC转换
  */
void JoyStick_Init(void)
{ 
	ADC_InitTypeDef ADC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	/* 使能GPIOA，ADC1,AFIO时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);

	/* 设置ADCCLK分频因子 ADCCLK = PCLK2/6，即 72MHz/6 = 12MHz */
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);

	/* 配置 PA.00 (ADC1_IN0) 作为模拟输入引脚 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	ADC_DeInit(ADC1);  //将ADC1设为缺省值
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;				//单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//单次转换
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//软件触发ADC转换
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//规则转换通道数目
	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct初始化ADC

	/* ADC的规则通道组设置：一个序列，采样时间239.5周期	*/
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5 );

	ADC_Cmd(ADC1, ENABLE);	//使能ADC1

	ADC_ResetCalibration(ADC1);	//复位ADC校准寄存器
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	ADC_StartCalibration(ADC1);	 //开启AD校准
	while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束
}

/**
  * @brief 摇杆按键（JoyStick）处理函数
	* @param none
  * @retval 按键值: KEY_NONE,KEY_CENTER,KEY_UP,KEY_LEFT,KEY_DOWN,KEY_RIGHT
  * @note
  *    此函数有响应优先级,KEY_CENTER > KEY_RIGHT > KEY_DOWN > KEY_LEFT > KEY_UP!!
  */
uint8_t JoyStick_Scan(uint8_t polling)
{
	uint16_t AdcValue;
	static uint8_t key_release = 1;//按键按松开标志

  /* 开启ADC转换 */	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);					//开始转换
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));			//等待转换结束
	AdcValue = ADC_GetConversionValue(ADC1);				//返回ADC1转换结果
	
	if(polling)		//支持连按
	{
		key_release = 1;									
	}
	
	if(key_release && (AdcValue >= 0xb4))					//检测到按键按下
	{
		key_release = 0;
		
		if(AdcValue >= 0xcba)return KEY_CENTER;
		else if(AdcValue >= 0x973)return KEY_RIGHT;
		else if(AdcValue >= 0x686)return KEY_DOWN;
		else if(AdcValue >= 0x354)return KEY_LEFT;
		else return KEY_UP;
	}
	
	if(AdcValue < 0xb4)
	{
		key_release = 1;	//未检测到按键按下
	}
	
 	return 0;				// 无按键按下
}

