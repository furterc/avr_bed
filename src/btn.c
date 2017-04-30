/*
 * btn.c
 *
 *  Created on: 22 Apr 2016
 *      Author: cfurter
 */

#include "btn.h"
#include "led.h"
#include "config.h"
#include "terminal.h"
#include "pwm.h"

#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>

btn_state btnState;

void btn_init()
{
	/* set buttons as inputs */
    BTN_TOP_DDR &= ~(1 << BTN_TOP_INPUTPIN);
    BTN_BOT_DDR &= ~(1 << BTN_BOT_INPUTPIN);

    btnState = MID;
}

void btn_topSelected()
{
	for (uint8_t idx = 0;idx < PWM_CHANNELS;idx++)
				pwm_setDuty(idx, 255);

}

void btn_midSelected()
{
	for (uint8_t idx = 0;idx < PWM_CHANNELS-3;idx++)
				pwm_setDuty(idx, 0);

	pwm_setDuty(6, 10);
	pwm_setDuty(7, 10);
	pwm_setDuty(8, 10);
}

void btn_botSelected()
{
	for (uint8_t idx = 0;idx < PWM_CHANNELS;idx++)
				pwm_setDuty(idx, 0);
}

void btn_checkState()
{
    /* switch changed */
    if (!(BTN_TOP_PIN & (1 << BTN_TOP_INPUTPIN)))
    {
    	if(btnState != TOP)
    	{
    		btnState = TOP;
    		btn_topSelected();
    		printf("btnTOP\r\n");

    	}
    }
    else if (!(BTN_BOT_PIN & (1 << BTN_BOT_INPUTPIN)))
    {
    	if(btnState != BOT)
   	  	{
    		btnState = BOT;
    		btn_botSelected();
    		printf("btnBOT\r\n");
   	  	}
    }
    else
    {
    	if(btnState != MID)
    	{
    		btnState = MID;
    		btn_midSelected();
    		printf("btnFOKKOL\r\n");
    	}
    }

}

btn_state btn_getState()
{
	return btnState;
}
void btn_setState(btn_state state)
{

}
