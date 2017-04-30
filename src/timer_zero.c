/*
 * timer0.c
 *
 *  Created on: 12 May 2016
 *      Author: cfurter
 */

#include "timer_zero.h"

void (*timerZeroCallback)(void) = 0;

/*** Function Prototypes ***/

ISR(TIMER0_OVF_vect);


/*** Functions ***/

/* Timer 0 is set up for 1mS interrupts */
void timerZero_init()
{
    /* Select clock source and prescaler -> clk/8 */
    TCCR0B |= (1 << CS01);

    /* Set the initial value of Counter */
    TCNT0 = RTC_TCNT0_REG_VAL;
}

void timerZero_setCB(void (*cb)(void))
{
    if(cb)
    {
        timerZeroCallback = cb;

        /* Enable Timer 0 Overflow interrupt */
        TIMSK0 |= (1 << TOIE0);
    }
}

/*** Interrupt service routines ***/

ISR(TIMER0_OVF_vect)
{
    /* Set the initial value for the counter */
    TCNT0 = RTC_TCNT0_REG_VAL;

    if(timerZeroCallback)
        timerZeroCallback();
}
