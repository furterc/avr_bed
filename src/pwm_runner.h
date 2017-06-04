/*
 * pwm_runner.h
 *
 *  Created on: 04 Jun 2017
 *      Author: christo
 */

#ifndef SRC_PWM_RUNNER_H_
#define SRC_PWM_RUNNER_H_

#include "pwm.h"

#define PWM_COUNT 9
class cPWMRunner
{
    cPWM * mPWM[9];
    uint16_t mCount;
public:
//    cPWMRunner(cPWM * pwm0);

    cPWMRunner(cPWM * pwm0, cPWM * pwm1, cPWM * pwm2, cPWM * pwm3, cPWM * pwm4, cPWM * pwm5, cPWM * pwm6, cPWM * pwm7, cPWM * pwm8);
    void run();
    virtual ~cPWMRunner();
};

#endif /* SRC_PWM_RUNNER_H_ */
