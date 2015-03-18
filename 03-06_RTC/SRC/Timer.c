#include "2440addr.h"
#include "option.h"
//#include "libc.h"
#if 0
//Function Declaration
void Timer_Init(void);
void Timer_Delay(int msec);

void Timer_Init(void)
{
	/* 
	* TO DO : Timer0 Init 
	* Prescaler value : 255, dead zone length = 0
	* Divider value : 1/16, no DMA mode
	* New frequency : (PCLK/(Prescaler value+1))*Divider value = (50Mhz/(256))*(1/16)
	*				= 12.207Khz(12207Hz)
	*/
	
	rTCFG0 = (0<<8)|(0xff); 
	rTCFG1 = (0<<20)|(3); 
	
	
	/* TCON설정 :Dead zone disable,  auto reload on, output inverter off
	*  manual update no operation, timer0 stop, TCNTB0=0, TCMPB0 =0
	*/
	rTCON  = (0<<4)|(1<<3)|(0<<2)|(0<<1)|(0);
	rTCNTB0 = 0;
	rTCMPB0 = 0;
  
}

void Timer_Delay(int msec)
{
	/*
	* 1) TCNTB0설정 : 넘겨받는 data의 단위는 msec이다.
	*                  따라서 msec가 그대로 TCNTB0값으로 설정될 수는 없다.
	* 2) manual update후에  timer0를 start시킨다. 
	* 	 note : The bit has to be cleared at next writing.
	* 3) TCNTO0값이 0이 될때까지 기다린다. 	
	*/
	/* YOUR CODE HERE */




	
	
}
void start_timer0(void)
{
	rTCFG0 = 0xff;
	rTCNTB0 = 0xffff; /* max of 16 bit value */
	rTCON = 2; /* update CNTB */	
	rTCON = 1; /* start timer 0 */
}

	/* 
	 * void stop_timer0(void)
	 * -----------------------------------------------------------------
	 * 
	 */
void stop_timer0(void)
{
	
	rTCON = 0; /* stop timer 0 */
}

	/* 
	 * void time (void)
	 * -----------------------------------------------------------------
	 * Get current value of timer 0
	 */
int time (void)
{
	return 0xffff - rTCNTO0 ;	
}
#else

void __irq RTC_Isr(void);
void RTC_ISR_Init(void);
void RTC_TimeSet(char hour, char min, char sec);
void RTC_Alarm_Set(char hour, char min, char sec);
void RTC_Alarm_Mode_Set(int year_en, int month_en, int day_en, int hour_en, int min_en, int sec_en);

//Function Declaration
void Timer_Init(void);
void Timer_Delay(int msec);

void Timer_Init(void)
{
	/* 
	* TO DO : Timer0 Init 
	* Prescaler value : 255, dead zone length = 0
	* Divider value : 1/16, no DMA mode
	* New frequency : (PCLK/(Prescaler value+1))*Divider value = (50Mhz/(256))*(1/16)
	*				= 12.207Khz(12207Hz)
	*/
	rTCFG0 = (0<<8)|(0xff); 
	rTCFG1 = (0<<20)|(3); 
	
	/* TCON설정 :Dead zone disable,  auto reload on, output inverter off
	*  manual update no operation, timer0 stop, TCNTB0=0, TCMPB0 =0
	*/
	rTCON  = (0<<4)|(1<<3)|(0<<2)|(0<<1)|(0);
	rTCNTB0 = 0;
	rTCMPB0 = 0;
  
}

void Timer_Delay(int msec)
{
	/*
	* 1) TCNTB0설정 : 넘겨받는 data의 단위는 msec이다.
	*                  따라서 msec가 그대로 TCNTB0값으로 설정될 수는 없다.
	* 2) manual update후에  timer0를 start시킨다. 
	* 	 note : The bit has to be cleared at next writing.
	* 3) TCNTO0값이 0이 될때까지 기다린다. 	
	*/
	/* YOUR CODE HERE */
	rTCNTB0 = 12.207*msec;	

	rTCON |= (1<<1)|(0);
	rTCON &= ~(1<<1);

	rTCON |= 1;	

	while(rTCNTO0 != 0);
//while(!(rTCNTO0 == 0));
	
	
}
void RTC_TimeSet(char hour, char min, char sec)
{
       rBCDHOUR= (unsigned char)(((hour/10)<<4) + (hour%10) );
       rBCDMIN=(unsigned char)( ((min/10)<<4) + (min%10) );
       rBCDSEC=(unsigned char)( ((sec/10)<<4) + (sec%10) );     	
}

void RTC_Alarm_Set(char hour, char min, char sec)
{
       rALMHOUR=(unsigned char)( ((hour/10)<<4) + (hour%10) );
       rALMMIN=(unsigned char)( ((min/10)<<4) + (min%10) );
       rALMSEC=(unsigned char)( ((sec/10)<<4) + (sec%10) );     	
}

void RTC_Alarm_Mode_Set(int year_en, int month_en, int day_en, int hour_en, int min_en, int sec_en)
{
	/* TODO: enable = 1 Disable = 0 */
//	year_en? : ; 
	year_en? (rRTCALM |= (0x1<<5)):(rRTCALM &=~(0x1<<5));
//	month_en?  : ; 
	month_en? (rRTCALM |= (0x1<<4)):(rRTCALM &=~(0x1<<4));
//	day_en?  : ; 
	day_en? (rRTCALM |= (0x1<<3)):(rRTCALM &=~(0x1<<3));
//	hour_en?  : ; 
	hour_en? (rRTCALM |= (0x1<<2)):(rRTCALM &=~(0x1<<2));
//	min_en?  : ; 
	min_en? (rRTCALM |= (0x1<<1)):(rRTCALM &=~(0x1<<1));
//	sec_en?  : ; 
	sec_en? (rRTCALM |= (0x1<<0)):(rRTCALM &=~(0x1<<0));
}

void __irq RTC_Isr(void)
{
	/* TO DO : 인터럽트 허용하지 않음 on RTC */
	rINTMSK |= (1<<30);
	/* TO DO : PENDING Register Clear */
	rSRCPND |= (1<<30);
	rINTPND |= (1<<30);
	
	
	Uart_Printf("\n RTC intr occur!!!\n");
	
	/* TO DO : RTC 인터럽트 허용 */
	rINTMSK &= ~(1<<30);
}

void RTC_ISR_Init(void)
{

	/* TO DO : 인터럽트 벡터에 RTC_Isr 함수 등록 */
	pISR_RTC = (unsigned int) RTC_Isr;
	
	/* TO DO : RTCCON-> No reset, Merge BCD count, XTAL divided clock, RTC control enable */
	rRTCCON &= ~(0x1<<3) & (0x1<<2) & (0x1<<1);
	rRTCCON |= (0x1<<0);

	
	/* TO DO : RTC 인터럽트 허용 */
	rINTMSK &= ~(0x1<<30);
	
	/* TO DO : Alarm Disable */
	rRTCALM &= ~(0x1<<6);

	/* RTC initial functions */
	RTC_TimeSet(12,0,0);
	RTC_Alarm_Set(12,0,10);
	RTC_Alarm_Mode_Set(0,0,0,0,0,1); 
	
	/* TO DO : Alarm Enable */
	rRTCALM |= (0x1<<6);
}
#endif