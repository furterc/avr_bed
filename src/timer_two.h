/*
 * timer1.h
 *
 *  Created on: 12 May 2016
 *      Author: cfurter
 */

#ifndef SRC_TIMER_TWO_H_
#define SRC_TIMER_TWO_H_

#include <avr/io.h>
#include <avr/interrupt.h>

/* Define the initial value for the 16-bit timer */
#define RTC_TCNT1_REG_VAL   0xC2F6

/* Function prototypes */
void timerTwo_init();
void timerTwo_setCB(void (*cb)(void));

#endif /* SRC_TIMER_TWO_H_ */
