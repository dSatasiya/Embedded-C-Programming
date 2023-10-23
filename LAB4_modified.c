/*-----------------------------------------------------------------------------
	File Name:	ELNC6007DSLab4.c
	Author:		Dhruv Satasiya
	Date:		16/10/2023
	Modified:	None
	© Fanshawe College, 2023

	Description: Developing the programme for analog to digital conversion. 
				 It reads the value of resistance and according to the different levels,
                 it turns the LEDs ON only when PB1 is pressed. 
	
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

#define PBMASK 0xF0

//defining ADC channel and resolution
#define ADCCHAN 0
#define ADCRES (5/1024)

#define LEVEL1	128
#define LEVEL2  256
#define LEVEL3  512
#define LEVEL4  768

#define DELAYCOUNT 50

void setOsc4MHz();
void configPorts();
void configADC();
int sampleADC(char);
void systemInitialization();

// Global Variables  ----------------------------------------------------------

/*>>>> setOsc4MHZ: -----------------------------------------------------------------------------
	File Name:	ELNC6007DSLab4.c
	Author:		Dhruv Satasiya
	Date:		16/10/2023
	Modified:	None
	Description:Ocsillator function to set the 4MHz of oscillator frequency.
	Input:      None
	Return:    None
-----------------------------------------------------------------------------*/
void setOsc4MHz()
{
	OSCCON = 0x52;
	while(!OSCCONbits.HFIOFS);
}// eo setOsc4MHz::

/*>>>> configPorts: -----------------------------------------------------------------------------
	File Name:	ELNC6007DSLab4.c
	Author:		Dhruv Satasiya
	Date:		16/10/2023
	Modified:	None
	Description:Configures I/O ports, ANSELx, LATx and TRISx.
	Input:      None
	Return:    None
-----------------------------------------------------------------------------*/
void configPorts()
{
	// configuring portD
	ANSELD = 0x00; 
	LATD = 0x00;
	TRISD = 0x00;
	
	// configuring portA
	ANSELA = 0x01;  
}//eo configPorts::

/*>>>> configADC: -----------------------------------------------------------------------------
	File Name:	ELNC6007DSLab4.c
	Author:		Dhruv Satasiya
	Date:		16/10/2023
	Modified:	None
	Description:Configures ADCx registers.
	Input:      None
	Return:     None
-----------------------------------------------------------------------------*/
void configADC()
{
	ADCON0 = 0x01;  // 0000 0001, AN0 selected.
	ADCON1 = 0x00;  // 0000 0000, voltage references selected, VDD and VSS.
	ADCON2 = 0xA9;  // 1010 1001, Right Justified, 12TAD as Acquisition Time and 
					// Conversion Clock select = FOSC/8
}// eo configADC ::

/*>>>> systemInitialization: -----------------------------------------------------------------------------
	File Name:	ELNC6007DSLab4.c
	Author:		Dhruv Satasiya
	Date:		16/10/2023
	Modified:	None
	Description:calls all the function for the system initialization.
	Input:      None
	Return:     None
-----------------------------------------------------------------------------*/
void systemInitialization()
{
	setOsc4MHz();
	configPorts();
	configADC();
} // eo systemInitialization ::

/*>>>> sampleADC: -----------------------------------------------------------------------------
	File Name:	ELNC6007DSLab4.c
	Author:		Dhruv Satasiya
	Date:		16/10/2023
	Modified:	None
	Description:It takes the ADC samples.
	Input:      chID.
	Return:     integer value of ADRES.
-----------------------------------------------------------------------------*/
int sampleADC(char chID)
{
	ADCON0bits.CHS = chID;  // gets the channel ID
	ADCON0bits.GO = TRUE;   // makes the GO bit high to start the ADC 
	
	while(ADCON0bits.GO);   // Converting......
	
	return ADRES; 
	
}// eo sampleADC ::

/*--- MAIN: FUNCTION ----------------------------------------------------------
 ----------------------------------------------------------------------------*/
void main( void )
{

	int adcResult = 0;
	float volts = 0;
	systemInitialization();
	
	while(1)
	{
		int pbState = PORTA;
		pbState = pbState & PBMASK;
	
		if(pbState == 0xE0)
		{
			adcResult = sampleADC(ADCCHAN);
			if (adcResult < LEVEL1)
			{
				LATD = 0x00;
			}
			if(adcResult > LEVEL1)
			{
				LATD = 0x08;
			}
			if(adcResult > LEVEL2)
			{
				LATD = 0x0C;
			}
			if(adcResult > LEVEL3)
			{
				LATD = 0x0E;
			}
			if(adcResult > LEVEL4)
			{
				LATD = 0x0F;
			}
		}
	}// eo while::

} // eo main::
