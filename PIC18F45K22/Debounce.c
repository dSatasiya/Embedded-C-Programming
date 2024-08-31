/*-----------------------------------------------------------------------------
	File Name:	push_button_debounce.c
	Author:		Dhruv Satasiya
	Date:		08/01/2023
	Modified:	None
	© Fanshawe College, 2023

	Description: This is the code to demonstrate how debounce works while 
				 working with the push buttons and the LEDs. 
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

//defining LED
#define LED1 LATBbits.LATB0

// defining push button
#define pb1 PORTAbits.RA4

#define PBMASK 0xF0
#define NOPRESS 0xF0
#define DELAYCOUNT 20

// Function Prototyping.
void setOsc4MHz();
void configPorts();
void systemInitialization();

/*>>>> setOsc4MHZ: -----------------------------------------------------------------------------
	Author:		Dhruv Satasiya
	Date:		30/10/2023
	Modified:	None
	Description:Ocsillator function to set the 4MHz of oscillator frequency.
	Input:      None
	Return:    None
-----------------------------------------------------------------------------*/
void setOsc4MHz()
{
	OSCCON = 0x52;      // 0101 0010
	while(!OSCCONbits.HFIOFS);
}// eo setOsc4MHz::

/*>>>> configPorts: -----------------------------------------------------------------------------
	Author:		Dhruv Satasiya
	Date:		30/10/2023
	Modified:	None
	Description:Configures I/O ports, ANSELx, LATx and TRISx.
	Input:      None
	Return:    None
-----------------------------------------------------------------------------*/
void configPorts()
{
	// configuring portD
	ANSELB = 0x00; 
	LATB = 0x00;
	TRISB = 0x00;
	
	// configuring portA
	ANSELA = 0x01;  
}//eo configPorts::

/*>>>> systemInitialization: -----------------------------------------------------------------------------

	Author:		Dhruv Satasiya
	Date:		30/10/2023
	Modified:	None
	Description:calls all the function for the system initialization.
	Input:      None
	Return:     None
-----------------------------------------------------------------------------*/
void systemInitialization()
{
	setOsc4MHz();
	configPorts();
}// eo systemInitialization ::

/*--- MAIN: FUNCTION ----------------------------------------------------------
 ----------------------------------------------------------------------------*/
void main( void )
{
	char pbState = 0;
	
	systemInitialization();

	while(TRUE)
	{
		pbState = PORTA;
		pbState = pbState & PBMASK;
		if(pbState != NOPRESS)
		{
			Delay1KTCYx(DELAYCOUNT);
			switch(pbState)
			{
				case 0xE0:
					 LED1 = !pb1;
					 break;

				default:
					 break;
			}
		}
	}// eo while :: 
	
	
}// eo main ::
