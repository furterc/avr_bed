/*
 * termHandler.c
 *
 *  Created on: 12 Apr 2016
 *      Author: cfurter
 */

#include "termHandler.h"
#include "terminal.h"
#include "config.h"
#include "pwm.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>

/* Function Prototypes */
void t_stripWhite(char * str);
int8_t t_findArrays(char * str, uint8_t * argc, char * argv[]);


char tempStr[16];

/* Help entries*/
void H(uint8_t argc, char * argv[]){};
void help(uint8_t argc, char * argv[]);
void pwmSet(uint8_t argc, char * argv[]);
void lightsOn(uint8_t argc, char * argv[]);
void setState(uint8_t argc, char * argv[]);
//void tempHumid(uint8_t argc, char * argv[]);
//void pwmEffect(uint8_t argc, char * argv[]);


//void version();


typedef void (*func_t)(uint8_t, char **);
typedef struct
{
	char* cmd;
	char* desc;
	func_t f;
}termCommands;

termCommands cmdTable[] = {
		/****************** Information ******************/
		{"HELP",0,0},
		{"h",      "help",        help},
		{"PWM",0,0},
		{"p",     "pwmSet",      pwmSet},
		{"l",     "lights on",      lightsOn},
		{"LED States",0,0},
		{"s",     "on, off, onoff, offon",      setState},

		//        {"th",      "Temperature and humidity display", tempHumid},

		{0,0,0}
};


/*
 * String functions
 */
void t_stripWhite(char * str)
{
	uint16_t len = 0;
	while(str[len] != 0)
	{
		if((str[len] == '\n') || (str[len] == '\r'))
			str[len] = 0;

		if(len++ > 31)
		{
			len = 0;
			break;
		}
	}
}

int8_t t_findArrays(char * str, uint8_t * argc, char * argv[])
{
	//remove the return and new line from the character array
	t_stripWhite(str);
	uint8_t argcTemp = 0;
	char * p = strtok(str, " ");

	while(p)
	{
		argv[argcTemp++] = p;
		p = strtok(NULL, " ");
	}
	*argc = argcTemp;
	return 0;
}

uint8_t t_Handler(char* cmd)
{
	uint8_t argc = 0;
	uint8_t idx = 0;
	char * argv[5];
	t_findArrays(cmd, &argc, argv);

	while(cmdTable[idx].cmd)
	{
		if(!strcmp(cmdTable[idx].cmd, cmd))
		{
			if(!cmdTable[idx].f)
				return 0;
			cmdTable[idx].f(argc,argv);
			return 1;
		}
		idx++;
	}
	return 0;
}

/*
 * Commands
 */

void help(uint8_t argc, char * argv[])
{
	uint8_t k = 0;
	while(cmdTable[k].cmd)
	{
		if(!cmdTable[k].f)
			printf("%s\r\n",cmdTable[k].cmd);
		else
		{
			printf_P(PSTR(" "));
			printf(cmdTable[k].cmd);
			printf_P(PSTR("\t- "));
			printf(cmdTable[k].desc);
			printf_P(PSTR("\r\n"));
		}

		k++;
	}
}

void pwmSet(uint8_t argc, char * argv[])
{
	if (argc > 2)
	{
		uint8_t pwmChannel = atoi(argv[1]);
		uint8_t pwmDuty = atoi(argv[2]);
		if (!pwm_setDuty(pwmChannel, pwmDuty))
			printf(PSTR("!PWM nr\n\r"));
	}
	else
	{
		for (uint8_t idx = 0; idx < 9; idx++)
			printf_P(PSTR("PWM %d duty: %d\n"), idx, pwm_getDuty(idx));

		printf_P(PSTR("PWM active: %d\n\r"),pwmDutyActive);

		printf_P(PSTR("PWM active: 0b0000000"));
		for (uint8_t idx = 9; idx > 0; idx--)
		{
			if (pwmDutyActive & (1 << idx))
				printf_P(PSTR("1"));
			else
				printf_P(PSTR("0"));
		}
		if (pwmDutyActive & (1 << 0))
			printf_P(PSTR("1"));
		else
			printf_P(PSTR("0"));
		printf_P(PSTR("\n\r"));
	}
}

void lightsOn(uint8_t argc, char * argv[])
{
//	uint8_t delayLen = atoi(argv[1]);
//
//	for(uint8_t idx=0;idx<255;idx++)
//	{
//		pwm_setDuty(0, idx);
//		delay_cnt(delayLen);
//	}
}

void setState(uint8_t argc, char * argv[])
{

}

//void version()
//{
//    printf_P(PSTR("Version: %s"), BMS_VERSION);
//}




//void t_setHr()
//{
//    rtc_setHour(val);
//}
//void t_setMin()
//{
//    rtc_setMinute(val);
//}
//
//void t_setSec()
//{
//    rtc_setSecond(val);
//}



//void tempHumid(uint8_t argc, char * argv[])
//{
//    int8_t tempI;
//    uint8_t tempD;
//    int8_t humidI;
//    uint8_t humidD;
//    if (dht_getdata(&tempI,&tempD,&humidI,&humidD) != -1)
//    {
//        char sTemp[20] =  "Temperature : ";
//        itoa(tempI, sTemp+14,10);
//        sTemp[16] = '.';
//        itoa(tempD, sTemp+17,10);
//        sTemp[19] = 0x00;
//        printf(sTemp);
//        printf(" C\n\r");
//
//        char sHumid[20] =  "Humidity    : ";
//        itoa(humidI, sHumid+14,10);
//        sHumid[16] = '.';
//        itoa(humidD, sHumid+17,10);
//
//        printf(sHumid);
//        printf(" %%\n\r");
//    }
//}
