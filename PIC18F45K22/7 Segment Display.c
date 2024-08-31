/*=============================================================================
	File Name:	7 Segment.c  
	Author:		Dhruv Satasiya
	Date:		27/07/2024
	Modified:	None
	© Fanshawe College, 2024

	Description: This code is to print numbers on 7 segment display with the help
				 of PIC18F45K22 microcontroller.
=============================================================================*/

/* Preprocessor ===============================================================
   Hardware Configuration Bits ==============================================*/
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

// Libraries ==================================================================
#include <p18f45k22.h>
#include <stdio.h>
#include <stdlib.h>
#include <delays.h>
#include <usart.h>

// Constants  =================================================================
#define TRUE	1	
#define FALSE	0

#define DELAYCOUNT 50

// Timer's constants
#define TFLAG INTCONbits.TMR0IF
#define TMR0ON T0CONbits.TMR0ON
#define POINTONESEC 0x3CB0
#define BYTESIZE 8

// 7 Segment Display Constants
#define A LATDbits.LATD5
#define B LATDbits.LATD4
#define C LATDbits.LATD2
#define D LATDbits.LATD1
#define E LATDbits.LATD0
#define F LATDbits.LATD6
#define G LATDbits.LATD7	
#define DP LATDbits.LATD3
#define TOTAL_DIGITS 10


// Global Variables  ==========================================================
typedef char number_t;

number_t digitsArray[TOTAL_DIGITS] = {0x80, 0xE3, 0x44, 0x41, 0x23, 0x11, 0x10, 0xC3, 0x00, 0x01};

// Function Prototype ======================================================

// Functions  =================================================================

/*>>> setOsc: ===========================================================
Author:		Dhruv Satasiya
Date:		27/07/2024
Modified:	None
Desc:		sets the internal oscillator at 4MHz frequency. 
Input: 		None
Returns:	None
============================================================================*/
void setOsc(void)
{
	OSCCON = 0x52;		//Oscillator is set for 4MHz.
	while(!OSCCONbits.HFIOFS);
	
} // eo setOsc::

/*>>> setPorts: ===========================================================
Author:		Dhruv Satasiya
Date:		27/07/2024
Modified:	None
Desc:		sets the I/O ports. 
Input: 		None
Returns:	None
============================================================================*/
void setPorts(void)
{
	/* ---PORT - A configuration--- */
	//ANSELA = 0x07;   // RA0, RA1, RA2 are set as analog pins.
	//LATA = 0x00;
	//TRISA = 0xFF;  // as they are pushbuttons and ADC pins, already as inputs by default.
	/* ---PORT - B configuration--- */
	//ANSELB = 0x00;
	//LATB = 0x00;
	//TRISB = 0x00;
	/* ---PORT - C configuration--- */
	//ANSELC = 0x00;
	//LATC = 0x00;
	//TRISC = 0xC0;   // setting the TX and RX pins as input pins.
	/* ---PORT - D configuration--- */
	ANSELD = 0x00;
	LATD = 0x00;
	TRISD = 0x00;	
} 
// eo setPorts::

/*>>> resetTimer0: ===========================================================
Author:		Dhruv Satasiya
Date:		27/07/2024
Modified:	None
Desc:		resets the timer0 and makes the timer flag false again.
Input: 		psc
Returns:	None
============================================================================*/
void resetTimer0(int psc)
{
	TFLAG = FALSE;
	TMR0H = psc >> BYTESIZE;
	TMR0L = psc;
	
} // eo resetTimer0::

/*>>> setTimer0: ===========================================================
Author:		Dhruv Satasiya
Date:		27/07/2024
Modified:	None
Desc:		sets the timer for 16-bits, high to low transition, and prescaler. 
Input: 		psc
Returns:	None
============================================================================*/
void setTimer0(int psc)
{
	resetTimer0(psc);
	T0CON = 0x10;

} // eo setTimer0::

/*>>> systemInit: ===========================================================
Author:		Dhruv Satasiya
Date:		27/07/2024
Modified:	None
Desc:		Calls all the basic setting functions to initialize the system.
Input: 		None
Returns:	None
============================================================================*/
void systemInit(void)
{
	setOsc();
	setPorts();
	setTimer0(POINTONESEC);
		
} // eo systemInit::

/*=== MAIN: FUNCTION ==========================================================
 ============================================================================*/
void main( void )
{
	char digitIndex = 0;
	char oneSecCount = 0;
	
	systemInit(); 			// Initializing the system...
	
	TMR0ON = TRUE;			// Turning the timer ON...
	
	while(TRUE)
	{
		if(TFLAG)
		{
			resetTimer0(POINTONESEC);
			oneSecCount++;
			if(oneSecCount >= 10)
			{
				oneSecCount = FALSE;
				LATD = digitsArray[digitIndex];
				digitIndex++;
				if(digitIndex >= TOTAL_DIGITS)
				{
					digitIndex = FALSE;
				} // eo if digitIndex >= 10
			} // eo one sec if	
		} // eo timer flag if
			
	} // eo indefinite while
} // eo main::


	
