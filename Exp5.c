#include <msp430G2553.h>

/*
 * EE5203 Microprocessors
 *
 * Experiment 5: PWM generation.
 *
 * Using Timer output mode to generate active PWM signal.
 * Timer is configured to directly drive the output on P1.6 pin.
 * PWM period and duty cycle is adjusted via TACCR0 and TACCR1, respectively.
 *
 * Author: Guray GURKAN
 * Oct, 2016
 */

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    DCOCTL = CALDCO_1MHZ;
    BCSCTL1 = CALBC1_1MHZ;

    P1DIR |= BIT6;
    P1SEL |= BIT6;

    TACTL = TASSEL_2 | MC_1 | ID_3;

    TACCR0 = 0xFFFF; 	// T_PWM = ?
    TACCR1 = 0x7FFF; 	// T_ON = ?

    //TA0CCR0 = 2500; 	// T_PWM = ?
    //TA0CCR1 = 127;    // T_ON = ?

    TACCTL1 = OUTMOD_7;
    _BIS_SR(LPM1_bits + GIE);
}





