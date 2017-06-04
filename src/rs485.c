/*
 * rs485.c
 *
 *  Created on: 11 May 2017
 *      Author: christo
 */

#include "rs485.h"

#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdio.h>

#include "rs485.h"

#define MYUBBR 115200

void re485_init()
{
//    DDRA &= ~(1 << 7);      //input
    DDRB |= (1 << 0);       //Output -  PB0 --> TXD0

    //set up the BAUD rate
    UBRR0H = (unsigned char)(MYUBBR >> 8);
    UBRR0L = (unsigned char)(MYUBBR);

    //double the USART Transmission speed
    UCSR0A |= (1 << U2X0);

    //set character size to 8-bit
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01); //p169

    //enable RX, TX and RX interrupt
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);// | (1 << RXCIE0);

    //enable global interrupts
    sei();
}


void transmit_byte(uint8_t b)
{
    //start transmission
    UDR0 = b;

    //clear the transfer complete flag
    UCSR0A |= (1 << TXC0);

    return;
}


//uint8_t uart_getchar(void)
//{
//    //wait for the incoming data
//    while ( !(UCSR0A & (1 << RXC0)) );
//    // Return the data
//    return(UDR0);
//}


