/*
 * toggle_switch.cpp
 *
 *  Created on: 03 Jun 2017
 *      Author: christo
 */

#include "toggle_switch.h"
#include <avr/io.h>

/* Setup Button port */
#define BTN_TOP_DDR DDRC
#define BTN_TOP_PORT PORTC
#define BTN_TOP_PIN PINC
#define BTN_TOP_INPUTPIN PC4

#define BTN_BOT_DDR DDRC
#define BTN_BOT_PORT PORTC
#define BTN_BOT_PIN PINC
#define BTN_BOT_INPUTPIN PC3

cToggleSwitch::cToggleSwitch()
{
    /* set buttons as inputs */
    BTN_TOP_DDR &= ~(1 << BTN_TOP_INPUTPIN);
    BTN_BOT_DDR &= ~(1 << BTN_BOT_INPUTPIN);
}

void cToggleSwitch::setCB(void (*cbTop)(void), void (*cbMid)(void),
        void (*cbBot)(void))
{
    if (cbTop)
        buttonTopCallback = cbTop;

    if (cbMid)
        buttonMidCallback = cbMid;

    if (cbBot)
        buttonBotCallback = cbBot;
}

void cToggleSwitch::run()
{
    if (!(BTN_TOP_PIN & (1 << BTN_TOP_INPUTPIN)))
    {
        if (mState != TOP)
        {
            mState = TOP;
            if (buttonTopCallback)
                buttonTopCallback();
        }
    }
    else if (!(BTN_BOT_PIN & (1 << BTN_BOT_INPUTPIN)))
    {
        if (mState != BOT)
        {
            mState = BOT;
            if (buttonBotCallback)
                buttonBotCallback();
        }
    }
    else
    {
        if (mState != MID)
        {
            mState = MID;
            if (buttonMidCallback)
                buttonMidCallback();
        }
    }
}

cToggleSwitch::~cToggleSwitch()
{
    // TODO Auto-generated destructor stub
}

