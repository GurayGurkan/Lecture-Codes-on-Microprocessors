#include <msp430g2553.h>

/*
 * EE5203 Microprocessors
 *
 * Experiment 2: Using Button Interrupts
 *
 * The green led is toggled after every button (P1.3) press.
 *
 * Author: Guray Gurkan
 * Oct, 2016
 */

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	P1DIR |= 0x41;	// P1.0 and P1.6 are outputs
	P1DIR &= ~0x08;	// P1.3 is input
	P1OUT |= 0x08;	// P1.3 is Pulled-up
	P1OUT &= ~0x41;	// P1.0 and P1.6 are LOW
	P1REN |= 0x08;	// Pull-up resistor enabled
	P1IFG &= ~0x08;	// P1.3 interrupt flag cleared
	P1IE  |= 0x08;	// P1.3 interrupt cap. enabled
	_BIS_SR(GIE+LPM4_bits);	// Sleep and wait for button press

}

#pragma vector = PORT1_VECTOR
__interrupt void buttonISR(void)
{
	P1IFG &= ~0x08; //Clear Interrupt Flag
	P1OUT ^= 0x40;	//Toggle GREEN led
}
