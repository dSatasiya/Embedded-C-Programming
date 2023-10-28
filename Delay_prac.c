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
#define LED1 LATDbits.LATD3

#define DELAYCOUNT 100

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
{;
	setOsc4MHz();
	
	
	while(TRUE)
	{
		LED1 = TRUE;
		Delay10KTCYx(DELAYCOUNT);
		LED1 = FALSE;	
		Delay10KTCYx(DELAYCOUNT);
	}// eo while

} // eo main::


// Important point to be noted: We cannot use the DELAYCOUNT value greater than 
// 255 or lesser than 1 [1, 255] as our all the delay functions have argument of 
// unsigned char. So default prototyping of the DelayaXTCYx()is :
// void Delay1KTCYx( unsigned char unit );
