/*****************************************************************                                
*	模块名称 :按键转换华摄氏温度功能
*	文件名称 : Calculation.c
*	版    本 : V1.0
*	说    明 : 通过按键中断设置华氏摄氏转换功能
******************************************************************/
#include "LPC11xx.h"                    // Device header
#include "send.h"
#include "key.h"
#define KEY1_DOWN()((LPC_GPIO1->DATA&(1<<0))!=(1<<0)
#define KEY2_DOWN()((LPC_GPIO1->DATA&(1<<1))!=(1<<1)
uint8_t counter=0;
void SEGinit()

{
	LPC_GPIO2->DIR|=0xFFF;
}

void KEYinit()

{

	LPC_GPIO3->DIR &=~(1<<0);
	LPC_GPIO3->DIR &=~(1<<1);

}

void BreakInit()

{
  LPC_GPIO3->IE|=(1<<0);

	LPC_GPIO3->IS&=~(1<<0);

	LPC_GPIO3->IEV&=~(1<<0);
	
	LPC_GPIO3->IE|=(1<<1);

	LPC_GPIO3->IS&=~(1<<1);

	LPC_GPIO3->IEV&=~(1<<1);
}

void PIONT1_TRQHandler()
{
	if((LPC_GPIO1->MIS&(1<<0))==(1<<0))
	{
		counter ++;
	LPC_GPIO1->IC=(1<<0);
	}
if((LPC_GPIO1->MIS&(1<<1))==(1<<1))
 {
	counter --;
	LPC_GPIO1->IC=(1<<1);
 }
}