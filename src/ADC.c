/*****************************************************************                                
*	ģ������ : ADCģ��ת����ģ��
*	�ļ����� : ADC.c
*	��    �� : V1.0
*	˵    �� : ADCģ��ת��������
******************************************************************/

#include "LPC11xx.h"                    // Device header

void ADC_Init(void)
	{
		LPC_SYSCON->SYSAHBCLKCTRL |=(1<<16);
		LPC_IOCON->PIO1_11 &= ~0xBF;
		LPC_IOCON->PIO1_11 |= 0x01;
		LPC_SYSCON->PDRUNCFG &=~(0x01<<4);
		LPC_SYSCON->SYSAHBCLKCTRL |=(0x01<<13);
		LPC_ADC->CR=(1<<7)|
		((SystemCoreClock/1000000-1)<<8)|
		(0<<16)|
		(0<<17)|
		(0<<24)|
		(0<<27);
	}
	