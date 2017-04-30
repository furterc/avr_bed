/*
 * led.h
 *
 *  Created on: Jul 2, 2016
 *      Author: christo-laptop
 */

#ifndef SRC_LED_H_
#define SRC_LED_H_

#include <stdint-gcc.h>

void led_init();
void led_on(uint16_t ledNr);
void led_off(uint16_t ledNr);

#endif /* SRC_LED_H_ */
