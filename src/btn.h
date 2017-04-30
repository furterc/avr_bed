/*
 * btn.h
 *
 *  Created on: 22 Apr 2016
 *      Author: cfurter
 */

#ifndef SRC_BTN_H_
#define SRC_BTN_H_

/* Setup Button port */
#define BTN_TOP_DDR DDRC
#define BTN_TOP_PORT PORTC
#define BTN_TOP_PIN PINC
#define BTN_TOP_INPUTPIN PC4

#define BTN_BOT_DDR DDRC
#define BTN_BOT_PORT PORTC
#define BTN_BOT_PIN PINC
#define BTN_BOT_INPUTPIN PC5

typedef enum {
	TOP,
	MID,
	BOT
} btn_state;

/* Function Prototypes */
void btn_init();
btn_state btn_getState();
void btn_setState(btn_state);
void btn_checkState();

#endif /* SRC_BTN_H_ */
