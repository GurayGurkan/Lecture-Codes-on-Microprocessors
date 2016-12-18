#include "msp430g2553.h"

/*
 * EE5203 Microprocessors
 *
 * Experiment 10: Setting up USCI_A0 for UART connection
 *
 * From View->Other->Terminal, the Terminal is openned.
 * Received and Transmitted characters can be seen in terminal.
 *
 * Author: Guray GURKAN
 * Oct, 2016
*/

void main(void)
{
	WDTCTL = WDTPW + WDTHOLD; // Stop the Watch dog

	//------------------- Configure the Clocks -------------------//

	BCSCTL1 = CALBC1_1MHZ;   // Set range
	DCOCTL  = CALDCO_1MHZ;   // Set DCO step + modulation

	//---------------- Configuring the LED's ----------------------//

	P1DIR  |=  BIT0 + BIT6;  // P1.0 and P1.6 output
	P1OUT  &= ~(BIT0 + BIT6);  // P1.0 and P1.6 = 0

	//--------- Setting the UART function for P1.1 & P1.2 --------//

	P1SEL  |=  BIT1 + BIT2;  // P1.1 UCA0RXD input
	P1SEL2 |=  BIT1 + BIT2;  // P1.2 UCA0TXD output

	//------------ Configuring the UART(USCI_A0) Table 15------------//

	UCA0CTL1 |=  UCSSEL_2 + UCSWRST;  // USCI Clock = SMCLK,USCI_A0 disabled
	UCA0BR0   =  6;                 // From datasheet table-
	UCA0BR1   =  0;                 // selects baudrate: 9600, clk = SMCLK
	UCA0MCTL |=  UCBRS_0 + UCBRF_8 + UCOS16;    // Modulation value from datasheet
	UCA0STAT &= ~UCLISTEN;            // loop back mode disabled
	UCA0CTL1 &= ~UCSWRST;             // Clear UCSWRST to enable USCI_A0

	//---------------- Enabling the interrupts ------------------//

	IE2 |= UCA0TXIE;                  // Enable the Transmit interrupt
	IE2 |= UCA0RXIE;                  // Enable the Receive  interrupt
	_BIS_SR(GIE);                     // Enable the global interrupt

	UCA0TXBUF = 'W';                  // Transmit a byte

	_BIS_SR(LPM0_bits + GIE);         // Going to LPM0
}

//-----------------------------------------------------------------------//
//                Transmit and Receive interrupts                        //
//-----------------------------------------------------------------------//

#pragma vector = USCIAB0TX_VECTOR
__interrupt void TransmitInterrupt(void)
{
	P1OUT  |= BIT0;//light up P1.0 Led on Tx
	_delay_cycles(10000);
	P1OUT &= ~BIT0;
	IFG2 &= ~UCA0TXIFG;
}

#pragma vector = USCIAB0RX_VECTOR
__interrupt void ReceiveInterrupt(void)
{
	P1OUT  |= BIT6;     // light up P1.6 LED on RX
	_delay_cycles(10000);
	P1OUT &= ~BIT6;
	IFG2 &= ~UCA0RXIFG; // Clear RX flag
}
