// main_SHT21.c
//
//****************************************************************************************************
// Author:
// 	Nipun Gunawardena
//
// Credits:
//	Borrows from Texas Instruments' sht21 library.
//
// Requirements:
//
//
// Description:
// 	Interface with Sensirion SHT21 to measure humidity without driverlib
//
// Notes:
//
// Todo:
//	Make more durable, timeouts, testing, etc.
//****************************************************************************************************



// Includes ------------------------------------------------------------------------------------------
#include <stdint.h>
#include <msp430.h>
#include "shtLib.h"
#include <string.h>
#include <stdio.h>


/**
 * Initialize UCA0 module in UART mode with boud rate 9600
 */
void initUARTA0()
{
	// Configure GPIO
	P2SEL1 |= BIT0 | BIT1;                    // USCI_A0 UART operation
	P2SEL0 &= ~(BIT0 | BIT1);
	// Configure USCI_A0 for UART mode
	UCA0CTLW0 = UCSWRST;                      // Put eUSCI in reset
	UCA0CTLW0 |= UCSSEL__SMCLK;               // CLK = SMCLK
	// Baud Rate calculation
	// 1000000/(16*9600) = 6.5104167
	UCA0BR0 = 6;                             // 1000000/16/9600
	UCA0BR1 = 0x00;
	UCA0MCTLW |= UCBRS0 + UCBRF_8 + UCOS16;
	UCA0CTLW0 &= ~UCSWRST;                    // Initialize eUSCI
//	UCA0IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt
}

void sendByteUARTA0(unsigned char byte)
{
	while(!(UCA0IFG&UCTXIFG));
	UCA0TXBUF = byte;
}

/**
 * Initialize UCA1 module in UART mode with boud rate 9600
 */
void initUARTA1()
{
	// Configure GPIO
	P2SEL1 |= BIT5 | BIT6;                    // USCI_A1 UART operation
	P2SEL0 &= ~(BIT5 | BIT6);
	// Configure USCI_A0 for UART mode
	UCA1CTLW0 = UCSWRST;                      // Put eUSCI in reset
	UCA1CTLW0 |= UCSSEL__SMCLK;               // CLK = SMCLK
	// Baud Rate calculation
	// 1000000/(16*9600) = 6.5104167
	UCA1BR0 = 6;                             // 1000000/16/9600
	UCA1BR1 = 0x00;
	UCA1MCTLW |= UCBRS0 + UCBRF_8 + UCOS16;
	UCA1CTLW0 &= ~UCSWRST;                    // Initialize eUSCI
//	UCA1IE |= UCRXIE;                         // Enable USCI_A1 RX interrupt
}

void sendByteUARTA1(unsigned char byte)
{
	while(!(UCA1IFG&UCTXIFG));
	UCA1TXBUF = byte;
}

char buffer[20];
int i=0, c=0;

// Main ----------------------------------------------------------------------------------------------
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;       // Stop WDT

	// Configure GPIO
	P1OUT &= ~BIT0;                           // Clear P1.0 output latch
	P3DIR |= BIT7;                            // For LED
	P1SEL1 |= BIT6 | BIT7;                    // I2C pins

	P3DIR |= BIT2;		// 3.2 = DE, 3.3 = RE
	P3OUT |= BIT2;		// DE enable hight, RE hight-impedence

	// Disable the GPIO power-on default high-impedance mode to activate
	// previously configured port settings
	PM5CTL0 &= ~LOCKLPM5;

	// Clock setup
	CSCTL0_H = CSKEY >> 8;                    // Unlock CS registers
	CSCTL1 = DCOFSEL_0 | DCORSEL;             // Set DCO to 1MHz
	CSCTL2 = SELA__VLOCLK | SELS__DCOCLK | SELM__DCOCLK; 	// Set MCLK = DCO
	CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1;     // Set all dividers to 1
	CSCTL4 &= ~LFXTOFF;						// Turn on LFXT

	// Lock CS registers - Why isn't PUC created?
	CSCTL0_H = 0;

	initUARTA0();
	initUARTA1();

	// Enable interrupts
	__bis_SR_register(GIE);

	__delay_cycles(10000);

//	  g_temp = 0.0f;
//	  g_hum = 0.0f;
//
//	  // Read Temperature
//	  SHT21ReadTemperature();
//
//	  // Read Humidity
//	  SHT21ReadHumidity();
//
//	  g_temp = g_temp;
//
//	  g_hum = g_hum;

	//char buff[12] = {'C','i','a','o',' ','m','o','n','d','o','\n','\0'};
	unsigned char buff[50];
	int i = 0;
	int d1 = 0;
	float f2 = 0;
	int d2 = 0;

	for(;;) {
		volatile unsigned int i;            // volatile to prevent optimization

		// Read Temperature
		SHT21ReadTemperature();
//		// Read Humidity
//		SHT21ReadHumidity();

		d1 = g_temp;            // Get the integer part (678).
		f2 = g_temp - d1;     // Get fractional part (678.0123 - 678 = 0.0123).
		d2 = (int)(f2 * 10000); // Or this one: Turn into integer.

		buff[0]='\0';
		sprintf(buff, "T:%d.%d\n", d1, d2);
		for(i=0;i<strlen(buff);i++)
		{
			sendByteUARTA0(buff[i]);
			sendByteUARTA1(buff[i]);
		}

//		d1 = g_hum;            // Get the integer part (678).
//		f2 = g_hum - d1;     // Get fractional part (678.0123 - 678 = 0.0123).
//		d2 = (int)(f2 * 10000); // Or this one: Turn into integer.
//
//		buff[0]='\0';
//		sprintf(buff, "Hum: %d.%d\n", d1, d2);
//		for(i=0;i<strlen(buff);i++)
//		{
//			sendByteUARTA1(buff[i]);
//		}

		P3OUT ^= BIT7;                      // Toggle P3.7 using exclusive-OR

		__delay_cycles(1000000);
		__delay_cycles(1000000);
		__delay_cycles(1000000);
		__delay_cycles(1000000);
		__delay_cycles(1000000);
		__delay_cycles(1000000);
	}
}




// Interrupts ----------------------------------------------------------------------------------------

// Timer B1 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_B0_VECTOR))) Timer0_B0_ISR (void)
#else
#error Compiler not supported!
#endif
{
	TB0CTL &= ~MC_3;
	__bic_SR_register_on_exit(LPM3_bits); 	// Exit LPM3
}


//#pragma vector=USCI_A1_VECTOR
//__interrupt void USCI_A1_ISR(void)
//{
//	switch(__even_in_range(UCA1IV,4))
//	{
//	case 0:break;                             // Vector 0 - no interrupt
//	case 2:                                   // Vector 2 - RXIFG
//		buffer[c] = UCA1RXBUF;              // the recieved data is store on buffer variable
//
//		if(buffer[c++]=='\0')
//		{
//			c=0;
//			for(i=0;buffer[i]!='\0';i++)
//			{
//				sendByteUARTA1(buffer[i]);
//			}
//		//		  __no_operation();
//		//		  __bic_SR_register_on_exit(LPM0_bits);   // Exit active CPU
//		}
//	  break;
//	case 4:break;                             // Vector 4 - TXIFG
//	default: break;
//  }
//}


