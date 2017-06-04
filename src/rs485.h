/*
 * rs485.h
 *
 *  Created on: 11 May 2017
 *      Author: christo
 */

#include <stdint-gcc.h>

#ifndef RS485_H_
#define RS485_H_

void init();
void transmit_byte(uint8_t b);

#endif /* RS485_H_ */
