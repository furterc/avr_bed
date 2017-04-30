/*
 * timer1.h
 *
 *  Created on: 12 May 2016
 *      Author: cfurter
 */

#ifndef SRC_TIMER_ONE_H_
#define SRC_TIMER_ONE_H_

#include <avr/io.h>
#include <avr/interrupt.h>

/* Define the initial value for the 16-bit timer */
#define RTC_TCNT1_REG_VAL   0xC2F6

/* Function prototypes */
void timerOne_init();
void timerOne_setCB(void (*cb)(void));

#endif /* SRC_TIMER_ONE_H_ */
