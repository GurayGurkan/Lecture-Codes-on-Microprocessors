#include <msp430G2553.h>

/*
 * EE5203 Microprocessors
 *
 * Experiment 5 - b: Servo Motor Driving via PWM
 *
 * Servo motor can be driven via 50 Hz PWM signal.
 * To rotate the servo, T_on duration is changed via
 * button P1.3 betwwen 0.5 to 2.5 ms.
 *
 * Author: Guray GURKAN
 * Oct, 2016
 */

volatile int duty=187; //center position

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    DCOCTL = CALDCO_1MHZ;
    BCSCTL1 = CALBC1_1MHZ;

	P1DIR |= BIT6; // | BIT2;
	P1SEL |= BIT6; // | BIT2;
	TACTL = TASSEL_2 | MC_1 | ID_3;

	P1DIR &= ~BIT3;
	P1OUT |= BIT3;
	P1REN |= BIT3;
	P1IE |= BIT3;
	P1IFG &= ~BIT3;

	TACCTL1 =  OUTMOD_7 ;
	TACCR0 = 2500;
	TACCR1 = duty;

	_BIS_SR(GIE);
}

#pragma vector = PORT1_VECTOR
__interrupt void button(void)
{

	duty -=10;
	if (duty<64)
		duty = 312;
	TA0CCR1 =duty;
	P1IFG &= ~BIT3;
	__delay_cycles(1000);
}




