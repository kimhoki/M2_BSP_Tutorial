/***************************************************************
*
*	1. System Init Test 
* 
*	Created by MDS Tech. NT Div.(2Gr) (2007.3.1~4)
*
****************************************************************
*/

#include "2440addr.h"

void LED_Port_Init(void);
void LED_ON_Off(void);
void LED_TOGGLE(void);
void KEY_PORT_Init(void);
int KEY_PORT_SCAN(void);


void Main()
{
	int i, j=0, key;
	LED_Port_Init();
	KEY_PORT_Init();


	rGPBDAT &= ~0x7E0;
	
	while(1)
	{
		
		while( (key = KEY_PORT_SCAN()) == 0);	
		
		
			
		
		if(key == 6)
		{
			rGPBDAT |= (0x1 << (j+5));
			j++;
			if(j>5)
				j=5;
		}
		else if(key == 1)
		{
			rGPBDAT &= ~(0x1 << (j+5));		
			j--;
			if(j<0)
				j=0;
		}
		for(i=0 ; i<8000000 ; i++);		
		
		
		/*
		if( key <= 5)
			rGPBDAT &= ~0x7C0;
		else 
			rGPBDAT &= ~0x7A0;
		
		
		//rGPBDAT &= ~0x7E0;	

		//rGPBDAT |= 0x7E0;
		for(i=0 ; i<8000000 ; i++);
		rGPBDAT |= 0x7E0;
		*/
	}

	
	
	/*
	while(1)
	{
		for(i=0 ; i<10000000 ; i++);
		//LED_TOGGLE;
		rGPBDAT |= 0x7E0;
		for(i=0 ; i<10000000 ; i++);
		rGPBDAT &= ~0x7E0;
	}
	*/
	

}
void KEY_PORT_Init()
{
	// GPF3, GPF4 = INPUT(00)
	rGPFCON &= ~(0xf << 6);			
	rGPFUP	&= ~0x18;		// PULL_UP 
	
	// GPB0, GPB1, GPB2, GPH9, GPB4 = OUTPUT(01)
	rGPBDAT |= 0x17;
	rGPBCON &= ~(0x33f);
	rGPBCON |= 0x115;		
							// GPB0, GPB1, GPB2, GPB4
	rGPHDAT |= 0x200;
	rGPHCON &= ~(0xC0000);
	rGPHCON |= 0x40000;	
							// GPH9
}

int KEY_PORT_SCAN()
{
	int i;
	static unsigned int temp0, temp1;
	
	
	while(1)
	{
		for (i=0 ; i<5 ; i++)
		{
			if ( i != 3)
			{
				rGPBDAT &= ~(0x1<<i);	// GPB0, GPB1, GPB2, GPB4 Clear
			}
			else
			{
				rGPHDAT &= ~(0x1<<9);	//	GPH9 Clear		
			}
			
			temp0 = ~(rGPFDAT>>3) & 0x3;
			
			if(temp0 == 0x1)
			{
				switch(i)
				{
					case 0: return 1;	//SW2
					case 1: return 2;	//SW4
					case 2: return 3;	//SW6
					case 3: return 4;	//SW8
					case 4: return 5;	//SW10
				}
			}
			else if(temp0 == 0x2)
			{
				switch(i)
				{
					case 0: return 6;	//SW3
					case 1: return 7;	//SW5
					case 2: return 8;	//SW7
					case 3: return 9;	//SW9
					case 4: return 10;	//SW11
				}
			}

			rGPBDAT |= 0x17;		// GPB0, GPB1, GPB2, GPB4 SET
			rGPHDAT |= 0x200;		//	GPH9 SET
		}	
	}
}	
	
void LED_TOGGLE()
{
	rGPBDAT ^= 0x7E0;		
}



void LED_Port_Init()
{
/*  
	
	Configure LED4(GPB5) as OUTPUT
	
	ldr r0, =GPBCON	//0x56000010
	ldr r1, [r0]
	bic r1, r1, #0xc00
	orr r1, r1, #0x400
	str r1, [r0]

*/	
	/* TO DO : set GPBCON[5] as output for LED4(GPB5) */

	rGPBDAT |= 0x7E0;
	rGPBCON |= (0x1<<10) | (0x1<<12) | (0x1<<14) | (0x1<<16) | (0x1<<18) | (0x1<<20);

}

void LED_ON_Off()
{
/*	
	Make LED4(GPB5) to LOW
	
	ldr r0, =GPBDAT 
	ldr r1, [r0]
	orr r1, r1, #0x20
	bic r1, r1, #0x20
	str r1, [r0]
*/
	int i;
	
	/* TO DO : refer to book */




		
}
