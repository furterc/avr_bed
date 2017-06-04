/*
 * pwm.cpp
 *
 *  Created on: 03 Jun 2017
 *      Author: christo
 */

#include "pwm.h"
#include "output.h"



cPWM::cPWM(cOutput * output)
{
    mDuty = 0;
    mActive = false;
    mOutput = output;
    mOutput->reset();
}

void cPWM::setDuty(uint8_t duty)
{
    mOutput->set();

    if(duty == 255)
    {
        mActive = false;
        mOutput->set();
    }else if (duty == 0)
    {
        mActive = false;
        mOutput->reset();
    }
    else
        mActive = true;

    mDuty = duty;
}

uint8_t cPWM::getDuty()
{
    return mDuty;
}

void cPWM::set()
{
    mOutput->set();
}

void cPWM::reset()
{
    mOutput->reset();
}

bool cPWM::get()
{
    return mOutput->get();
}

bool cPWM::isActive()
{
    return mActive;
}

//void cPWM::run()
//{
//    if(!mActive)
//        return;
//
//    if(++mDutyCount == 0xFF)
//    {
//        /* Reset Ports */
//        mDutyCount = 0;
//        mOutput->set();
//    }
//
//    if (mDutyCount == mDuty)
//        mOutput->reset();
//}

cPWM::~cPWM()
{
    // TODO Auto-generated destructor stub
}

