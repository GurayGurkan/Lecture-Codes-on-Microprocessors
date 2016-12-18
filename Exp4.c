#include <msp430.h>

/*
 * EE5203 Microprocessors
 *
 * Experiment 4:
 * Using TimerA and related interrupt vectors
 * There are two interrupt sources:
 *
 * 1) TimerA overflow (16bit) interrupt
 *
 * 2) TimerA Capture and Compare Interrupt
 *
 *
 * Author: Guray GURKAN
 * Oct, 2016
 */

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

	DCOCTL = CALDCO_1MHZ;
	BCSCTL1 = CALBC1_1MHZ;
	P1DIR |= 0x01;							// P1.0 output

	//	****** This part configures Timer0_A1 (CCI) Interrupt *******************
	//  TACCR0 = 6500;
	//	TACCTL0 = CCIE;                 // CCR0 interrupt enabled
	//	TACTL = TASSEL_2 + MC_1 + ID_3; // SMCLK, up.mode, DIV = 1/8
	// **************************************************************************

	//	****** This part configures Timer0_A0 (TAI) Oveflow Interrupt *************
	TACTL = TASSEL_2 + MC_2 + ID_3 + TAIE; // SMCLK, cont.mode, DIV = 1/8, TAR interrupt enabled
	// ***************************************************************************

	_BIS_SR(LPM1_bits + GIE);
}

#pragma vector=TIMER0_A1_VECTOR // TAIFG
__interrupt void Timer_1 (void)
{
	TACTL &= ~TAIFG;
	P1OUT ^= 0x01;// Toggle P1.0
}


#pragma vector=TIMER0_A0_VECTOR // CCIFG of TACCR0
__interrupt void Timer_2 (void)
{
	P1OUT ^= 0x01;// Toggle P1.0
}
