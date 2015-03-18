/*
 * =====================================================================
 * NAME         : Led.c
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
//#include "libc.h"

//Function Declaration
void Led_Init();
void Led_Display(int data);

void Led_Init()
{
	/* TO DO : Init GPIO port connected to LED 
	 * LED[4:9] = GPB[5:10] */
	 
		
}

void Led_Display(int data)
{
	int i;
	
#if 1
	//** if ~ else를 사용할 경우 

	 
#endif
	
#if 0
	//** switch ~ case를 사용할 경우 



#endif 

#if 0
	//** 삼항연산자를 사용할 경우 


					
#endif

	for(i=0;i<0xfffff;i++);

	rGPBDAT |= (0x3f<<5);
}

