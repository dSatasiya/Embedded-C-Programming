/*-----------------------------------------------------------------------------
	File Name:	ELNC6007DSLab4.c
	Author:		Dhruv Satasiya
	Date:		16/10/2023
	Modified:	None
	© Fanshawe College, 2023

		Description: This code is to understand how timer exactly works. This tells us the
				 exact functionality of the timer result byte(TMR0), timer ON bit(T0CONbits.TMROON)
				 and the flag bit of INTCONbits.TMR0IF.
	
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
#define LED2 LATDbits.LATD0 
#define LED1 LATDbits.LATD1
#define LED4 LATDbits.LATD2
#define LED3 LATDbits.LATD3

//defining port pin
#define PB1 PORTAbits.RA4  // PB1 will be high.
#define PB2 PORTAbits.RA5
#define PB3 PORTAbits.RA6
#define PB4 PORTAbits.RA7

#define PBMASK 0xF0
#define NOPRESS 0xF0
#define LEDMASK 0x0F

//defining ADC channel and resolution
#define ADCCHAN 0
#define ADCRES (5/1024)

#define LEVEL1	128
#define LEVEL2  256
#define LEVEL3  512
#define LEVEL4  768

#define HIGHERTHANONE 0x0000       //1.048576 second
#define T0FLAG INTCONbits.TMR0IF
#define TMRON T0CONbits.TMR0ON
#define BYTESIZE 8

#define DELAYCOUNT 100

void setOsc4MHz();
void configPorts();
void configADC();
int sampleADC(char);
void systemInitialization();
void resetTMR0(int);
void configTMR0(int);

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

void resetTMR0(int psc)
{
	T0FLAG = FALSE;          // T0FLAG is not actual register or bit-field, it is just a macro.
	TMR0H = psc >> BYTESIZE;
	TMR0L = psc;
}// eo resetTMR0 ::

void configTMR0(int psc)
{
	resetTMR0(psc);  // Here in resetTMR0, TMR0 is actual 16-bits(2 Bytes) register.
	T0CON = 0x13; 
}// eo configTMR0 ::

void systemInitialization()
{
	setOsc4MHz();
	configPorts();
	configADC();
	configTMR0(HIGHERTHANONE);
	
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
/*int sampleADC(char chID)
{
	ADCON0bits.CHS = chID;  // gets the channel ID
	ADCON0bits.GO = TRUE;   // makes the GO bit high to start the ADC 
	
	while(ADCON0bits.GO);   // Converting......
	
	return ADRES; 
	
}// eo sampleADC ::*/
/*--- MAIN: FUNCTION ----------------------------------------------------------
 ----------------------------------------------------------------------------*/
void main( void )
{
	char count = 0;
	systemInitialization();
	
	//T0CONbits.TMR0ON = TRUE;
	//timerVal = TMR0;
	
	/*TMRON = TRUE;

	while(1)
	{
		LED1 = TRUE;
		LED2 = TRUE;
		LED3 = TRUE;
		LED4 = TRUE;
		while(T0FLAG)
		{
			LED1 = FALSE;
			LED2 = FALSE;
			LED3 = FALSE;
			LED4 = FALSE;
			Delay10KTCYx(DELAYCOUNT);
			resetTMR0(HIGHERTHANONE); // Auto reset by DELAYCOUNT
			/*if(PB1 == FALSE) // Reset by Push Button-1
			{
				resetTMR0(HIGHERTHANONE);
			}
			
		}
		
	}*/ //eo indefinite while

	while(1)
	{
		int pbState = PORTA;
		//char lastState = 0xF0;
		pbState = (pbState & PBMASK);
		if (pbState != NOPRESS)
		{
			switch(pbState)
			{
				case 0xE0:
					//LED1 = ~(pbState>>4);
					TMRON = TRUE;
					break;
				case 0xD0:
					TMRON = FALSE;
					break;
				case 0xB0:
					count = 0;
					LATD = 0x00;
					break;
				default:
					break;	
			}
		}
		if(T0FLAG == TRUE)
		{
			resetTMR0(HIGHERTHANONE);
			count++;
			LATD = count & LEDMASK;		
		}
		
	}// eo while::

} // eo main::
