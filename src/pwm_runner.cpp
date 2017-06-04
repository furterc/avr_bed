/*
 * pwm_runner.cpp
 *
 *  Created on: 04 Jun 2017
 *      Author: christo
 */

#include "pwm_runner.h"

cPWMRunner::cPWMRunner(cPWM * pwm0, cPWM * pwm1, cPWM * pwm2, cPWM * pwm3,
        cPWM * pwm4, cPWM * pwm5, cPWM * pwm6, cPWM * pwm7, cPWM * pwm8)
{
    mPWM[0] = pwm0;
    mPWM[1] = pwm1;
    mPWM[2] = pwm2;
    mPWM[3] = pwm3;
    mPWM[4] = pwm4;
    mPWM[5] = pwm5;
    mPWM[6] = pwm6;
    mPWM[7] = pwm7;
    mPWM[8] = pwm8;

    mCount = 0;
}

void cPWMRunner::run()
{
    if (++mCount > 255)
    {
        mCount = 0;

        //set led
        for (int i = 0; i < PWM_COUNT; i++)
            if (mPWM[i]->isActive())
                mPWM[i]->set();

        return;
    }

    for (int i = 0; i < PWM_COUNT; i++)
        if (mPWM[i]->isActive())
            if (mCount == mPWM[i]->getDuty())
                mPWM[i]->reset();

}

cPWMRunner::~cPWMRunner()
{
    // TODO Auto-generated destructor stub
}

