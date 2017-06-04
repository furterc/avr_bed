/*
 * timer_zero.cpp
 *
 *  Created on: 03 Jun 2017
 *      Author: christo
 */

#include "timer_zero.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define RTC_TCNT0_REG_VAL   240

cTimerZero::cTimerZero()
{
    // TODO Auto-generated constructor stub

    /* Select clock source and prescaler -> clk/64 */
     TCCR0B |= (1 << CS01) | (1 << CS00);

     /* Set the initial value of Counter */
     TCNT0 = RTC_TCNT0_REG_VAL;
}

void cTimerZero::setCB(void (*cb)(void))
{
    if(cb)
    {
        timerZeroCallback = cb;

        /* Enable Timer 0 Overflow interrupt */
        TIMSK0 |= (1 << TOIE0);
    }
}


void cTimerZero::serviceCB()
{
    if(timerZeroCallback)
            timerZeroCallback();
}
cTimerZero::~cTimerZero()
{
    // TODO Auto-generated destructor stub
}


ISR(TIMER0_OVF_vect)
{
    /* Set the initial value for the counter */
    TCNT0 = RTC_TCNT0_REG_VAL;

    TimerZero.serviceCB();
}

cTimerZero TimerZero;
