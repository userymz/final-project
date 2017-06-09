#include "LPC11xx.h"                    // Device header
#include "send.h"
#define KEY1_DOWN()((LPC_GPIO1->DATA&(1<<9))!=(1<<9)
#define KEY2_DOWN()((LPC_GPIO1->DATA&(1<<9))!=(1<<10)
uint8_t counter=0;
void SEGinit()

{
	LPC_GPIO2->DIR|=0xFFF;
}

void KEYinit()

{

	LPC_GPIO3->DIR &=~(1<<9);
	LPC_GPIO3->DIR &=~(1<<10);

}

void BreakInit()

{
  LPC_GPIO3->IE|=(1<<9);

	LPC_GPIO3->IS&=~(1<<9);

	LPC_GPIO3->IEV&=~(1<<9);
	
	LPC_GPIO3->IE|=(1<<10);

	LPC_GPIO3->IS&=~(1<<10);

	LPC_GPIO3->IEV&=~(1<<10);
}

void PIONT1_TRQHandler()
{
	if((LPC_GPIO1->MIS&(1<<9))==(1<<9))
	{
		counter ++;
	LPC_GPIO1->IC=(1<<9);
	}
if((LPC_GPIO1->MIS&(1<<10))==(1<<10))
 {
	counter --;
	LPC_GPIO1->IC=(1<<10);
 }
}