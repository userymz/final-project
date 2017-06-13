#include "LPC11xx.h"                    // Device header
#include "ADC.h"   
#include "send.h" 
#include "Calculation.h"   
#include "LCD.h"  
#include "key.h"
#include "stdio.h"

extern char F;
extern char T;
extern char mea[20];
extern char sendpc[20];
extern uint8_t counter;
int main()
{
InitLCD();
SEGinit();
ADC_Init();
UART_Init();
BreakInit();
LCD_IOInit();
NVIC_EnableIRQ(EINT3_IRQn);
	while(1)
	{
		
		measure();
		UART_SendStr(mea);
		LCD_DisplayStr(0,0, "Hellow!");
		LCD_DisplayStr(0,1, mea);

	
	}
	
}