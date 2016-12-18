#include <msp430G2553.h>

/*
 * EE5203 Microprocessors
 *
 * Experiment 9: Low current Unipolar Stepper motor driving
 * Model: PHILIPS MB11
 * Pin Sequence: Y_2, Y_1, G_2, G_1 (Red: Ground)
 *
 * By button press, motor is rotated 7.5 degrees.
 * After a complete cycle (48 steps), button is disabled.
 *
 * Author: Guray GURKAN
 * Oct, 2016
*/
char data[4]={BIT0, BIT1, BIT2, BIT3}; //WAVE drive

volatile int steps = 0;

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	P1DIR &= ~BIT3;
	P1IE  |= BIT3;
	P1REN |= BIT3;
	P1OUT |= BIT3;
	P1IFG &= ~BIT3;
	P2DIR = 0xFF;
	_BIS_SR(LPM0_bits + GIE);
}

#pragma vector=PORT1_VECTOR
__interrupt void singlestep()
{
	P1IFG &= ~BIT3;
	P2OUT = data[steps % 4];
	steps++;
	_delay_cycles(100000);
	if (steps==48)
		P1IE &= ~BIT3;
}


