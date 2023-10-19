/*-----------------------------------------------------------------------------
	File Name:	ELNC6007DSLab2.c
	Author:		Dhruv Satasiya
	Date:		18/09/2023
	Modified:	None
	© Fanshawe College, 2023

	Description: Developing the programme of blinking LEDs at certain delay.
	
-----------------------------------------------------------------------------*/

/* Preprocessor ---------------------------------------------------------------
   Hardware Configuration Bits ----------------------------------------------*/
#pragma config FOSC		= INTIO67
#pragma config PLLCFG	= OFF
#pragma config PRICLKEN = ON
#pragma config FCMEN	= OFF
#pragma config IESO		= OFF
#pragma config PWRTEN	= OFF 
#pragma config BOREN	= ON
#pragma config BORV		= 285 
#pragma config WDTEN	= OFF
#pragma config PBADEN	= OFF
#pragma config LVP		= OFF
#pragma config MCLRE	= EXTMCLR

// Libraries ------------------------------------------------------------------
#include <p18f45k22.h>
#include <stdio.h>
#include <stdlib.h>
#include <delays.h>

// Constants  -----------------------------------------------------------------
#define TRUE	1	
#define FALSE	0
// defining led pin 	
#define LED4 LATDbits.LATD0 
#define LED3 LATDbits.LATD1
#define LED2 LATDbits.LATD2
#define LED1 LATDbits.LATD3
//defining port pin
#define PB1 PORTAbits.RA4  // PB1 will be high.
#define PB2 PORTAbits.RA5
#define PB3 PORTAbits.RA6
#define PB4 PORTAbits.RA7

#define PBMASK 0xF0    // This is = 1111 0000
#define NOPRESS 0xF0   // = 1111 0000


#define DELAYCOUNT 50

// Global Variables  ----------------------------------------------------------

/*-----------------------------------------------------------------------------
	File Name:	ELNC6007DSLab2.c
	Author:		Dhruv Satasiya
	Date:		18/09/2023
	Modified:	None
	© Fanshawe College, 2023

	Description: Ocsillator function to set the 4MHz of oscillator frequency.
	
-----------------------------------------------------------------------------*/

void setOsc4MHz()
{
	OSCCON = 0x52;
	while(!OSCCONbits.HFIOFS);
}// eo setOsc4MHz::

void configPorts()
{
	// configuring portD
	ANSELD = 0x00;  // LED configuration.
	TRISD = 0x00;
	LATD = 0x00;
	// configuring portA
	ANSELA = 0x00;  // PORT configuration.
	//TRISA = 0x00;
}//eo configPorts::

/*--- MAIN: FUNCTION ----------------------------------------------------------
 ----------------------------------------------------------------------------*/
void main( void )
{
	configPorts();
	setOsc4MHz();
	
	while(TRUE)
	{
		/*LED1 = !PB1; // Turning on the LED1
		LED2 = !PB2; // Turning on the LED2
		LED3 = !PB3; // Turning on the LED3
		LED4 = !PB4; // Turning on the LED4*/

		/*LED1 = PB1;
		LED2 = PB2;
		LED3 = PB3;
		LED4 = PB4;*/
		
		LATD = ~PORTA;  // LATD = 0000 0000 and PORTA = 1111 0000 and 
						//                     ~PORTA = 0000 1111

	}// eo while

} // eo main::
