/*
 * pwm.c
 *
 *  Created on: Jun 4, 2016
 *      Author: christo-laptop
 */

#include "pwm.h"
#include "led.h"

#include <avr/interrupt.h>

uint8_t dutyC;
uint8_t pwmDutyCycle[PWM_CHANNELS];


void pwm_init()
{
	led_init();
	/* Initialize variables */
	dutyC = 0;
	pwmDutyActive = 0;
	for (uint8_t idx = 0; idx < PWM_CHANNELS; idx++)
		pwmDutyCycle[idx] = 0;
}

uint8_t pwm_setDuty(uint8_t pwmChannel, uint8_t pwmDuty)
{
	/* if pwmChannel not valid return 0 */
	if (!(pwmChannel < PWM_CHANNELS))
		return 0;

	pwmDutyCycle[pwmChannel] = pwmDuty;
	if (pwmDuty == 255)
	{
		led_on(pwmChannel);
		pwmDutyActive &= ~(1 << pwmChannel);
	}

	else if (!pwmDuty)
	{
		led_off(pwmChannel);
		pwmDutyActive &= ~(1 << pwmChannel);
	}

	else
	{
		pwmDutyActive |= (1 << pwmChannel);
	}

	return 1;
}

uint8_t pwm_getDuty(uint8_t pwmChannel)
{
	if (pwmChannel < PWM_CHANNELS)
		return pwmDutyCycle[pwmChannel];
	else
		return 0;
}

uint8_t pwm_setDuties(uint8_t pwmChannels[])
{
    for(uint8_t idx = 0; idx < PWM_CHANNELS; idx++)
    {
        pwmDutyCycle[idx]= pwmChannels[idx];
        if ((pwmChannels[idx])&&(pwmChannels[idx] != 0xFF))
        	pwmDutyActive |= (1 << idx);
        else
        	pwmDutyActive &= ~(1 << idx);
    }
    return 1;
}
//
//uint8_t pwm_getDuties(uint8_t * pwmChannels[])
//{
//    for(uint8_t idx = 0; idx < PWM_CHANNELS; idx++)
//    {
//        *pwmChannels[idx] = pwmDutyCycle[idx];
//    }
//    return 1;
//}

void pwm_run()
{
//	cli();
	if (!pwmDutyActive)
		return;
	if(++dutyC == 0xFF)
	{
		/* Reset Ports */
		dutyC = 0;
		for(uint8_t idx = 0; idx < PWM_CHANNELS; idx++)
			if (pwmDutyActive & (1 << idx))
				led_on(idx);
	}
	if (dutyC)
		for(uint8_t idx = 0; idx < PWM_CHANNELS; idx++)
			if ((dutyC == pwmDutyCycle[idx]) && (pwmDutyActive & (1 << idx)))
				led_off(idx);
//	sei();
}
