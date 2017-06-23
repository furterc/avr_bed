/*
 * cTimerPwm.cpp
 *
 *  Created on: 18 Feb 2017
 *      Author: christo
 */

#include "TimerPwm.h"

#include <avr/io.h>


cTimerPwm::cTimerPwm() {
    mInv = 0;
    mTimerNum = 0;

    mPwmA = 0;
    mPwmB = 0;
}

cTimerPwm::cTimerPwm(uint8_t inv, uint8_t timerNum, cPWM * pwmA, cPWM * pwmB)
{
    mTimerNum = timerNum;
    mInv = inv;

    mPwmA = pwmA;
    mPwmB = pwmB;
}

void cTimerPwm::init()
{
    if (mEnabled)
        return;

    switch (mTimerNum)
    {
    case 0:
    {
        // set PD5 & PD6 as output
        DDRD |= _BV(5) | _BV(6);

        if (mInv == 1)
        {
            // inverting mode A & B
            TCCR0A |= _BV(COM0A1);
            TCCR0A |= _BV(COM0B1);
        } else
        {
            // non-inverting mode A & B
            TCCR0A |= _BV(COM0A1) | _BV(COM0A0);
            TCCR0A |= _BV(COM0B1) | _BV(COM0B0);
        }

        // set Waveform as phase correct PWM / 8 bit
        TCCR0A |=_BV(WGM00);
        // set the prescaler as clk/1024
        TCCR0B |= _BV(CS01) | _BV(CS00);

        mPwmA->setOCRn(&OCR0A);
        mPwmB->setOCRn(&OCR0B);
    }
    break;

    case 2:
    {
        // set PB3 & PD3 & PL5 as output
        DDRB |= _BV(3);
        DDRD |= _BV(3);

        if (mInv == 1)
        {
            // inverting mode A & B
            TCCR2A |= _BV(COM2A1) | _BV(COM2A0);
            TCCR2A |= _BV(COM2B1) | _BV(COM2B0);
        } else
        {
            // non-inverting mode A & B
            TCCR2A |= _BV(COM2A1);
            TCCR2A |= _BV(COM2B1);
        }

        // set Waveform as phase correct PWM / 8 bit
        TCCR2A |= _BV(WGM20);

        // set the prescaler as clk/1024
        TCCR2B |= _BV(CS21) | _BV(CS20);

        mPwmA->setOCRn(&OCR2A);
        mPwmB->setOCRn(&OCR2B);
    }
    break;

    default:
        return;
    }

    mEnabled = true;
}


cTimerPwm::~cTimerPwm()
{
    // TODO Auto-generated destructor stub
}

