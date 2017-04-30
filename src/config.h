/*
 * config.h
 *
 *  Created on: 12 Apr 2016
 *      Author: cfurter
 */

#ifndef SRC_CONFIG_H_
#define SRC_CONFIG_H_

/* Message defines */
#define BMS_VERSION             "0.0.1 April 2016\r\n"
#define TERM                ">> "
//#define MSG_NO_BATTERY          "No battery connected\r\n"

/* UART defines*/
#define SYSTEM_CLOCK    16000000 //1Mhz
#define BAUDRATE        115200
#define MYUBBR ((SYSTEM_CLOCK / (BAUDRATE * 8UL))-1)

#endif /* SRC_CONFIG_H_ */
