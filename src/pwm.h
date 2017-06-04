/*
 * pwm.h
 *
 *  Created on: 03 Jun 2017
 *      Author: christo
 */

#ifndef SRC_PWM_H_
#define SRC_PWM_H_

#include <stdint-gcc.h>
#include "output.h"

class cPWM
{
    cOutput * mOutput;
    bool mActive;
    uint8_t mDuty;

public:
    cPWM(cOutput * output);
    bool isActive();
    uint8_t getDuty();
    void setDuty(uint8_t duty);
    bool get();
    void set();
    void reset();
    virtual ~cPWM();
};

#endif /* SRC_PWM_H_ */
