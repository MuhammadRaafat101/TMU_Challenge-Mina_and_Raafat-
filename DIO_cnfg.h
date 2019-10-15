/*
 * DIO_cnfg.h
 *
 *  Created on: Sep 20, 2019
 *      Author: Rafaat
 */

#ifndef DIO_CNFG_H_
#define DIO_CNFG_H_

#include "Std_Types.h"
typedef	enum{SEGA,SEGB,SEGC,SEGD,NUM_OF_PINS}pins;

#define	HIGH	1
#define	LOW		0

#define	OUTPUT	1
#define	INPUT	1

#define	PULLUP	1
#define	EXTRES	0

#define	PORT_A	0
#define	PORT_B	1
#define	PORT_C	2
#define	PORT_D	3


#define	PIN0	0
#define	PIN1	1
#define	PIN2	2
#define	PIN3	3
#define	PIN4	4
#define	PIN5	5
#define	PIN6	6
#define	PIN7	7

#define INITI	1
#define NOTINIT	0

#define	NA		0xFF


typedef	struct{
	uint8 Port;
	uint8 Pin;
	uint8 Dir;
	uint8 Out;
	uint8 Res;
	uint8 Init;
}Dio_Config;

Dio_Config Dio_arr[NUM_OF_PINS];
#endif /* DIO_CNFG_H_ */
