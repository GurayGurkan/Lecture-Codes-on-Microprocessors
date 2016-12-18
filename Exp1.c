#include <msp430g2553.h>

/*
 * EE5203 Microprocessors
 *
 * Experiment 1:
 * Basic type of software toggling of two leds via finite number of loops.
 * Initial states for Red (P1.0) and Green (P1.6) leds are OFF and ON, respectively.
 *
 * Variable "i" determines the toggling period of Leds (almost) in CPU cycles.
 * Variable "j" determines the duration of toggling.
 *
 * Author: Guray GURKAN
 * Oct, 2016
 */


int main(void) {
    WDTCTL = WDTPW | WDTHOLD;      	//Stop Watchdog Timer

    P1DIR |= 0x41;

    volatile long int i,j;
    P1OUT = 0x40;
    j=0;
    while(j<1000)						//Finite loop
    {
      i = 30000;                     	//Delay
      do (i--);
      while (i !=0);

      P1OUT ^= 0x41;              	//Toggle leds using an exclusive-OR
      j++;
    }
  }
