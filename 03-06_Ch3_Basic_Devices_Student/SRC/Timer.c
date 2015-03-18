#include "2440addr.h"
#include "option.h"
//#include "libc.h"

//Function Declaration
void Timer_Init(void);
void Timer_Delay(int msec);
void start_timer0(void);
void stop_timer0(void);
int time(void);


int time()
{		
	return 0xffff - rTCNTO0;	
}

void stop_timer0()
{
	rTCON = 0;		
}


void start_timer0()
{

	rTCNTB0 = 0xffff;
	rTCON = 2;
	rTCON = 1;
	
	
	//
	//rTCON &= ~(1<<1);
	
	//rTCON |= 1;
	
	/*
	rTCON |= (0x1<<1) | 0; 		// auto-reload on,  manual-update on
	rTCON &= ~(0x1<<1); 		// manual-update off
	rTCON |= (0x1<<0);			// Timer0 Start
	*/
}

void Timer_Init(void)
{
 	// Divider 1/4, prescaler 125  ==>  10us
	rTCFG0 |= (0x7C<<0); 
	rTCFG1 |= (0x1<<0);	
	rTCON  = (0<<4);
	rTCNTB0 = 0;
	rTCMPB0 = 0;


	/* 
	* TO DO : Timer0 Init 
	* Prescaler value : 255, dead zone length = 0
	* Divider value : 1/16, no DMA mode
	* New frequency : (PCLK/(Prescaler value+1))*Divider value = (50Mhz/(256))*(1/16)
	*				= 12.207Khz(12207Hz)  == 81.9us
	*/

	
	/* TCON설정 :Dead zone disable,  auto reload on, output inverter off
	*  manual update no operation, timer0 stop, TCNTB0=0, TCMPB0 =0
	*/
	/****
	rTCFG0 |= (0xff<<0);	// Prescaler 255
	rTCFG1 |= (0x3<<0);		// Divider 1/16
	rTCON  = (0<<4)|(1<<3)|(0<<2)|(0<<1)|(0);
	rTCNTB0 = 0;
	rTCMPB0 = 0;
	*****/
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
	rTCON |= (0x1<<1) | 0; 	// auto-reload on,  manual-update on
	rTCON &= ~(0x1<<1); 				// manual-update off
	rTCON |= (0x1<<0);				// timer0 start

	while(rTCNTO0 != 0);
	/******
	rTCNTB0 = 12.207*msec;
	
	rTCON |= (1<<1) | (0);
	rTCON &= ~(1<<1);
	
	rTCON |= 1;
	
	while(rTCNTO0 != 0);
	*******/		
}