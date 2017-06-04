/*
 * RS485.cpp
 *
 *  Created on: 29 Apr 2017
 *      Author: christo
 */

#include "RS485.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include "output.h"

#define BAUD 9600
#define MYUBBR ((F_CPU / (BAUD * 8UL))-1)

cOutput mWriteEnable = cOutput(PORT_PD(2));

cRS485::cRS485()
{
    DDRD |= _BV(PD1);       //Output -  PB0 --> TXD0

    //set up the BAUD Rate
    UBRR0H = (unsigned char) (MYUBBR >> 8);
    UBRR0L = (unsigned char) (MYUBBR);

    //double transmission speed
    UCSR0A |= _BV(U2X0);
    //set the character size to 8-bit
    UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
    //Enable RX | TX interrupt
    UCSR0B = _BV(TXEN0) | _BV(RXEN0) | _BV(TXCIE0);// | _BV(RXCIE3);

    mWriteEnable.reset();
}

void cRS485::transmit_byte(uint8_t b)
{
    mWriteEnable.set();
    //wait until the transmitter is ready
    while (!(UCSR0A & (1 << UDRE0)));

    //write the data to the uart buffer
    UDR0 = b;

    //clear the transfer complete flag
    UCSR0A |= (1 << TXC0);

}

void cRS485::transmit_packet(uint8_t * buff, uint8_t len)
{
    for (uint8_t i = 0; i < len; i++)
    {
        transmit_byte(buff[i]);
    }
    transmit_byte(0x0D);
}

ISR(USART_RX_vect)
{
//    printp("485: %d", UDR3);
}

ISR(USART_TX_vect)
{
    mWriteEnable.reset();
}

cRS485::~cRS485()
{
    // TODO Auto-generated destructor stub
}

