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

#define Macro_Clear_Interrupt_Pending(type)		{rSRCPND = (type);rINTPND=(type);}
#define Macro_Clear_Sub_Source_Pending(type)	rSUBSRCPND=(type)


#define EXAMPLE 412
/*	
 * 410 : �ǽ� 7-2 : Timer_Interrupt Test
 *
 * 411 : �ǽ� 7-1 : UART_Interrupt Test
 *	
 * 412 : �ǽ� 7-3 : Key_Interrupt Test
 * 
 */


/***************************************
 * 
 * Title: Timer_Interrupt
 * 
 ***************************************/

#if EXAMPLE == 410

// ISR Declaration
void __irq Timer0_ISR(void);

void __irq Timer0_ISR()
{
	/* �ش� ���ͷ�Ʈ Masking */ 

	rINTMSK |= (1<<10);
	/* TODO : Pending Register Clear */
	Macro_Clear_Interrupt_Pending(BIT_TIMER0);	

	Uart_Send_String("Timer ISR\n");
	
	/* �ش� ���ͷ�Ʈ UnMasking */
	rINTMSK &= ~(1<<10);
}

void Main()
{
	Uart_Init(115200);	

	Uart_Send_Byte('\n');
	Uart_Send_Byte('A');	
	Uart_Send_String("Hello Timer Interrupt Test...!!!\n");
	
	Timer_Init();
	
	/* TODO : ���ͷ�Ʈ ���Ϳ� Timer0_ISR �Լ� ��� */
	
	pISR_TIMER0 = (unsigned int) Timer0_ISR;


	/* Interrupt Unmasking */
	rINTMSK &= ~(1<<10);
	
	Timer_Delay(1000);
	
}

#endif


/***************************************
 * 
 * Title: UART_Interrupt
 * 
 ***************************************/

#if EXAMPLE == 411

static char Input_Char;

//** ISR Function declaration 
static void __irq  Uart_RX0_ISR(void);

static void __irq Uart_RX0_ISR(void)
{
	/* TO DO : UART0_RX �� �ٽ� �߻����� �ʵ��� Masking  */
	rINTSUBMSK |= (unsigned) BIT_SUB_RXD0;
	rINTMSK    |= (unsigned) BIT_UART0;

	
	/* TO DO: Pendng Clear on UART0_RX,UART0_ERR */
	Macro_Clear_Sub_Source_Pending(BIT_SUB_RXD0);
	Macro_Clear_Interrupt_Pending(BIT_UART0);

	
	/* ISRoutine Execution*/
	Uart_Send_Byte('\n');
	Uart_Send_String("Uart Receive data is OK..!!\n");
	
	#if 0
	if(Uart_Check_Overrun_Error()) 	Uart_Send_Byte('*'); Uart_Send_Byte('\n');
	#endif
	
	/* UnMasking on UART0_RX */  
	rINTSUBMSK &=~(0x1<<0);
	rINTMSK &=~(0x1<<28);

}

void Main(void)
{	

	Uart_Init(115200);	

	Uart_Send_Byte('\n');
	Uart_Send_Byte('A');	
	Uart_Send_String("Hello Uart Interrupt Test...!!!\n");
	
	/* TODO : ���ͷ�Ʈ ���Ϳ� Uart_RX0_ISR �Լ� ��� */
	pISR_UART0 = (unsigned int) Uart_RX0_ISR;
	
	/* TO DO : ���ͷ�Ʈ ��� on UART0_RX,ERR  */
	rINTSUBMSK &= (unsigned) (~BIT_SUB_RXD0);
	rINTSUBMSK &= (unsigned) (~BIT_SUB_ERR0);
	rINTMSK &= (unsigned) (~BIT_UART0);

	


	for(;;)
	{
		Input_Char=Uart_Get_Char();
		Uart_Printf("Input charter is : %c \n ", Input_Char);
	}
			
			
}

#endif

/***************************************
 * 
 * Title: Key_Interrupt (External Interrupt)
 * 
 ***************************************/

#if EXAMPLE == 412

// Global Variables Declaration
//volatile int Key_Value = 0;
int Key_Value = 0;

// ISR Declaration
void __irq Key_EINT3_ISR(void);
void __irq Key_EINT4_ISR(void);

void __irq Key_EINT4_ISR()
{

	unsigned int temp;
//	Uart_Printf("d\n");
	/* �ش� ���ͷ�Ʈ Masking */ 
	rEINTMASK |= (1<<4);
	rINTMSK |= (1<<4);

	/* Ű�� �б� ���Ͽ� Polling �Լ� ��� */
	temp = rGPFCON;

	/* TO DO :  1) GPFCON[7:3] change to Input mode 
	 *          2) �Էµ� Ű���� Ȯ���Ͽ� ������ ���� 
     */
    rGPFCON &= (~(0x3<<6)) & (~(0x3<<8));
  	Key_Value = Key_Wait_Get_Pressed();



    /* �ݵ�� port�� �����ϱ� ���Ͽ� ������ ������ ���� */
	rGPFCON = temp;

	/* TO DO : Keyout�� 0�� �Ͽ� Ű �Է� �����·� �ٲ� */
	rGPBDAT &= (~0x17);
	rGPHDAT &= (~0x200);


	/* TO DO: Pendng Clear on EINT4 */
	rEINTPEND |= (0x1<<4);
	Macro_Clear_Interrupt_Pending(BIT_EINT4_7);

	/* �ش� ���ͷ�Ʈ UnMasking */ 
	rEINTMASK &= ~(1<<4);
	rINTMSK &= ~(1<<4);
}



void __irq Key_EINT3_ISR()
{

	unsigned int temp;
	/* �ش� ���ͷ�Ʈ Masking */ 
	rINTMSK |= (1<<3);

	/* Ű�� �б� ���Ͽ� Polling �Լ� ��� */
	temp = rGPFCON;

	/* TO DO :  1) GPFCON[7:3] change to Input mode 
	 *          2) �Էµ� Ű���� Ȯ���Ͽ� ������ ���� 
     */
    rGPFCON &= (~(0x3<<6)) & (~(0x3<<8));
  	Key_Value = Key_Wait_Get_Pressed();



    /* �ݵ�� port�� �����ϱ� ���Ͽ� ������ ������ ���� */
	rGPFCON = temp;

	/* TO DO : Keyout�� 0�� �Ͽ� Ű �Է� �����·� �ٲ� */
	rGPBDAT &= (~0x17);
	rGPHDAT &= (~0x200);


	/* TO DO: Pendng Clear on EINT3 */
	Macro_Clear_Interrupt_Pending(BIT_EINT3);


	/* �ش� ���ͷ�Ʈ UnMasking */ 
	rINTMSK &= ~(1<<3);

}

void Main(void)
{	
	int a,i;
	
	Led_Init();
	for(i=0;i<8;i++)
		Led_Display(i);
	Key_IRQ_Port_Init();
	Uart_Init(115200);
		
	/* TODO : ���ͷ�Ʈ ���Ϳ� Key_EINT3_ISR �Լ� ��� */
	pISR_EINT3 	 = (unsigned int) Key_EINT3_ISR;
	pISR_EINT4_7 = (unsigned int) Key_EINT4_ISR;

	/* TO DO : ���ͷ�Ʈ ��� on EINT3, EINT4 */	
	rEINTMASK &= ~(0x1<<4);
	rINTMSK &= ~(0x1<<3);
	rINTMSK &= ~(0x1<<4);


	


	Uart_Send_String("Key ISR Test \n");
	
	for(;;)
	{
		if(Key_Value)
		Uart_Printf("Key Value =%d\n",  Key_Value); 
		Key_Value = 0;
			
	}
			
}
#endif