/*
 * toggle_switch.h
 *
 *  Created on: 03 Jun 2017
 *      Author: christo
 */

#ifndef SRC_TOGGLE_SWITCH_H_
#define SRC_TOGGLE_SWITCH_H_
class cToggleSwitch
{
    typedef enum {
        TOP,
        MID,
        BOT
    } btn_state;

    btn_state mState = TOP;
    void (*buttonTopCallback)(void) = 0;
    void (*buttonMidCallback)(void) = 0;
    void (*buttonBotCallback)(void) = 0;

public:
    cToggleSwitch();
    void setCB(void (*cbTop)(void), void (*cbMid)(void), void (*cbBot)(void));
    void run();
    virtual ~cToggleSwitch();
};

#endif /* SRC_TOGGLE_SWITCH_H_ */
