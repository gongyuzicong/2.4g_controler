#ifndef __SPI_H__
#define __SPI_H__

#include "stm32f10x.h"

void SPI_Initial(void);
void SPI1_SetSpeed(u8);
u8 SPI1_ReadWriteByte(u8);


#endif

