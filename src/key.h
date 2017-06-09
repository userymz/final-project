/*****************************************************************                                
*	模块名称 :按键转换华摄氏温度功能
*	文件名称 : Calculation.c
*	版    本 : V1.0
*	说    明 : 通过按键中断设置华氏摄氏转换功能宏定义等
******************************************************************/#include "LPC11xx.h"                    // Device header

void SEGinit();
void KEYinit();
void BreakInit();
void PIONT1_TRQHandler();
