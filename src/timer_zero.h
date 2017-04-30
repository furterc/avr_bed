/*
 * timer0.h
 *
 *  Created on: 12 May 2016
 *      Author: cfurter
 */

#ifndef SRC_TIMER_ZERO_H_
#define SRC_TIMER_ZERO_H_

#include <avr/io.h>
#include <avr/interrupt.h>

/* Define the initial value for the 8-bit timer */
#define RTC_TCNT0_REG_VAL   0xC3


/*** Function Prototypes ***/

void timerZero_init();
void timerZero_setCB(void (*cb)(void));

#endif /* SRC_TIMER_ZERO_H_ */
