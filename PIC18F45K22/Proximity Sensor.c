/*-----------------------------------------------------------------------------
	File Name:	Proximity.c
	Author:		Dhruv Satasiya
	Date:		29/08/2024
	Modified:	None
	© Fanshawe College, 2024

	Description: Developing the programme of Proximity sensor detection and
				 turning ON and OFF the light accordingly.
	
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
#include <usart.h>


// Constants  -----------------------------------------------------------------
#define TRUE				1	
#define FALSE				0
#define ON 					1
#define OFF					0

#define DELAYCOUNT 			50

// defining led pin 	
#define LIGHT 				LATDbits.LATD0 
#define BUZZER 			LATDbits.LATD1
#define PROXIMITY			PORTAbits.RA2
#define BUZZER_DELAY		100

// Global Variables  ==========================================================

// Function Prototype ======================================================
void setOsc(void);
void configPorts(void);
void systemInit(void);

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
	ANSELA = 0x00;      // All pins set to digital pins
	LATA = 0x00;		  // 
	TRISA = 0x04;  	  // RA2 pin set as Input to read the proximity sensor
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
		
} // eo systemInit::


/*--- MAIN: FUNCTION ----------------------------------------------------------
 ----------------------------------------------------------------------------*/
void main( void )
{
	systemInit();											// System Initialization Function

	while(TRUE)
	{
		//LED = TRUE;	
		if(PROXIMITY == FALSE)
		{
			Delay10KTCYx(DELAYCOUNT);					// delay to let the LIGHT toggle.
			LIGHT = !LIGHT;								// Turning the light ON when hand wave or 
																//motion is detected.
			BUZZER = OFF;									// relay did not work it could be faulty
			Delay10KTCYx(BUZZER_DELAY);
			BUZZER = ON;

		} //when proximity is ON

	}// eo while

} // eo main::

