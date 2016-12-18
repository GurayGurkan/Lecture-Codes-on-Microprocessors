#include <msp430.h> 
#include "lcdLib.h"

/*
 * EE5203 Microprocessors
 *
 * Experiment 8: A simple voltmeter realization
 *
 * Using TimerA interrupt set to 0.5 Hz, ADC result on P1.0 is converted to input voltage.
 * The conversion result is then published on LCD, yielding to a simple Voltmeter.
 *
 * Author: Guray GURKAN
 * Oct, 2016

MSP430 Pins
-----------
P2.0 -> LCD D4
P2.1 -> LCD D5
P2.2 -> LCD D6
P2.3 -> LCD D7
P2.4 -> LCD E
P2.5 -> LCD RS
 */


int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	lcdInit();
	lcdClear();

	TACTL = TASSEL_2 |MC_1 | ID_3;
	TACCR0 = 62500;
	TACCTL0 = CCIE;

	ADC10CTL0 = ADC10SHT_2 | ADC10ON;
	ADC10CTL1 = INCH_1;
	ADC10AE0 |= BIT1; // P1.1
	ADC10CTL0 |= ENC;

	_BIS_SR(GIE);


}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void update_Volt(void)
{
	ADC10CTL0 |= ADC10SC;
	while (ADC10CTL1 & ADC10BUSY); //wait until ADC operation is completed
	lcdClear();

	float i;
	int v, mv;

	i = (float) ADC10MEM *3.515;
	v = i/1000;
	mv = (i - v*1000)*10;

	lcdSetInt(v,0,0);
	lcdSetText(".",1,0);

	if (mv>999)
		lcdSetInt(mv,2,0);
	else if (mv>99)
	{
		lcdSetInt(0,2,0);
		lcdSetInt(mv,3,0);
	}
	else if (mv>9)
	{
		lcdSetText("00",2,0);
		lcdSetInt(mv,4,0);
	}
	else
	{
		lcdSetText("000",2,0);
		lcdSetInt(mv,5,0);
	}
	lcdSetText(" V",7,0);
}
