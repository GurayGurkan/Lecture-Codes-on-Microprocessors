#include <msp430.h>

/*
 * EE5203 Microprocessors
 *
 * Experiment 7-b: Continuous ADC Operation (2)
 *
 * Using only ADC interrupt, ADC operation is achieved continuously.
 * ADC operation is triggered once and CPU is put to sleep in main( ) function.
 * Then, when the first ADC operation is completed, the ADC interrupt is genererated.
 * In ADC ISR, the ADC operation is triggered once again and the Led is toggled.
 * By continuous ADC triggering in ADC ISR, a continouos ADC operation is achieved.
 *
 * Author: Guray GURKAN
 * Oct, 2016
 */

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
	ADC10CTL0 = ADC10SHT_2 + ADC10ON + ADC10IE; // ADC10ON, interrupt enabled
	ADC10CTL1 = INCH_1 + ADC10DIV_7;                       // input A1, divide by 8
	ADC10AE0 |= BIT1;                        	 // PA.1 ADC option select
	P1DIR |= 0x01;                            	// Set P1.0 to output direction
	ADC10CTL0 |= ENC + ADC10SC;            // Sampling and conversion start
	_BIS_SR(CPUOFF + GIE);
}

#pragma vector=ADC10_VECTOR
__interrupt void wakeupCPU(void)
{
	P1OUT ^= 0x01;                       	// Toggle P1.0 LED
	ADC10CTL0 |= ADC10SC;
}
