#include "LPC11xx.h"                    // Device header
#include "ADC.h"   
#include "send.h" 
#include "Calculation.h"   
#include "LCD.h"  
#include "key.h"




extern char mea[20];
extern char sendpc[20];
extern uint8_t counter;
int main()
{
InitLCD();
ADC_Init();
UART_Init();
SEGinit();
KEYinit();
BreakInit();
	
	while(1)
	{
		
			UART_SendStr(mea);
		  LCD_DisplayStr(0,0, mea);
	}
	
}