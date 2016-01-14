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

#define ID 1

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

void gpioLowPower()
{
	 // Configure GPIO

	// -------- BOARD PROFONDITA' --------
	P1OUT = 0xFF;
	P1DIR = 0xFF;

	P2OUT = 0xFF;
	P2DIR = 0xFF;

	P3OUT = 0xFF;
	P3DIR = 0xFF;

	P4OUT = 0xFF;
	P4DIR = 0xFF;

	PJOUT = 0xFF;
	PJDIR = 0xFF;

	// Shout down mode
	P3OUT &= ~BIT2;					// DE enable low
	P3OUT |= BIT3;					// !RE enable hight
	P3DIR |= BIT2 + BIT3;			// 3.2 = DE, 3.3 = RE

	// LED power off
	P3OUT &= ~BIT7;
	P3DIR |= BIT7;

	//    // -------- BOARD SUPERFICE --------
	//  P1OUT = 0x00;
	//  P1OUT = BIT1 + BIT2 + BIT6 + BIT7;
	//  P1DIR = 0x00;
	//  P1DIR = BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5;
	//
	//  P2OUT = 0x00;
	//  P2OUT = BIT2 + BIT4 + BIT5 + BIT6 + BIT7;
	//  P2DIR = 0x00;
	//  P2DIR = BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7;
	//
	//  P3OUT = 0xFF;
	//  P3DIR = 0xFF;
	//
	//  P4OUT = 0x00;
	//  P4OUT = BIT6 + BIT7;
	//  P4DIR = 0x00;
	//  P4DIR = BIT6 + BIT7;
	//
	//  PJOUT = 0x00;
	//  PJOUT = BIT0 + BIT1 + BIT2 + BIT4 + BIT5 + BIT6 + BIT7;
	//  PJDIR = BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7;

	//	// Shout down mode
	//	P3OUT &= ~BIT2;					// DE enable low
	//	P3OUT |= BIT3;					// !RE enable hight
	//	P3DIR |= BIT2 + BIT3;			// 3.2 = DE, 3.3 = RE
	//
	//	// LED power off
	//	P3OUT &= ~BIT7;
	//	P3DIR |= BIT7;
	//
	//	// Radio off
	//	P1OUT |= BIT2;
	//	P1DIR |= BIT2;
	//
	//	// ADCEN off
	//	P2OUT |= BIT2;
	//	P2DIR |= BIT2;
	//
	//	// ADC level low
	//	P2OUT &= ~BIT3;
	//	P2DIR |= BIT3;
	//
	//	// -------- eink --------
	//	// #RST
	//	P1OUT &= ~BIT1;
	//	P1DIR |= BIT1;
	//	// PWM, DCH
	//	P2OUT |= BIT4;
	//	P2OUT &= ~BIT7;
	//	P2DIR &= BIT7;
	//	// #DCS, BUSY
	//	P3OUT |= BIT0;
	//	P3OUT &= ~BIT1;
	//	P3DIR |= BIT0;
	//	P3DIR &= ~BIT0;
	//	// #RST
	//	PJOUT |= BIT0;
	//	PJDIR |= BIT0;
}

void gpioInit()
{
	// Configure GPIO
	P1OUT &= ~BIT0;                           // Clear P1.0 output latch
	P3DIR |= BIT7;                            // For LED
	P1SEL1 |= BIT6 | BIT7;                    // I2C pins

	P3DIR |= BIT2;		// 3.2 = DE, 3.3 = RE
	P3OUT |= BIT2;		// DE enable hight, RE hight-impedence
}

unsigned char buff[50];
volatile unsigned int i=0, c=0;            // volatile to prevent optimization

// Main ----------------------------------------------------------------------------------------------
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;       // Stop WDT

	gpioLowPower();

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

	// Enable interrupts
	__bis_SR_register(GIE);

	__delay_cycles(10000);

	for(;;) {
		volatile unsigned int i;            // volatile to prevent optimization

		gpioInit();
		P3OUT ^= BIT7;                      // Toggle P3.7 using exclusive-OR

		// Read Temperature
		SHT21ReadTemperature();
//		// Read Humidity
//		SHT21ReadHumidity();

		buff[0]='\0';
		sprintf(buff, "T%d:%.2f\n", ID,  g_temp);

		initUARTA0();
		initUARTA1();

		for(i=0;i<strlen(buff);i++)
		{
			sendByteUARTA0(buff[i]);
			sendByteUARTA1(buff[i]);
		}

		P3OUT ^= BIT7;                      // Toggle P3.7 using exclusive-OR
		gpioLowPower();

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

//		P3OUT ^= BIT7;                      // Toggle P3.7 using exclusive-OR

		// Inizializzazione del timer
		TA0CCTL0 = CCIE;                    // TACCR0 interrupt enabled
		TA0CCR0 = 62500 - 1;
		TA0CTL = TASSEL__SMCLK | MC__CONTINOUS;   // SMCLK, continuous mode
		__bis_SR_register(LPM4_bits + GIE);       // Enter LPM3 w/ interrupt
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

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_A0 (void) {		// Timer0 A0 interrupt service routine
	 if (++c == 50) {
			__bic_SR_register_on_exit(LPM4_bits); 	// Exit LPM3
			c=0;
	}
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


