#include <msp430G2553.h>

/*
 * EE5203 Microprocessors
 *
 * Experiment 9: Low current Unipolar Stepper motor driving (2)
 * Model: PHILIPS MB11
 * Pin Sequence: Y_2, Y_1, G_2, G_1 (Red: Ground)
 *
 * Using TimerA, motor is rotated continously.
 *
 * Author: Guray GURKAN
 * Oct, 2016
*/

char data[4]={BIT0,BIT1,BIT2,BIT3}; //WAVE drive

volatile int i=0;

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	TACTL = TASSEL_2 | MC_1 | ID_3;
	TACCR0 = 62500;
	TACCTL0 = CCIE;
	P2DIR = 0xFF;
	_BIS_SR(GIE);
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TimerISR()
{
	P2OUT = data[i % 4];
	i++;
}


