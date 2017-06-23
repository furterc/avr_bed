#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

#include "cplus_plus.h"
#include "output.h"
#include "RS485.h"
#include "cMsg.h"
#include "toggle_switch.h"
#include "TimerPwm.h"
#include "pwm.h"

cToggleSwitch ToggleSwitch = cToggleSwitch();


cOutput led = cOutput(PORT_PB(5));



cPWM light[4];
cTimerPwm timerZeroPwm = cTimerPwm(1, 0, &light[0], &light[1]);
cTimerPwm timerTwoPwm = cTimerPwm(0, 2, &light[2], &light[3]);


uint8_t mCount = 0;
void heartBeat()
{
    switch (mCount++)
    {
    case 0:
        led.set();
        break;
    case 1:
        led.reset();
        break;
    case 2:
        led.set();
        break;
    case 3:
        led.reset();
        break;
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
        break;
    case 12:
    default:
        mCount = 0;
        break;
    }
}

cMsg msg = cMsg();

void bed(cMsg packet)
{
    uint8_t pChan = packet.getData0();
    if (packet.getType() == packet.TYPE_SET)
        light[pChan].setDutyC(packet.getData1());
    else
    {
        packet.setType(packet.TYPE_SET);
        packet.setData1(light[pChan].getDutyC());
        uint8_t bytes[4];
        packet.toBytes(bytes);
        RS485.transmit_packet(bytes, 4);
    }
}
extern const rs485_dbg_entry bedLEDEntry =
{ bed, msg.TAG_LED_BED };

void toggleSwitchTop(void)
{
    light[0].setDutyC(255);       //top
    light[1].setDutyC(255);     //bot
    light[2].setDutyC(255);     //lyf
    light[3].setDutyC(255);       //kop
}

void toggleSwitchMid(void)
{
    light[0].setDutyC(20);       //top
    light[1].setDutyC(1);     //bot
    light[2].setDutyC(0);     //lyf
    light[3].setDutyC(0);       //kop
}

void toggleSwitchBot(void)
{
    light[0].setDutyC(0);       //top
    light[1].setDutyC(0);     //bot
    light[2].setDutyC(0);     //lyf
    light[3].setDutyC(0);       //kop
}

int main()
{
    sei();

    timerZeroPwm.init();
    timerTwoPwm.init();

    light[0].setDutyC(0);       //top
    light[1].setDutyC(255);     //bot
    light[2].setDutyC(25);     //lyf
    light[3].setDutyC(25);       //kop

    ToggleSwitch.setCB(toggleSwitchTop, toggleSwitchMid, toggleSwitchBot);

    while (1)
    {
        heartBeat();
        ToggleSwitch.run();
        RS485.run();
        _delay_ms(100);
    }

    return 1;
}

