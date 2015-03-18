#include "2440addr.h"
#include "option.h"
//#include "libc.h"

//Function Declaration 
void Key_Port_Init(void);
void Key_Get_Pressed_with_LED();
int Key_Get_Pressed();
int Key_Wait_Get_Pressed();
void Key_Wait_Get_Released();

//Function
void Key_Port_Init(void)
{
	// KEYOUT[0:4] = GPB[0:2] & GPH[9] & GPB[4], KEYIN[0:1] = GPF[3:4]
	
	/* TODO : GPFCON - Input mode */
	rGPFCON &= ~(0xf << 6);			
	rGPFUP	&= ~0x18;

	
	/* TODO : GPBCON & GPHCON - output mode */
	rGPBDAT |= 0x17;
	rGPBCON &= ~(0x33f);
	rGPBCON |= 0x115;		
							// GPB0, GPB1, GPB2, GPB4
	rGPHDAT |= 0x200;
	rGPHCON &= ~(0xC0000);
	rGPHCON |= 0x40000;
							// GPH9

	
}

void Key_Get_Pressed_with_LED()
{
	/* TO DO : SW2/4/6/8/10 => LED4, SW3/5/7/9/11 => LED5 */
	int i, j, dir;
	
	for(i=0;i<6;i++)
		{
			
			if(i==3)
				rGPHDAT &= ~(0x1<<9);
			else if(i<5)
				rGPBDAT &= ~(0x1<<i);
			else
				dir = 1;
			if( ((~(rGPFDAT>>3)) & 0x3) & (dir != 1))
				{
					rGPBDAT |= (1<<(5+i));
					for(j=0 ; j<0x3fffff ; j++);
				}
		}
}

int Key_Get_Pressed()
{
	/* TO DO : 입력된 키값을 확인하여 리턴하는 함수 */
	int i,j;	

	for(j=4 ; j>=0 ; j-- )
	{
		if (j==3) {
			rGPBDAT |= 0x17;
			rGPHDAT |= 0x1<<9;
			rGPHDAT &= ~(0x1<<9);
		} else {
			rGPHDAT |= 0x1<<9;
			rGPBDAT |= (0x17);
			rGPBDAT &= ~(0x1<<j);
		}

		for(i=0;i<2;i++)
		{
			if(~(rGPFDAT>>3) & (0x1<<i))
				return i*5+1+j;
		}
	}
	return 0;

}

int Key_Wait_Get_Pressed()
{
	/* TO DO : 키가 눌려졌을 때에만 값을 리턴하도록 기다려 주는 함수 */
	int a;
	while(!( a=Key_Get_Pressed()));
	return a;
	
}

void Key_Wait_Get_Released()
{	
	/* TO DO : 키가 눌려지지 않았을 때를 나타내는 함수 */
	while(Key_Get_Pressed());
}