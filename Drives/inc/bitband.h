#ifndef __BITBAND_H__
#define __BITBAND_H__	
#include "stm32f10x.h"																    
	 
//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).
//IO口操作宏定义
#define BITBAND(Addr, BitNum) 	((Addr & 0xF0000000) + 0x2000000 + ((Addr & 0xFFFFF) << 5) + (BitNum << 2)) 
//#define MEM_ADDR(Addr)  		*((volatile unsigned long  *)(Addr))
#define MEM_ADDR(Addr)  		*((vu32 *)(Addr))
#define BIT_ADDR(Addr, BitNum)  MEM_ADDR(BITBAND(Addr, BitNum)) 


#endif

