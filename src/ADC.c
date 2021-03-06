/*****************************************************************                                
*	模块名称 : ADC模数转换器模块
*	文件名称 : ADC.c
*	版    本 : V1.0
*	说    明 : ADC模数转换函数等
******************************************************************/

#include "LPC11xx.h"                    // Device header
#include "ADC.h"
void ADC_Init(void)
	{
		LPC_SYSCON->SYSAHBCLKCTRL |=(1<<16);
		LPC_IOCON->PIO1_11 &= ~0xBF;
		LPC_IOCON->PIO1_11 |= 0x01;
		LPC_SYSCON->PDRUNCFG &=~(0x01<<4);
		LPC_SYSCON->SYSAHBCLKCTRL |=(0x01<<13);
		LPC_ADC->CR=(0x01<<7)|
		((SystemCoreClock/1000000-1)<<8)|
		(0<<16)|
		(0<<17)|
		(0<<24)|
		(0<<27);
	}
	