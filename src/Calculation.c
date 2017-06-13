/*****************************************************************                                
*	模块名称 :数据转换模块
*	文件名称 : Calculation.c
*	版    本 : V1.0
*	说    明 : 将测出的电阻值具体转化为温度
******************************************************************/
#include "LPC11xx.h"                    // Device header
#include "calculation.h"
#include "stdio.h"
extern uint8_t counter;
float  T;
float  F;
char mea[20];
char sendpc[20];
void measure()
{
	uint32_t i;
	uint32_t ulADCData;
	uint32_t ulADCBuf;
	uint32_t res;
		ulADCData=0;
		for(i=0;i<10;i++)
		{
			LPC_ADC->CR|=(1<<24);
			while((LPC_ADC->DR[7]&0x80000000)==0);
			LPC_ADC->CR|=(1<<24);
			while((LPC_ADC->DR[7]&0x80000000)==0);
			ulADCBuf=LPC_ADC->DR[7];
			ulADCBuf=(ulADCBuf>>6)&0x3ff;
			ulADCData+=ulADCBuf;
		}
	   ulADCData=ulADCData/10;
	   ulADCData=(ulADCData*3300)/1024;	
	   res=(ulADCData*10000)/(3300-ulADCData);
		
			  if (res==28017)
				T=0  ;
			if (res==26825)
				T=1   ;
			if(( 26825>res)&&(res>18560))
	 	   T= 1+(26825-res)/1000 ;
	    if((18560 >res )&&(res>12690))
			 T=	10+(18560-res)/700 ;
			if(( 12690>res )&&(res>10953))
			 T= 20+(12690-res)/600 ;
			if(( 10953>res )&&(res>9576))
		   T=23+(10953-res)/500; 	
			if(( 9576>res )&&(res>8160))
		   T=26+(9576-res)/350;
			if(( 8160>res )&&(res>7578))
			 T=30+(8160-res)/300;
			if(( 7578>res )&&(res>6357))
			 T=32+(7578-res)/250;
			if(( 6357>res )&&(res>4828))
			 T=37+(6357-res)/200;
			
			F=37+T*1.8; 
		 if(counter==0)
		sprintf (mea,"NOW=%.2d 'C",(int)T);
		else
		sprintf (mea,"NOW=%.2d 'C",(int)F);
		 
		}
	