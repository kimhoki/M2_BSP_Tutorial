/*
 * =====================================================================
 * NAME         : Main.c
 *
 * Descriptions : Main routine for S3C2440
 *
 * IDE          : CodeWarrior 2.0 or Later
 *
 * Modification
 *	   
 * =====================================================================
 */
#include "2440addr.h"

#define EXAMPLE 610

/*********** 6장 Exam ***************	
 * 
 * 610 : Touch Test (실습 9-1 : Touch Test)
 * 
 * 
 * Advanced Course
 * 1. make macro function 
 */
 
 /***************************************
 * 
 * Title: Touch Test
 * 
 ***************************************/

#if EXAMPLE == 610


//**ISR Declaration
void __irq Touch_ISR(void);

volatile  int ADC_x, ADC_y;
volatile  int Touch_Pressed=0;

void __irq Touch_ISR()
{
	/* 인터럽트 허용하지 않음 on Touch */
	rINTSUBMSK |= (0x1<<9);
	rINTMSK |= (0x1<<31);	
	
	/* TO DO: Pendng Clear on Touch */	
	rSUBSRCPND |= (1<<9);
	rSRCPND |= (1<<31);
	rINTPND |= (1<<31);


	if(rADCTSC & 0x100)
	{
		rADCTSC &= (0xff); 
		Touch_Pressed = 0;
		Uart_Send_String("Detect Stylus Up Interrupt Signal \n");
	}
	
	else
	{
		Uart_Send_String(" ISR 내부  \n");
		
		/* TO DO : Stylus Down, YM_out Enable, YP_out Disable, XM_out Disable, XP_out disable
		 * 		   XP Pull-up Disable, Auto Sequential measurement of X/Y, No operation mode */
		
		rADCTSC = (1<<8)|(1<<7)|(1<<6)|(0<<5)|(1<<4)|(1<<3)|(1<<2)|(0);
		

		/*********
		rADCTSC &= ~(0x3<<0);
		rADCTSC &= ~(0x1<<8);
		rADCTSC &= ~(0x1<<5);
		rADCTSC |= (0x1<<7) | (0x1<<3) | (0x1<<2) | (0x1<<6)| (0x1<<4);
		*********/

		/* TO DO : ENABLE_START */		
		rADCCON |= 0x1<<0;
		
		
		/* wait until End of A/D Conversion */
		while(!(rADCCON & (1<<15)));
		
		/*store X-Position & Y-Position Conversion data value to ADC_x, ADC_y */
		ADC_x = (rADCDAT0 & 0x3ff);
		ADC_y = (rADCDAT1 & 0x3ff);
		
		Touch_Pressed = 1;
		
		/* TO DO : change to Waiting for interrupt mode 
		 *		   Stylus Up, YM_out Enable, YP_out Disable, XM_out Disable, XP_out disable
		 * 		   XP Pull-up Disable, Normal ADC conversion, Waiting for interrupt mode */		
		
		rADCTSC = (1<<8)|(1<<7)|(1<<6)|(1<<4)|(0<<3)|(0<<2)|(3);
		
		/********
		rADCTSC |= (0x1<<8) | (0x3<<0);
		rADCTSC &= ~(0x1<<3) & (0x1<<2);
		********/
				
		
	}
	
	/* 인터럽트 다시 허용  on Touch */
	rINTSUBMSK &= ~(0x1<<9);
	rINTMSK &= ~(0x1<<31);
	
}

void Main(void)
{	
	Uart_Init(115200);
	Touch_Init();
	Led_Init();	
	
	Uart_Printf("*** Touch Test *** \n");
	
	/* TO DO : 인터럽트 벡터에 DMA0_ISR 함수 등록 */
	pISR_ADC = (unsigned int) Touch_ISR;
	
	/* TO DO :  인터럽트 허용 on Touch */
	rINTSUBMSK &= ~(0x1<<9);
	rINTMSK &= ~(0x1<<31);
		
	
	while(1)
	{
		if(Touch_Pressed)
		{
			Uart_Printf("X : %d, Y: %d \n", ADC_x, ADC_y);	
			
			if(ADC_y<521)
			{
				if(ADC_x<351)		Led_Display(1);
				else if(ADC_x>=351 && ADC_x<646)
									Led_Display(2);
				else				Led_Display(3);
			}
			else
			{
				if(ADC_x<351)		Led_Display(4);
				else if(ADC_x>=351 && ADC_x<646)
									Led_Display(5);
				else				Led_Display(6);
			}
			while(!(Touch_Pressed==0));
				Uart_Printf("Released\n\n");			
		}
	}
}

#endif 

 