/*****************************************************************                                
*	模块名称 : 发送到PC端模块
*	文件名称 : ADC.h
*	版    本 : V1.0
*	说    明 :  通信发送接收宏定义等
******************************************************************/
#include "LPC11xx.h"           // Device header
void UART_Init(void);
void UART_SendByte(uint8_t ucDat);
void UART_SendStr(char * pucStr);
void delay(void);