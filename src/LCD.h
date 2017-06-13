#include "LPC11xx.h"                    // Device header
void Delayms(uint16_t ms);
void SysTick_Handler(void);
uint8_t Busy_Check();
void LCD_WriteCommand(uint32_t cmd);
void LCD_WriteData(uint32_t dat);
uint8_t LCD_DisplayChar(uint8_t x, uint8_t y, uint8_t ch);
uint8_t LCD_DisplayStr(uint8_t x, uint8_t y, uint8_t *pStr);
void LCD_IOInit(void);
void InitLCD();

