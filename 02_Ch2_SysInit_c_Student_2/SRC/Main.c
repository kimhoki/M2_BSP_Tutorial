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

void Main()
{
	int i;
	
	LED_Port_Init();
	Key_Port_Init();

	
		LED_ON_Off();
	
	for(;;)
	{
		Key_Get_Pressed_with_LED();	
	}
			

	
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
	rGPBCON &=~(0xfff<<10);
	rGPBCON |=(0x555<<10);

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
	int j,i;
	
	/* TO DO : refer to book */
	for (i=5;i<11;i++)
	{
		rGPBDAT |= 0x1<<i;
		for (j=0;j<0x3fffff;j++);
		rGPBDAT &= ~(0x1<<i);
	}
		

	

		
}
