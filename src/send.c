/*****************************************************************                                
*	模块名称 : 发送到PC端模块
*	文件名称 : send.c
*	版    本 : V1.0
*	说    明 : 通信发送接收等功能
******************************************************************/
#include "LPC11xx.h" 
#include "send.h"
#define UART_BPS 9600

void UART_Init(void)
{
	uint16_t usFdiv;
	LPC_SYSCON->SYSAHBCLKCTRL|=(1<<16);
	LPC_IOCON->PIO1_6&=~0x07;
	LPC_IOCON->PIO1_6|=(1<<0);
	LPC_IOCON->PIO1_7&=~0x07;
	LPC_IOCON->PIO1_7|=(1<<0);
	LPC_SYSCON->SYSAHBCLKCTRL|=(1<<12);
	LPC_SYSCON->UARTCLKDIV=0x01;
	LPC_UART->LCR=0x83;
	usFdiv=(SystemCoreClock/LPC_SYSCON->UARTCLKDIV/16)/UART_BPS;
	LPC_UART->DLM=usFdiv/256;
	LPC_UART->DLL=usFdiv%256;
	LPC_UART->LCR=0x03;
	LPC_UART->FCR=0x07;
}
	void Delay(uint32_t ulTime)
	{
		uint32_t i;
		i=0;
		while(ulTime--)
		{
			for (i=0;i<5000;i++);
		}
	}
void UART_SendByte(uint8_t ucDat)
{
	LPC_UART->THR=ucDat;
	while((LPC_UART->LSR&0x40)==0);
}
void UART_SendStr(char * pucStr)
{
	while(1)
	{
	if(*pucStr=='\0')break;
	UART_SendByte (*pucStr++);
	}
}	