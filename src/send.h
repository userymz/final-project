/*****************************************************************                                
*	ģ������ : ���͵�PC��ģ��
*	�ļ����� : ADC.h
*	��    �� : V1.0
*	˵    �� :  ͨ�ŷ��ͽ��պ궨���
******************************************************************/
#include "LPC11xx.h"           // Device header
void UART_Init(void);
void UART_SendByte(uint8_t ucDat);
void UART_SendStr(char * pucStr);
void delay(void);