/*
 * rs485_commands.cpp
 *
 *  Created on: 11 May 2017
 *      Author: christo
 */

#include "RS485.h"

extern const rs485_dbg_entry rs485pwm0;
extern const rs485_dbg_entry rs485pwm1;
extern const rs485_dbg_entry rs485pwm2;
extern const rs485_dbg_entry rs485pwm3;
extern const rs485_dbg_entry rs485pwm4;
extern const rs485_dbg_entry rs485pwm5;
extern const rs485_dbg_entry rs485pwm6;
extern const rs485_dbg_entry rs485pwm7;
extern const rs485_dbg_entry rs485pwm8;

const rs485_dbg_entry* rs485_dbg_entries[] =
{
        &rs485pwm0,
        &rs485pwm1,
        &rs485pwm2,
        &rs485pwm3,
        &rs485pwm4,
        &rs485pwm5,
        &rs485pwm6,
        &rs485pwm7,
        &rs485pwm8,
        0
};

