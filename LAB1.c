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
#define LED1 LATDbits.LATD0 
#define LED2 LATDbits.LATD1
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

/*--- MAIN: FUNCTION ----------------------------------------------------------
 ----------------------------------------------------------------------------*/
void main( void )
{
	ANSELD = 0x00;
	TRISD = 0x00;
	LED1 = TRUE;
	LED2 = FALSE;
	setOsc4MHz();
	while(TRUE)
	{
		Delay10KTCYx(DELAYCOUNT);
		LED1 = !LED1;
		LED2 = !LED2;
	}
	
} // eo main::
