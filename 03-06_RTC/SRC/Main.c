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
//#include "libc.h"

#define EXAMPLE 330
/*
 * 310: 실습 3 : LED_ON_Test
 *
 * 311	실습 4-1 : Key_Input_Test_with_LED
 *	
 * 312: 실습 4-2 : Key_Input_Test_with_UART
 *
 * 320: 실습 5 : UART_Test
 *
 * 330: 실습 6 : Timer_Test	
 * 
 */

/***************************************
 * 
 * Title: LED_ON_Test
 * 
 ***************************************/

#if EXAMPLE == 310
void Main(void)
{	
	int a;
	
	Led_Init();
	
	while(1){
	for(a=0;;a++)
		Led_Display(a%7);
	}
			
}
#endif 
 
/***************************************
 * 
 * Title: Key_Input_Test_with_LED
 * 
 ***************************************/

#if EXAMPLE == 311
void Main(void)
{	
	int a,i;
	
	Led_Init();
	Key_Port_Init();

	
	for(a=0;a<7;a++)
		Led_Display(a);
	
	for(;;)
	{
		Key_Get_Pressed_with_LED();	
	}
			
}
#endif  

/***************************************
 * 
 * Title: Key_Input_Test_with_UART
 * 
 ***************************************/

#if EXAMPLE == 312
void Main(void)
{	
	int a,i;
	
	Led_Init();
	Key_Port_Init();
	Uart_Init(115200);

	Uart_Send_String("Key Test \n");
	
	for(a=0;a<7;a++)
		Led_Display(a);
	
	for(;;)
	{
		Uart_Printf("Key Value =%d\n", Key_Wait_Get_Pressed()); 
		Key_Wait_Get_Released();
			
	}

}
#endif 

/***************************************
 * 
 * Title: UART_Test
 * 
 ***************************************/

#if EXAMPLE == 320
void Main(void)
{	

	Uart_Init(115200);	

	Uart_Send_Byte('\n');
	Uart_Send_Byte('A');
	Uart_Send_Byte('\n');
	Uart_Send_String("Hello Uart Test...!!!\n");
	
	Uart_Printf("input character is [");
	Uart_Send_Byte(Uart_Get_Char());
	Uart_Printf("]\n");	
			
}
#endif


	
/***************************************
 * 
 * Title: Timer_Test
 * 
 ***************************************/

#if EXAMPLE == 330 
void Main()
{
#if 0
	Uart_Init(115200);	

	Timer_Init();	
	start_timer0();
	Uart_Send_Byte('\n');
	Uart_Send_Byte('\n');
	Uart_Printf("current time = %d\n",time());
	stop_timer0();
	start_timer0();
	Uart_Send_Byte('A');	
	Uart_Send_Byte('\n');
	Uart_Send_String("Hello Uart Test...!!!\n");
	Uart_Printf("current time = %d",time());
	stop_timer0();
	while(1)
	{
	//	Uart_Send_String("Time Delay\n");
	//	Timer_Delay(1000);
	};

#else

	Uart_Init(115200);
	Timer_Init();
	Uart_Printf("\n Hello RTC Interrupt Test...!!!\n");
	
	RTC_ISR_Init();
	while(1)
	{
		Uart_Printf("\n%02x:%02x:%02x", rBCDHOUR, rBCDMIN, rBCDSEC);
		Timer_Delay(1000);
	}		
		
	
}
#endif
#endif