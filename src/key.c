/*****************************************************************                                
*	模块名称 :按键转换华摄氏温度功能
*	文件名称 : Calculation.c
*	版    本 : V1.0
*	说    明 : 通过按键中断设置华氏摄氏转换功能
******************************************************************/
#include "LPC11xx.h"                    // Device header
#include "send.h"
#include "key.h"
#include "stdio.h"
#include "LCD.h"
 extern float  F;
 extern char mea[20];
 extern float  T;
uint8_t counter;
void SEGinit()

{
	LPC_GPIO2->DIR|=0xFFF;
}


void BreakInit()

{
	
	LPC_GPIO3 ->DIR &=~(1<<0);
  
	LPC_GPIO3->IE|=(1<<0);
	
	LPC_GPIO3->IS&=~(1<<0);

	LPC_GPIO3->IEV&=~(1<<0);
	
	LPC_GPIO3 ->DIR &=~(1<<1);
	LPC_GPIO3->IE|=(1<<1);

	LPC_GPIO3->IS&=~(1<<1);

	LPC_GPIO3->IEV&=~(1<<1);
}

void PIOINT3_IRQHandler(void)
{
	if((LPC_GPIO3->MIS&(1<<0))==(1<<0))
	{
		counter=1;
	LPC_GPIO3->IC=(1<<0);
	}
if((LPC_GPIO3->MIS&(1<<1))==(1<<1))
 {
	counter =0;
	LPC_GPIO3->IC=(1<<1);
 }
}