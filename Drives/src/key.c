#include "key.h"
#include "joystick.h"

/**
  * @brief  ����IO��ʼ��
  * @param  None
  * @retval None
	* @note   �������ӵ�GPIOA.00���͵�ƽ�����ߵ�ƽ��
  */
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	   
	/* ʹ��GPIOAʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	/* ����GPIOA.00Ϊ�������� */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}


/**
  * @brief  ����ɨ�����
  * @param  polling:����ɨ��ģʽ
  *     @arg polling=0,��֧����������
  *     @arg polling=1,֧����������
  * @retval None
	* @note   
  */
uint8_t KEY_Scan(uint8_t polling)
{
	static uint8_t key_pre = 0;//ǰһ�ΰ���ֵ
	uint8_t key_cur = 0;//��ǰ����ֵ
	
	/* ��ȡ��ǰ����IOֵ */
	key_cur = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
	
	if(polling) key_pre=0;				//���֧����������������Ҫ��¼ǰһ�ΰ���ֵ
	
	/* �����⵽�а������£�����֧���������� */
	if(polling && key_cur) return KEY_CENTER;
	
	if(key_cur == 0)//���û�м�⵽��������
	{
		if(key_pre > KEY_JITTER_COUNT)	//�����һ��ɨ�����а������µģ�˵������̧��
		{
			key_pre = 0;				//�����һ�ΰ���ֵ
			return KEY_CENTER;			//������Ч����
		}
		else return KEY_NONE;
	}
	else//��⵽��������
	{
		if(key_pre<0xff)
		{
			key_pre++;//key_pre�ۼ�
		}
	}
	
	return KEY_NONE;
}

