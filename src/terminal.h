/*
 * terminal.h
 *
 *  Created on: 07 Apr 2016
 *      Author: cfurter
 */

#ifndef SRC_TERMINAL_H_
#define SRC_TERMINAL_H_

#include <avr/pgmspace.h>

volatile uint8_t validData;

void term_init();
void handleTerm();

#endif /* SRC_TERMINAL_H_ */
