#include "LPC11xx.h"  // LPC11xx����Ĵ���
#include "string.h"

#define LCD_RS_LOW 		LPC_GPIO2->DATA &= ~(1<<0)	//����״̬����
#define LCD_RS_HIGH		LPC_GPIO2->DATA |=  (1<<0)	//
#define LCD_RW_LOW		LPC_GPIO2->DATA &= ~(1<<1)	//��дʹ������
#define LCD_RW_HIGH		LPC_GPIO2->DATA |=  (1<<1)	//
#define LCD_E_LOW		LPC_GPIO2->DATA &= ~(1<<2)	//ʹ�ܶ�
#define LCD_E_HIGH		LPC_GPIO2->DATA |=  (1<<2)	//

#define LCD_DATAPORT	LPC_GPIO2->DATA	            //DB0��DB7���ݶ˿�
#define LCD_DATA_IN		LPC_GPIO2->DIR &= ~0xFFF	//���ö˿�Ϊ����
#define LCD_DATA_OUT	LPC_GPIO2->DIR |=  0xFFF	//���ö˿�Ϊ���

static volatile unsigned int ticks = 0;
/********************************************************************************
* FunctionName   : Delayms(uint16_t ms)
* Description    : ����ϵͳ��ʱ���������뼶��ʱ
* EntryParameter : ms:Ϊ��ʱ����
* ReturnValue    : None
********************************************************************************/
void Delayms(uint16_t ms)					
{
	SysTick->CTRL &= ~(1<<2);
	SysTick->LOAD = 25000*ms-1;			
	SysTick->VAL = 0;						
	SysTick->CTRL = ((1<<1)|(1<<0));       
	while(!ticks);						    
	ticks = 0;							    
	SysTick->CTRL = 0;	
}
/********************************************************************************
* FunctionName   : SysTick_Handler()
* Description    : ϵͳ���Ķ�ʱ���жϷ�����
* EntryParameter : None
* ReturnValue    : None
********************************************************************************/
void SysTick_Handler(void)
{
	ticks++;
}
/********************************************************************************
* FunctionName   : Busy_Check()
* Description    : �ж�LCDģ���Ƿ�æ��������û��ȡ��8λ����Ҫ�������ж�
* EntryParameter : None
* ReturnValue    : ��LCD���ݶ˿ڶ�ȡ������
********************************************************************************/
uint8_t Busy_Check()
{
 	uint8_t LCD_Status;
	LCD_RS_LOW;
	LCD_RW_HIGH;
	LCD_E_HIGH;	//����Ϊ�����������ź�
	Delayms(1);
	
//	LCD_DATA_IN;	//���˿�����Ϊ����
    LPC_GPIO2->DIR &= ~(0x7F8);
    
    LCD_Status = (LPC_GPIO2->DATA & 0x7F8) >> 3;	//��ȡ�˿�����
//	LCD_DATA_OUT;	//���˿�����Ϊ���
	LPC_GPIO2->DIR |= 0x7F8;
    
	LCD_E_LOW;	
	return LCD_Status;
}
/********************************************************************************
* FunctionName   : LCD_WriteCommand()
* Description    : д�����
* EntryParameter : cmd:����
* ReturnValue    : None
********************************************************************************/
void LCD_WriteCommand(uint32_t cmd)
{
 	while((Busy_Check()	&	0x80)	==	0x80);	//�ж�LCDģ���Ƿ�æ
	LCD_RS_LOW;
	LCD_RW_LOW;
	LCD_E_LOW;	//����Ϊ����д�����ź�
    
	LPC_GPIO2->DATA = ((cmd << 3) & 0x7F8) | 0x00;	//������д��
	Delayms(1);	
	LCD_E_HIGH;
	Delayms(1);
	LCD_E_LOW;
}
/********************************************************************************
* FunctionName   : LCD_WriteData()
* Description    : д��ʾ���ݺ���
* EntryParameter : dat:����
* ReturnValue    : None
********************************************************************************/
void LCD_WriteData(uint32_t dat)
{
 	while((Busy_Check() & 0x80) == 0x80);	//�ж�LCDģ���Ƿ�æ
	LCD_RS_HIGH;
	LCD_RW_LOW;
	LCD_E_LOW;	//����Ϊ����д�����ź�
	LPC_GPIO2->DATA = ((dat << 3) & 0x7F8) | 0x01;	//������д��
	Delayms(1);	
	LCD_E_HIGH;
	Delayms(1);
	LCD_E_LOW;
}
/********************************************************************************
* FunctionName   : LCD_DisplayChar()
* Description    : ��ָ��λ����ʾ�ַ���yֵֻ��ȡ0��1��xֵ0=<x<=16��
* EntryParameter : x:x����(0~16), y: y����(0~1)��ch:Ϊ�ַ�
* ReturnValue    : None
********************************************************************************/
uint8_t LCD_DisplayChar(uint8_t x, uint8_t y, uint8_t ch)
{
	if ((y > 2) || (x > 16)) // x,y�������
	{
	    return 1;
	}
	x |= ((y == 1) ? 0xC0 : 0x80); // ��ʾ����
	LCD_WriteCommand(x); // ���ﲻ���æ�źţ����͵�ַ��
	LCD_WriteData(ch);
	return 0;
}
/********************************************************************************
* FunctionName   : LCD_DisplayStr()
* Description    : ���ƶ�λ����ʾ�ַ�����
* EntryParameter : x - x����(0~15), y - y����(0~1), *pStr - ��ʾ�ַ���
* ReturnValue    : ��ȷ����0�����󷵻�1
********************************************************************************/
uint8_t LCD_DisplayStr(uint8_t x, uint8_t y, uint8_t *pStr)
{
  uint8_t i;
	uint8_t lineAddr[] = {0x80, 0xC0};

	if ((y >= 2) || (x >= 16))	// x, y�������
	{
	    return 1;
	}
	LCD_WriteCommand(lineAddr[y] + x);  // д���ַ
	for (i=x; ((i<16) && (*pStr!='\0')); i++)
	{
 		LCD_WriteData(*(pStr++)); // д������
	}
	if (*pStr != '\0') // �ж������Ƿ�д��
	{
 		x = 0; // ûд��д���2��
		if (++y < 2)
		{
		    LCD_DisplayStr(x, y, pStr); // ��һ�м�����ʾ(�ݹ����)
		} 
	}
	return 0;
}
/********************************************************************************
* FunctionName   : LCDIOInit()
* Description    : ��ʼ��LCD�õ��Ķ˿�,
                   DB0~DB7�õ�P2.0��P2.7��RS��RW��E�õ�P3.0~P3.3
* EntryParameter : None
* ReturnValue    : None
********************************************************************************/
void LCD_IOInit(void)
{
	LPC_GPIO2->DIR |= 0xFFF;	//����P2_0~P2_7Ϊ���
//	LPC_GPIO3->DIR |= 0x0F;	//����P3_0~P3_3Ϊ���
    LPC_GPIO0->DIR |= 0x02;
    LPC_GPIO0->DATA |= (0x02);    
}
/********************************************************************************
* FunctionName   : InitLCD()
* Description    : ��ʼ��LCD�˿ڲ���������ʾ��ʽ
* EntryParameter : None
* ReturnValue    : None
********************************************************************************/
void InitLCD()
{
	LCD_IOInit();	//��ʼ��LCD�õ���GPIO
 	LCD_WriteCommand(0x38);	//����Ϊ8λ���ߡ�2����ʾ��5��7��������
	Delayms(1);	
	LCD_WriteCommand(0x01);	//��������HOMEλ
	Delayms(1);	
	LCD_WriteCommand(0x06);	//��������Ϊ������ʽ����ʾ���ݲ��ƶ�
	Delayms(1);	
	LCD_WriteCommand(0x0c);	//����ʾ���رչ�꣬��겻��˸
	Delayms(1);	
}
/********************************************************************************
* FunctionName   : main()
* Description    : ���������ڵ�һ����ʼΪֹ��ʼ��ʾ�ַ�����ռ��������һ��
* EntryParameter : None
* ReturnValue    : None
********************************************************************************/
