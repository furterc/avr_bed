/*
 * timer1.c
 *
 *  Created on: 12 May 2016
 *      Author: cfurter
 */

#include "timer_two.h"

void (*timerTwoCallback)(void) = 0;

#define RTC_C2_TNT2_reg     0x05


ISR(TIMER2_OVF_vect);

/*** Functions ***/

/* Set up timer1 to interrupt on 1  millisecond intervals */
void timerTwo_init()
{
    /* Select clock source and prescaler clk/128 */
    TCCR2B = (1 << CS22);

    /* Set initial value of Counter */
    TCNT2 = RTC_C2_TNT2_reg;
}

void timerTwo_setCB(void (*cb)(void))
{
    if(cb)
    {
        timerTwoCallback = cb;

        /* Enable Timer 2 OVerflow interrupt */
        TIMSK2 |= (1 << TOIE2);
    }
}


/*** Interrupt Service Routines ***/

ISR(TIMER2_OVF_vect)
{
    /* Reset the timer register */
    TCNT2 = RTC_C2_TNT2_reg;

    if(timerTwoCallback)
        timerTwoCallback();
}
