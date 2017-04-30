/*
 * terminal.c
 *
 *  Created on: 07 Apr 2016
 *      Author: cfurter
 */

#include "uart.h"
#include "terminal.h"
#include "termHandler.h"
#include "config.h"

#include <stdio.h>
#include <stdint-gcc.h>
#include <avr/interrupt.h>

#define TERM_RX_LEN 16
#define TERM_ECHO

ISR(USART_RX_vect);

char t_RX[TERM_RX_LEN];
uint8_t t_RXLen = 0;

void term_init()
{
    uart_init();
    printf(TERM);
    validData = 0;
}

void handleTerm()
{
//    cli();
    validData = 0;
    t_RX[t_RXLen] = 0;

    //check if the command exists and if it contains more than new line and return
    if(!t_Handler(t_RX) && t_RXLen > 2)
    {
        printf_P(PSTR("Unknown command '%s' type 'h' for help\n\r"),t_RX);
    }
    printf(TERM);
    t_RXLen = 0;
//    sei();
}

ISR(USART_RX_vect)
{
    cli();
    uint8_t RXdata;

    //wait for the byte to be received
    while( !(UCSR0A & (1 << RXC0)));

    RXdata = UDR0;

    //echo the character received from terminal
    #ifdef TERM_ECHO
    printf("%c",RXdata);
    #endif

    //if a lien return is found handleTerm else append the character array with the received character
    if (RXdata == '\r')
    {
        t_RX[t_RXLen++] = RXdata;
        t_RX[t_RXLen++] = '\n';
        printf("%c", '\n');
        validData = 1;
//        handleTerm();
    }else
        t_RX[t_RXLen++] = RXdata;
    sei();
}
