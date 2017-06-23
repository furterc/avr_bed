/*
 * RS485.cpp
 *
 *  Created on: 29 Apr 2017
 *      Author: christo
 */

#include "RS485.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include "output.h"

#define BAUD 9600
#define MYUBBR ((F_CPU / (BAUD * 8UL))-1)

cOutput mWriteEnable = cOutput(PORT_PC(2));

cRS485::cRS485()
{
    mDataReady = false;
    mCommandLen = 0;

    DDRB |= _BV(PB0);   //output

    //set up the BAUD Rate
    UBRR0H = (unsigned char) (MYUBBR >> 8);
    UBRR0L = (unsigned char) (MYUBBR);

    //double transmission speed
    UCSR0A |= _BV(U2X0);
    //set the character size to 8-bit
    UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
    //Enable RX | TX interrupt
    UCSR0B = _BV(TXEN0) | _BV(RXEN0) | _BV(RXCIE0) | _BV(TXCIE0);

    mWriteEnable.reset();
}

void cRS485::transmit_byte(uint8_t b)
{
    mWriteEnable.set();
    //wait until the transmitter is ready
    while (!(UCSR0A & (1 << UDRE0)))
        ;

    //write the data to the uart buffer
    UDR0 = b;

    //clear the transfer complete flag
    UCSR0A |= (1 << TXC0);
}

void cRS485::transmit_packet(uint8_t * buff, uint8_t len)
{
    uint8_t frame_ptr[64];
    uint32_t frame_length = 64;
    cHDLCframer::frame(buff, 4, frame_ptr, &frame_length);

    for (uint8_t i = 0; i < frame_length; i++)
    {
        transmit_byte(frame_ptr[i]);
    }
}

void cRS485::handleCommand()
{
    mCommand[mCommandLen] = 0;

        uint8_t data[mCommandLen];
        memcpy(&data, mCommand, mCommandLen);
        memset(mCommand, 0xFF, 64);

        cMsg cmsgIn = cMsg(data);
        uint8_t idx = 0;
        const rs485_dbg_entry *curr485Entry = rs485_dbg_entries[idx++];
        while (curr485Entry)
        {
            if ((curr485Entry->tag == cmsgIn.getTag()))
            {
                curr485Entry->func(cmsgIn);
                return;
            }
            curr485Entry = rs485_dbg_entries[idx++];
        }
}

void cRS485::run()
{
    if (mDataReady)
        {
            mDataReady = false;
            handleCommand();
        }
}

void cRS485::handle(uint8_t ch)
{
    int rxLen = framer.pack(ch);
        if (rxLen)
        {
            mCommandLen = rxLen;
            memcpy(&mCommand, framer.buffer(), rxLen);
            mDataReady = true;
        }
}

ISR(USART_RX_vect)
{
    RS485.handle(UDR0);
}

ISR(USART_TX_vect)
{
    mWriteEnable.reset();
}

cRS485::~cRS485()
{
    // TODO Auto-generated destructor stub
}

cRS485 RS485;
