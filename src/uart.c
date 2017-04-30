/*
 * uart.c
 *
 *  Created on: 07 Apr 2016
 *      Author: cfurter
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint-gcc.h>
#include <stdio.h>

#include "uart.h"
#include "config.h"

//define functions for printf
static int uart_putchar(char c, FILE *stream);
uint8_t uart_getchar(void);

static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);


void uart_init()
{
    //set up inputs and outputs
//    DDRA &= ~(1 << 7);      //Input  -  PA7 --> RXD0
    DDRB |= (1 << 0);       //Output -  PB0 --> TXD0

    //set up the BAUD rate
    UBRR0H = (unsigned char)(MYUBBR >> 8);
    UBRR0L = (unsigned char)(MYUBBR);

    //double the USART Transmission speed
    UCSR0A |= (1 << U2X0);

    //set character size to 8-bit
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01); //p169

    //enable RX, TX and RX interrupt
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);

    //enable global interrupts
    sei();

    //required for printf init
    stdout = &mystdout;
}


static int uart_putchar(char c, FILE *stream)
{
    //while newline not received
    if (c == '\n') uart_putchar('\r', stream);

    //loop trough the array of bytes
    loop_until_bit_is_set(UCSR0A, UDRE0);

    //start transmission
    UDR0 = c;

    //clear the transfer complete flag
    UCSR0A |= (1 << TXC0);

    return 0;
}


uint8_t uart_getchar(void)
{
    //wait for the incoming data
    while ( !(UCSR0A & (1 << RXC0)) );
    // Return the data
    return(UDR0);
}
