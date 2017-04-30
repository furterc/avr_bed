#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "led.h"
#include "pwm.h"
#include "btn.h"
#include "terminal.h"
#include "termHandler.h"
#include "timer_zero.h"



void timerZeroRun(void)
{
	pwm_run();

}



int main(void)
{
	sei();
	btn_init();

	timerZero_init();
	timerZero_setCB(timerZeroRun);
	led_init();
	term_init();
	led_on(0);
	while(1)
	{
		if (validData == 1)
			handleTerm();
		btn_checkState();
	}
	return 0;
}
