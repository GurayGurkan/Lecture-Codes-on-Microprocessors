#include <msp430g2553.h>
#include "lcdLib.h"

/*
 * EE5203 Microprocessors
 *
 * Experiment 6: LCD Basics
 *
 * MSP430 Pins
 * -----------
 * P2.0 -> LCD D4
 * P2.1 -> LCD D5
 * P2.2 -> LCD D6
 * P2.3 -> LCD D7
 * P2.4 -> LCD E
 * P2.5 -> LCD RS
 *
 * Author: Guray GURKAN
 * Oct, 2016
 */

unsigned char name[6]={'M','S','P','4','3','0'};


int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	lcdInit();
	delay_ms(1);
	lcdWriteCmd(0x80 | 0x40 |8);
	unsigned char i =0;

	for (i=0;i<6;i++)
	{
		//lcdWriteCmd(0x80 | 0x40 | i+5);
		lcdWriteData(name[i]);
		delay_ms(200);
	}
}
