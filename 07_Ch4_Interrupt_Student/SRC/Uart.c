/*
 * =====================================================================
 * NAME         : Uart.c
 *
 * Descriptions : Uart Test Driver
 *
 * IDE          : CodeWarrior 2.0 or Later
 *
 * Modification
 *	   
 * =====================================================================
 */
#include "2440addr.h"
#include <stdarg.h>

// Function Declaration
void Uart_Init(int baud);

void Uart_Printf(char *fmt,...);
void Uart_Send_String(char *pt);
void Uart_Send_Byte(int data);
char Uart_Get_Char(void);
int Uart_Check_Overrun_Error(void);


void Uart_Init(int baud)
{
	// PORT GPIO initial
	rGPHCON &= ~(0xf<<4);
	rGPHCON |= (0xa<<4);

	/*  Non-FiFo��� */
	rUFCON0 = 0x0; 
	rUMCON0 = 0x0;
	
	/* Line Control(Normal mode, No parity, One stop bit, 8bit Word length */
	rULCON0 = 0x3;
	
	/* TO DO : Transmit & Receive Mode is interrupt request or polling mode  */


	/* baud rate ����  */		
	rUBRDIV0= ((unsigned int)(PCLK/16./baud+0.5)-1 );
}


void Uart_Printf(char *fmt,...)
{
    va_list ap;
    char string[256];

    va_start(ap,fmt);
    vsprintf(string,fmt,ap);
    Uart_Send_String(string);
    va_end(ap);		
}

void Uart_Send_String(char *pt)
{
	while(*pt)
	{
		Uart_Send_Byte(*pt++);		
	}	
}

void Uart_Send_Byte(int data)
{
	if(data=='\n')
	{
		while(!(rUTRSTAT0 & 0x2));
		WrUTXH0('\r');
	}

	while(!(rUTRSTAT0 & 0x2));	
		WrUTXH0(data);
}

char Uart_Get_Char()
{
	while(!(rUTRSTAT0 & 0x1));
	return RdURXH0();	
	//return *(volatile unsigned char *)URXH0;
	 
}

int Uart_Check_Overrun_Error()
{
	/* overrun error check in ERROR Status Register  */
	while(!(rUERSTAT0 & 0x1));	
	return 1;

}


