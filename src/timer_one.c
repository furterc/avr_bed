/*
 * timer1.c
 *
 *  Created on: 12 May 2016
 *      Author: cfurter
 */

#include "timer_one.h"

void (*timerOneCallback)(void) = 0;

/*** Function prototypes ***/

ISR(TIMER1_OVF_vect);


/*** Functions ***/

/* Set up timer1 to interrupt on 1 second intervals*/
void timerOne_init()
{
    /* Select clock source and prescaler clk/1024 */
    TCCR1B |= (1 << CS10) | (1 << CS11);

    /* Set initial value of Counter */
    TCNT1 = RTC_TCNT1_REG_VAL;
}

void timerOne_setCB(void (*cb)(void))
{
    if(cb)
    {
        timerOneCallback = cb;

        /* Enable Timer 1 Overflow interrupt */
        TIMSK1 |= (1 << TOIE1);
    }
}


/*** Interrupt Service Routines ***/

ISR(TIMER1_OVF_vect)
{
    /* Reset the timer register */
    TCNT1 = RTC_TCNT1_REG_VAL;

    if(timerOneCallback)
        timerOneCallback();
}
