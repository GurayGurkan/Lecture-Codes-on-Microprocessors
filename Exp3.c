#include "msp430g2553.h"

/*
 * EE5203 Microprocessors
 *
 * Experiment 3: Seven-segment display driving via MPS430
 *
 * P2.3 is configured as a pulled-up input button.
 * On each button press, the number on display is increased by one.
 * 7-segment leds are driven via predefined byte array.
 *
 *
 * Author: Guray Gurkan
 * Oct, 2016
 */

char seg[] = {0x3F, 0x06, 0x5B,0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F,0x6F};

unsigned int n;

void main( void )
{
	WDTCTL = WDTPW + WDTHOLD;
	DCOCTL  = CALDCO_1MHZ;
	BCSCTL1 = CALBC1_1MHZ;
	P1DIR |= 0xFF;
	P1OUT = ~seg[0];

	P2DIR &= ~0x08;	// P2.3 is input
	P2OUT |= 0x08;	// P2.3 is Pulled-up

	P2REN |= 0x08;	// Pull-up resistor enabled
	P2IFG &= ~0x08;	// P2.3 interrupt flag cleared
	P2IE  |= 0x08;	// P2.3 interrupt cap. enabled
	n=0;
	_BIS_SR(GIE+LPM4_bits);

}

#pragma vector=PORT2_VECTOR
__interrupt void characters(void)
{
	P2IFG &= ~0x08;
	n++;
	P1OUT = ~seg[n % 10];
}
