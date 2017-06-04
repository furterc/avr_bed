/*
 * timer_zero.h
 *
 *  Created on: 03 Jun 2017
 *      Author: christo
 */

#ifndef SRC_TIMER_ZERO_H_
#define SRC_TIMER_ZERO_H_

class cTimerZero
{
    void (*timerZeroCallback)(void) = 0;
public:
    cTimerZero();
    void setCB(void (*cb)(void));
    void serviceCB();
    virtual ~cTimerZero();

};

extern cTimerZero TimerZero;

#endif /* SRC_TIMER_ZERO_H_ */
