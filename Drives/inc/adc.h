#ifndef __ADC_H__
#define __ADC_H__
#include "stm32f10x.h"

void ADC_Initialize(void);
uint16_t Get_Adc(ADC_TypeDef* ADCx, uint8_t ch);
uint16_t Get_Adc_Average(ADC_TypeDef* ADCx, uint8_t ch);


#endif

