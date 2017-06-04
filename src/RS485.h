/*
 * RS485.h
 *
 *  Created on: 29 Apr 2017
 *      Author: christo
 */

#ifndef RS485_H_
#define RS485_H_

#include <stdint-gcc.h>

class cRS485
{
public:
    cRS485();
    void transmit_byte(uint8_t b);
    void transmit_packet(uint8_t * buff, uint8_t len);
    virtual ~cRS485();
};

#endif /* RS485_H_ */
