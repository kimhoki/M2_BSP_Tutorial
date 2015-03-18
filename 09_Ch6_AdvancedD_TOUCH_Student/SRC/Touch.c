#include "2440addr.h"

void Touch_Init(void);


void Touch_Init(void)
{
	rADCDLY = (50000); 
     /* TO DO : prescaler enable, prescaler value=39, Analog no input, 
      * 		Normal operation mode, Disable start, No operation */
    rADCCON = (1<<14)|(39<<6)|(0<<3)|(0<<2)|(0<<1)|(0);
      
      
    /*****  
	rADCCON |= (0x1<<14)|(0x27<<6);
	rADCCON &= ~(0x1<<2)&(0x1<<0)&(0x1<<1);
	******/
	
	 /* TO DO :  For Waiting Interrupt Mode rADCTSC=0xd3 */
	rADCTSC = (0<<9)|(1<<7)|(1<<6)|(1<<4)|(0<<3)|(0<<2)|(3);
	 
	//rADCTSC = 0xD3;

	
}

