#include <msp430.h>

/*
 * EE5203 Microprocessors
 *
 * Experiment 7-a: Continuous ADC Operation (1)
 *
 * Using endless loop, ADC operation is achieved continuously.
 * CPU is put to sleep after initiation of ADC operation and
 * then waken up when ADC operation is completed.
 *
 * ADC interrupt is used to wake up CPU as soon as ADC operation
 * is completed.
 *
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
  for (;;)
  {
    ADC10CTL0 |= ENC + ADC10SC;            // Sampling and conversion start
    _BIS_SR(CPUOFF + GIE);     	// LPM0, ADC10_ISR will force exit
    P1OUT ^= 0x01;                       	// Toggle P1.0 LED
  }
}
#pragma vector=ADC10_VECTOR
__interrupt void wakeupCPU(void)
{
  _BIC_SR_IRQ(CPUOFF);	// Clear CPUOFF bit from 0(SR)
}
