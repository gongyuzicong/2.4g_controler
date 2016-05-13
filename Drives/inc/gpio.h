#ifndef __CFG_GPIO_H__
#define __CFG_GPIO_H__

#include "common_include.h"
#include "bitband.h"

#define GPIOA_X_ON(PIN) 		(GPIOA->BSRR |= (1 << PIN))
#define GPIOB_X_ON(PIN) 		(GPIOB->BSRR |= (1 << PIN))
#define GPIOC_X_ON(PIN) 		(GPIOC->BSRR |= (1 << PIN))
#define GPIOD_X_ON(PIN) 		(GPIOD->BSRR |= (1 << PIN))
#define GPIOE_X_ON(PIN) 		(GPIOE->BSRR |= (1 << PIN))
#define GPIOF_X_ON(PIN) 		(GPIOF->BSRR |= (1 << PIN))
#define GPIOG_X_ON(PIN) 		(GPIOG->BSRR |= (1 << PIN))

#define GPIOA_X_OFF(PIN) 		(GPIOA->BSRR |= (1 << (PIN + 16)))
#define GPIOB_X_OFF(PIN) 		(GPIOB->BSRR |= (1 << (PIN + 16)))
#define GPIOC_X_OFF(PIN) 		(GPIOC->BSRR |= (1 << (PIN + 16)))
#define GPIOD_X_OFF(PIN) 		(GPIOD->BSRR |= (1 << (PIN + 16)))
#define GPIOE_X_OFF(PIN) 		(GPIOE->BSRR |= (1 << (PIN + 16)))
#define GPIOF_X_OFF(PIN) 		(GPIOF->BSRR |= (1 << (PIN + 16)))
#define GPIOG_X_OFF(PIN) 		(GPIOG->BSRR |= (1 << (PIN + 16)))

#define GPIOx_PINx_ON(GPIOx, PINx)		(GPIOx->BSRR |= (1 << PINx))
#define GPIOx_PINx_OFF(GPIOx, PINx)		(GPIOx->BSRR |= (1 << (PINx + 16)))

#define GPIOx_READ_BITx(GPIOx, PINx)	(GPIOx->IDR & (0x01 << PINx))

#define GPIOA_READ_BITx(PINx)	GPIOx_READ_BITx(GPIOA, PINx)


/*****************direct set:start*************************/
#define GPIOx_PINx_OUT(GPIOx, PINx, Data)	(GPIOx->ODR |= (Data << PINx))

#define GPIOA_PINx_OUT(PINx, Data)			(GPIOx_PINx_OUT(GPIOA, PINx, Data))
#define GPIOB_PINx_OUT(PINx, Data)			(GPIOx_PINx_OUT(GPIOB, PINx, Data))
#define GPIOC_PINx_OUT(PINx, Data)			(GPIOx_PINx_OUT(GPIOC, PINx, Data))
#define GPIOD_PINx_OUT(PINx, Data)			(GPIOx_PINx_OUT(GPIOD, PINx, Data))
#define GPIOE_PINx_OUT(PINx, Data)			(GPIOx_PINx_OUT(GPIOE, PINx, Data))
#define GPIOF_PINx_OUT(PINx, Data)			(GPIOx_PINx_OUT(GPIOF, PINx, Data))
#define GPIOG_PINx_OUT(PINx, Data)			(GPIOx_PINx_OUT(GPIOG, PINx, Data))

/*****************direct set:end*************************/

//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE + 12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE + 12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE + 12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE + 12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE + 12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE + 12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE + 12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE + 8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE + 8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE + 8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE + 8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE + 8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE + 8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE + 8) //0x40011E08 

/*****************位带操作:start************************/
//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr, n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr, n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr, n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr, n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr, n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr, n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr, n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr, n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr, n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr, n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr, n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr, n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr, n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr, n)  //输入

//例如：需要定义GPIOA.01作为输出IO，定义格式为： #define PA1out	GPIOout(GPIOA, 1)
//例如：需要定义GPIOA.01作为输入IO，定义格式为： #define PA1in	 GPIOin(GPIOA, 1)
#define GPIOout(GPIOx, bit)			MEM_ADDR(BITBAND((uint32_t)(&GPIOx->ODR), bit))
#define GPIOin(GPIOx, bit)			MEM_ADDR(BITBAND((uint32_t)(&GPIOx->IDR), bit))
/////////////////////////////////////////////////////////////////
/****************位带操作:end***************************/

/***********GPIO 翻转 begin********************/
#define GPIO_PIN_Toggle(OptObj,GPIO, PIN)	(OptObj = 1 - ((GPIO->ODR >> PIN) & 0x01))
#define PA_PIN_Toggle(PIN)			(PAout(PIN) = 1 - ((GPIOA->ODR >> PIN) & 0x01))
#define PB_PIN_Toggle(PIN)			(PBout(PIN) = 1 - ((GPIOB->ODR >> PIN) & 0x01))
#define PC_PIN_Toggle(PIN)			(PCout(PIN) = 1 - ((GPIOC->ODR >> PIN) & 0x01))
#define PD_PIN_Toggle(PIN)			(PDout(PIN) = 1 - ((GPIOD->ODR >> PIN) & 0x01))
#define PE_PIN_Toggle(PIN)			(PEout(PIN) = 1 - ((GPIOE->ODR >> PIN) & 0x01))
#define PF_PIN_Toggle(PIN)			(PFout(PIN) = 1 - ((GPIOF->ODR >> PIN) & 0x01))
#define PG_PIN_Toggle(PIN)			(PGout(PIN) = 1 - ((GPIOG->ODR >> PIN) & 0x01))
/***********GPIO 翻转 end**********************/


#endif
