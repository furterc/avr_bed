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

//cRS485 rs485 = cRS485();
cPacket packet = cPacket(1, 0, 0, 0);

cOutput leds[9] =
{ PORT_PB(5),/*PORT_PD(2)*/ PORT_PD(3), PORT_PD(4), PORT_PD(5), PORT_PD(6),
        PORT_PD(7), PORT_PB(0), PORT_PB(2), PORT_PB(1) };

cPWM pwms[9] =
{ &leds[0], &leds[1], &leds[2], &leds[3], &leds[4], &leds[5], &leds[6],
        &leds[7], &leds[8] };

cPWMRunner pwmRunner = cPWMRunner(&pwms[0], &pwms[1], &pwms[2], &pwms[3],
        &pwms[4], &pwms[5], &pwms[6], &pwms[7], &pwms[8]);

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

cPacket mPacket = cPacket();

void bed0(cPacket packet)
{
    if (packet.getType() == packet.TYPE_GET)
    {
        packet.setType(packet.TYPE_SET);
        packet.setData(pwms[0].getDuty());
        uint8_t bytes[4];
        packet.toBytes(bytes);
        RS485.transmit_packet(bytes, 4);
        return;
    }
    else
        pwms[0].setDuty(packet.getData());
}
extern const rs485_dbg_entry rs485pwm0 =
{ bed0, mPacket.BT_BED_0 };

void bed1(cPacket packet)
{
    if (packet.getType() == packet.TYPE_GET)
    {
        packet.setType(packet.TYPE_SET);
        packet.setData(pwms[1].getDuty());
        uint8_t bytes[4];
        packet.toBytes(bytes);
        RS485.transmit_packet(bytes, 4);
        return;
    }
    else
        pwms[1].setDuty(packet.getData());
}
extern const rs485_dbg_entry rs485pwm1 =
{ bed1, mPacket.BT_BED_1};

void bed2(cPacket packet)
{
    if (packet.getType() == packet.TYPE_GET)
    {
        packet.setType(packet.TYPE_SET);
        packet.setData(pwms[2].getDuty());
        uint8_t bytes[4];
        packet.toBytes(bytes);
        RS485.transmit_packet(bytes, 4);
        return;
    }
    else
        pwms[2].setDuty(packet.getData());
}
extern const rs485_dbg_entry rs485pwm2 =
{ bed2, mPacket.BT_BED_2 };

void bed3(cPacket packet)
{
    if (packet.getType() == packet.TYPE_GET)
    {
        packet.setType(packet.TYPE_SET);
        packet.setData(pwms[3].getDuty());
        uint8_t bytes[4];
        packet.toBytes(bytes);
        RS485.transmit_packet(bytes, 4);
        return;
    }
    else
        pwms[3].setDuty(packet.getData());
}
extern const rs485_dbg_entry rs485pwm3 =
{ bed3, mPacket.BT_BED_3 };

void bed4(cPacket packet)
{
    if (packet.getType() == packet.TYPE_GET)
    {
        packet.setType(packet.TYPE_SET);
        packet.setData(pwms[4].getDuty());
        uint8_t bytes[4];
        packet.toBytes(bytes);
        RS485.transmit_packet(bytes, 4);
        return;
    }
    else
        pwms[4].setDuty(packet.getData());
}
extern const rs485_dbg_entry rs485pwm4 =
{ bed4, mPacket.BT_BED_4 };

void bed5(cPacket packet)
{
    if (packet.getType() == packet.TYPE_GET)
    {
        packet.setType(packet.TYPE_SET);
        packet.setData(pwms[5].getDuty());
        uint8_t bytes[5];
        packet.toBytes(bytes);
        RS485.transmit_packet(bytes, 4);
        return;
    }
    else
        pwms[5].setDuty(packet.getData());
}
extern const rs485_dbg_entry rs485pwm5 =
{ bed5, mPacket.BT_BED_5 };

void bed6(cPacket packet)
{
    if (packet.getType() == packet.TYPE_GET)
    {
        packet.setType(packet.TYPE_SET);
        packet.setData(pwms[6].getDuty());
        uint8_t bytes[4];
        packet.toBytes(bytes);
        RS485.transmit_packet(bytes, 4);
        return;
    }
    else
        pwms[6].setDuty(packet.getData());
}
extern const rs485_dbg_entry rs485pwm6 =
{ bed6, mPacket.BT_BED_6 };

void bed7(cPacket packet)
{
    if (packet.getType() == packet.TYPE_GET)
    {
        packet.setType(packet.TYPE_SET);
        packet.setData(pwms[7].getDuty());
        uint8_t bytes[4];
        packet.toBytes(bytes);
        RS485.transmit_packet(bytes, 4);
        return;
    }
    else
        pwms[7].setDuty(packet.getData());
}
extern const rs485_dbg_entry rs485pwm7 =
{ bed7, mPacket.BT_BED_7 };

void bed8(cPacket packet)
{
    if (packet.getType() == packet.TYPE_GET)
    {
        packet.setType(packet.TYPE_SET);
        packet.setData(pwms[8].getDuty());
        uint8_t bytes[4];
        packet.toBytes(bytes);
        RS485.transmit_packet(bytes, 4);
        return;
    }
    else
        pwms[8].setDuty(packet.getData());
}
extern const rs485_dbg_entry rs485pwm8 =
{ bed8, mPacket.BT_BED_8 };


void timer_zero_callback(void)
{
    pwmRunner.run();
}

void toggleSwitchTop(void)
{
    for (uint8_t idx = 0; idx < LED_COUNT; idx++)
        pwms[idx].setDuty(255);
}

void toggleSwitchMid(void)
{
    for (uint8_t idx = 0; idx < LED_COUNT - 3; idx++)
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

    while (1)
    {
        ToggleSwitch.run();
        RS485.run();
        _delay_ms(100);
    }

    return 1;
}

