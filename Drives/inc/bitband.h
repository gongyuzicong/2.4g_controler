#ifndef __BITBAND_H__
#define __BITBAND_H__	
#include "stm32f10x.h"																    
	 
//λ������,ʵ��51���Ƶ�GPIO���ƹ���
//����ʵ��˼��,�ο�<<CM3Ȩ��ָ��>>������(87ҳ~92ҳ).
//IO�ڲ����궨��
#define BITBAND(Addr, BitNum) 	((Addr & 0xF0000000) + 0x2000000 + ((Addr & 0xFFFFF) << 5) + (BitNum << 2)) 
//#define MEM_ADDR(Addr)  		*((volatile unsigned long  *)(Addr))
#define MEM_ADDR(Addr)  		*((vu32 *)(Addr))
#define BIT_ADDR(Addr, BitNum)  MEM_ADDR(BITBAND(Addr, BitNum)) 


#endif

