#ifndef __MY_OPERATOR_H__
#define __MY_OPERATOR_H__

#include "common_include.h"

#define RX_DR		0x40	// �����ж�
#define TX_DS		0x20	// ���ݷ����ж�,�Զ�Ӧ��ģʽ��,�յ�ACK�����
#define MAX_RT		0x10	// �����ط��ж�

typedef enum
{
	stopStatus = 0,
	goStraightStatus,
	backStatus,
	cirLeft,
	cirRight,
}AgvStatus, *AgvStatus_P;

void joystickScan_Send_NRF(void);
void OLED_DisFormat_For_NRFandAGV(void);
void My_NRF24L01_Init(void);
void My_Change_To_TX_Mode_Fast(void);
void My_Change_To_RX_Mode_Fast(void);
void My_Change_NRFandAGV_View(u8 *);


#endif


