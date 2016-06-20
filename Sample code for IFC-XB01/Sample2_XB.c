//=====================================================================================
//
//	Author				: Cytron Technologies		
//	Project				: IFC-XB01
//	Project description	: 
//  Date				: JAN 2010
//
//=====================================================================================

//=====================================================================================
//	include h file for cards
//	User has to include h file for all the cards used 
//=====================================================================================
#include<p18f2685.h>
#include "iic.h"
#include "iic_xb.h"
#include "iic_cp.h"


//=====================================================================================
//	configuration bit, User is advised not to change the setting here
//=====================================================================================
#pragma config OSC = HSPLL
#pragma config FCMEN = OFF 
#pragma config IESO = OFF 
#pragma config PWRT = OFF 
#pragma config BOREN = OFF 
#pragma config WDT = OFF 
#pragma config MCLRE = ON
#pragma config PBADEN = OFF 
#pragma config DEBUG = OFF
#pragma config XINST = OFF
#pragma config LVP = OFF 

//=====================================================================================
//	define input or ouput of board here
//	For example: 
//				1.led1 was defined for first LED on MB00
//				2.buzzer was defined for buzzer on MB00
//	The address for input/output devide on board is fixed, hence user is 
//	advised not to change the defined address for input/output 
//=====================================================================================

#define	led1		LATBbits.LATB0 	// led1 defined as output for first LED on MB00	
#define	led2		LATBbits.LATB1	// led2 defined as output for second LED on MB00
#define	led3		LATBbits.LATB2	// led3 defined as output for third LED on MB00
#define	led4		LATBbits.LATB3	// led4 defined as output for forth LED on MB00
#define	led5		LATBbits.LATB4	// led5 defined as output for fifth LED on MB00
#define	led6		LATBbits.LATB5	// led6 defined as output for sixth LED on MB00
#define	led7		LATBbits.LATB6	// led7 defined as output for seventh LED on MB00
#define	led8		LATBbits.LATB7	// led8 defined as output for eighth LED on MB00
#define	led			LATB			// led defined as output for ALL LED on MB00

#define	sw1			PORTAbits.RA2	// sw1 defined as input for SW1 on MB00
#define	sw2			PORTAbits.RA1	// sw2 defined as input for SW2 on MB00
#define	sw3			PORTAbits.RA0	// sw3 defined as input for SW3 on MB00
#define	buzzer		LATCbits.LATC5	// buzzer defined as output for buzzer on MB00
#define busy_led	LATCbits.LATC1	// busy_led defined as output for Busy LED on MB00
#define error_led	LATCbits.LATC2	// error_led defined as output for Error LED on MB00
#define slave_reset	LATCbits.LATC0	// slave_reset define as output to reset slave cards

//=====================================================================================
//	card address
//	User can define the address of slave card here
//=====================================================================================
#define add_xb		0b000001	// Please make sure the communication address on 
#define add_xb2		0b000010								

//=====================================================================================
//	function prototype
//	User needs to include all the function prototype here
//	The first 4 functions prototype are fixed, user is also advised not to
//	change it.
//=====================================================================================
void ISRHigh(void);
void ISRLow(void);
void delay(unsigned long data);
void init(void);
	
//=====================================================================================
//	Main Function
//	This is the main function where program start to execute 
//=====================================================================================
unsigned char rec_data[8]={0,0,0,0,0,0,0,0};

void main(void)
{
	//--------------------------------------------------------------------------------
	//	Program start
	//	User can start to write/modify the program here
	//--------------------------------------------------------------------------------
	//local variables
	unsigned short i,temp1;
	unsigned long address=0, SH, SL;

	//	User is advised not to change or remove the initialization function called 
	init();					// call initialization function of the setting in program
	delay(200000);			// waiting for slave card to ready
	

	while(1)
	{
		
		
//pls comment or uncomment the part needed
		
		if (cp1_sw(1)==0)
		{

			while(cp1_sw(1)==0);					// start on button release
// broadcast address setting=============================================================
// ==========================transmitter=================================================
// transmitter destination address is set to broadcast address

			led2=1;

			xb_MY(add_xb,0x1113);			// set the source address, MY to ABCD		
			xb_DL(add_xb,0x0000FFFF);		// set the destination address, DL to 0xFFFF
											// which is the broadcast address for 16bits 
											// addressing
			xb_CH(add_xb, 0x0B);			// select a channel for transmission		
			xb_ID(add_xb,0x4332);				//	select a PAN ID

//===========================receiver====================================================
			xb_MY(add_xb2,0x1234);			// set the source address, MY to 1234
			xb_DL(add_xb2,0x00001113);		// set the destination address, DL to 0xABCD	
			xb_CH(add_xb2, 0x0B);			// receiver need to be in the same channel 
											// to receive from transmitter
			xb_ID(add_xb2,0x4332);			// set PAN ID to be same
	
		}

		if (cp1_sw(2)==0)
		{

			while(cp1_sw(2)==0);					// start on button release
// broadcast address setting=============================================================
// ==========================transmitter=================================================
// transmitter PAN ID is set to broadcast value

			led2=1;

			xb_MY(add_xb,0x1113);			// set the source address, MY to ABCD		
			xb_DL(add_xb,0x00007E7D);		// set the destination address, DL to 0xFFFF
											// which is the broadcast address for 16bits 
											// addressing
			xb_CH(add_xb, 0x0C);			// select a channel for transmission		
			xb_ID(add_xb,0xFFFF);			// broadcast PAN ID. this will broadcast to 
											// every PANID in the same CH.

//===========================receiver====================================================
			xb_MY(add_xb2,0x7E7D);			// set the source address, MY to 1234
			xb_DL(add_xb2,0x00001113);		// set the destination address, DL to 0xABCD	
			xb_CH(add_xb2, 0x0C);			// receiver need to be in the same channel 
											// to receive from transmitter
			xb_ID(add_xb2,0x3332);			// set PAN ID
	
		}
		
		if (cp1_sw(3)==0)
		{
			led3=1;
			while(cp1_sw(3)==0);
			xb_send(add_xb, 'I','F','C','-','X','B','0','1');	// send out data			
			
		}

		if (cp1_sw(4)==0)
		{
			while(cp1_sw(4)==0);
			xb_send(add_xb, '1','2','3','4','5','6','7','8');	// send out data
		//	xb_send(add_xb, 0x7E,0x7E,0x13,0x7E,0x11,0x7E,0x7E,0x7D);	// send out data
		}	

		xb_receive(add_xb2);					//poll the IFC-XB01 to get data
		cp1_goto(0,0);
		cp1_str("receive:");
		cp1_char(rec_data[0]);					//display receive data on IFC-CP
		cp1_char(rec_data[1]); 
		cp1_char(rec_data[2]); 
		cp1_char(rec_data[3]); 
		cp1_char(rec_data[4]); 
		cp1_char(rec_data[5]); 
		cp1_char(rec_data[6]);  
		cp1_char(rec_data[7]); 

		cp1_goto(1,0);
		cp1_str("RSSI:");
		cp1_dec(xb_RSSI(add_xb2),3);
			
		
		

	

//	delay(1000);
		
	}
	
	
		
} //endmain






//=====================================================================================
//	functions
//  User can write all the necessary function here
//=====================================================================================
void delay(unsigned long data)
{
	// this is a delay function for user to use when the program need a delay
	// this function can be call by type : delay(xxxx),
	// user can replace the 'xxxx' with a value to determine how long the program
	// should delay for, the bigger the value, the longer the time of the delay
	for( ;data>0;data-=1);
}


void init(void)
{
	// this is a initialization for set the input and output of PIC18F2685
	// User is advised NOT to change the setting here
	// tris
	TRISB=0x00;				// led as output
	TRISA=0xff;				// push button as input
	TRISC=0x00;				// set port c as output
	
	// the setting for analog to digital converter, ADC for PIC18F2685
	// User is advised NOT to change the setting here
	// adc
	ADCON1=0x0F;
	
	//call the initialization function of I2C
	iic_init();		
	
	//	set the initial condition of output device on board
	//	User is advised not to change the initial condition
	led=0x00;				// turn OFF all LED on board by sending value '0x00'
	buzzer=0;				// turn OFF buzzer on board by sending value '0'
	error_led=0;			// turn OFF Error LED on board by sending value '0'
	busy_led=1;				// turn ON Busy LED on board by sending value '1'
	slave_reset=1;			// reset slave cards
	delay(10000);			
	slave_reset=0;			
	delay(80000);			
	busy_led=0;				// turn OFF Busy LED on board by sending value '0'
}


//=====================================================================================
//	Interrupt vector
//=====================================================================================
#pragma	code InterruptVectorHigh = 0x08
void InterruptVectorHigh(void)
{
 	_asm
		goto ISRHigh		// jump to interrupt routine
	_endasm
}
#pragma code
#pragma	code InterruptVectorLow = 0x18
void InterruptVectorLow(void)
{
 	_asm
		goto ISRLow			// jump to interrupt routine
	_endasm
}
#pragma code

//=====================================================================================
//	Interupt Service Routine
//	this a function reserved for interrupt service routine
//	User may need it in advance development of the program
//=====================================================================================
#pragma interrupt ISRHigh
void ISRHigh(void)
{

}

#pragma interrupt ISRLow
void ISRLow(void)
{

}

