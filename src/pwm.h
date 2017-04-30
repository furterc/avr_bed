/*
 * pwm.h
 *
 *  Created on: Jun 4, 2016
 *      Author: christo-laptop
 */

#ifndef SRC_PWM_H_
#define SRC_PWM_H_

#include <stdint-gcc.h>

#define PWM_CHANNELS 9

uint16_t pwmDutyActive;

void pwm_init();
void pwm_run();

uint8_t pwm_setDuty(uint8_t pwmChannel, uint8_t pwmDuty);
uint8_t pwm_getDuty(uint8_t pwmChannel);
uint8_t pwm_setDuties(uint8_t pwmChannels[]);
//uint8_t set_getDuties(uint8_t * pwmChannels[]);


#endif /* SRC_PWM_H_ */
