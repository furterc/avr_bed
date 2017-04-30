/*
 * led.c
 *
 *  Created on: Jul 2, 2016
 *      Author: christo-laptop
 */

#include "led.h"

#include <stdio.h>
#include <avr/io.h>

#define LED0_DDR    DDRD
#define LED0_PORT   PORTD
#define LED0_PIN    PD2

#define LED1_DDR    DDRD
#define LED1_PORT   PORTD
#define LED1_PIN    PD3

#define LED2_DDR    DDRD
#define LED2_PORT   PORTD
#define LED2_PIN    PD4

#define LED3_DDR    DDRD
#define LED3_PORT   PORTD
#define LED3_PIN    PD5

#define LED4_DDR    DDRD
#define LED4_PORT   PORTD
#define LED4_PIN    PD6

#define LED5_DDR    DDRD
#define LED5_PORT   PORTD
#define LED5_PIN    PD7

#define LED6_DDR    DDRB
#define LED6_PORT   PORTB
#define LED6_PIN    PB0

#define LED7_DDR    DDRB
#define LED7_PORT   PORTB
#define LED7_PIN    PB2

#define LED8_DDR    DDRB
#define LED8_PORT   PORTB
#define LED8_PIN    PB1

void led_init()
{
    /* Initialize PORTs as output */
    LED0_DDR |= (1 << LED0_PIN);
    LED1_DDR |= (1 << LED1_PIN);
    LED2_DDR |= (1 << LED2_PIN);
    LED3_DDR |= (1 << LED3_PIN);
    LED4_DDR |= (1 << LED4_PIN);
    LED5_DDR |= (1 << LED5_PIN);
    LED6_DDR |= (1 << LED6_PIN);
    LED7_DDR |= (1 << LED7_PIN);
    LED8_DDR |= (1 << LED8_PIN);
}

void led_on(uint16_t ledNr)
{
    switch (ledNr)
    {
    case 0: { LED0_PORT |= (1 << LED0_PIN); }break;
    case 1: { LED1_PORT |= (1 << LED1_PIN); }break;
    case 2: { LED2_PORT |= (1 << LED2_PIN); }break;
    case 3: { LED3_PORT |= (1 << LED3_PIN); }break;
    case 4: { LED4_PORT |= (1 << LED4_PIN); }break;
    case 5: { LED5_PORT |= (1 << LED5_PIN); }break;
    case 6: { LED6_PORT |= (1 << LED6_PIN); }break;
    case 7: { LED7_PORT |= (1 << LED7_PIN); }break;
    case 8: { LED8_PORT |= (1 << LED8_PIN); }break;
    default:
        break;
    }
}

void led_off(uint16_t ledNr)
{
    switch (ledNr)
    {
    case 0: { LED0_PORT &= ~(1 << LED0_PIN); }break;
    case 1: { LED1_PORT &= ~(1 << LED1_PIN); }break;
    case 2: { LED2_PORT &= ~(1 << LED2_PIN); }break;
    case 3: { LED3_PORT &= ~(1 << LED3_PIN); }break;
    case 4: { LED4_PORT &= ~(1 << LED4_PIN); }break;
    case 5: { LED5_PORT &= ~(1 << LED5_PIN); }break;
    case 6: { LED6_PORT &= ~(1 << LED6_PIN); }break;
    case 7: { LED7_PORT &= ~(1 << LED7_PIN); }break;
    case 8: { LED8_PORT &= ~(1 << LED8_PIN); }break;
    default:
        break;
    }
}


