#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

#include "cplus_plus.h"
#include "output.h"
#include "RS485.h"
#include "Packet.h"
#include "pwm.h"
#include "pwm_runner.h"
#include "timer_zero.h"
#include "toggle_switch.h"

#define LED_COUNT 9

cToggleSwitch ToggleSwitch = cToggleSwitch();

cRS485 rs485 = cRS485();
cPacket packet = cPacket(1, 0, 0, 0);

cOutput leds[9] =
{ /*PORT_PD(2)*/ PORT_PB(5), PORT_PD(3), PORT_PD(4), PORT_PD(5), PORT_PD(6), PORT_PD(7),
        PORT_PB(0), PORT_PB(2), PORT_PB(1) };

cPWM pwms[9] =
{ &leds[0], &leds[1], &leds[2], &leds[3], &leds[4], &leds[5], &leds[6],
        &leds[7], &leds[8] };

cPWMRunner pwmRunner = cPWMRunner(&pwms[0],&pwms[1],&pwms[2],&pwms[3],&pwms[4],&pwms[5],&pwms[6],&pwms[7],&pwms[8]);

//cOutput led = cOutput(PORT_PB(5));

//uint8_t mCount = 0;
//void heartBeat()
//{
//    switch (mCount++)
//    {
//    case 0:
//        led.set();
//        break;
//    case 1:
//        led.reset();
//        break;
//    case 2:
//        led.set();
//        break;
//    case 3:
//        led.reset();
//        break;
//    case 4:
//    case 5:
//    case 6:
//    case 7:
//    case 8:
//    case 9:
//    case 10:
//    case 11:
//        break;
//    case 12:
//    default:
//        mCount = 0;
//        break;
//    }
//}

void timer_zero_callback(void)
{
    pwmRunner.run();
}

void toggleSwitchTop(void)
{
    for (uint8_t idx = 0; idx < LED_COUNT; idx++)
        pwms[idx].setDuty(100);
}

void toggleSwitchMid(void)
{
    for (uint8_t idx = 0; idx < LED_COUNT-3; idx++)
            pwms[idx].setDuty(0);

    pwms[6].setDuty(15);
    pwms[7].setDuty(15);
    pwms[8].setDuty(15);
}

void toggleSwitchBot(void)
{
    for (uint8_t idx = 0; idx < LED_COUNT; idx++)
            pwms[idx].setDuty(0);
}

int main()
{
    sei();

    ToggleSwitch.setCB(toggleSwitchTop, toggleSwitchMid, toggleSwitchBot);
    TimerZero.setCB(timer_zero_callback);

    packet.setType(packet.TYPE_GET);
    packet.setTag(packet.BT_STUDY_TOP);
    packet.setData(15);
    uint8_t bytes[4];
    packet.toBytes(bytes);
    rs485.transmit_packet(bytes, 4);

    for (uint8_t idx = 0; idx < LED_COUNT; idx++)
                pwms[idx].setDuty(20);

    uint8_t count = 0;
    while (1)
    {
        if (++count > 254)
        {
            count = 0;
//            ToggleSwitch.run();
        }
//        ToggleSwitch.run();
//        heartBeat();
//        if (++prescaler > 10)
//        {
////            ToggleSwitch.run();
////            rs485.transmit_packet(bytes, 4);
//            prescaler = 0;
//        }
//        _delay_ms(100);
    }

    return 1;
}

