/*
 * DIO.h
 *
 *  Created on: Sep 20, 2019
 *      Author: Rafaat
 */

#ifndef DIO_H_
#define DIO_H_

#include "DIO_cnfg.h"
#include "Reg.h"
#include "Std_Types.h"



#define MAX_NUM_OF_PINS	(uint8)32

status	Dio_init(void);
status	Dio_read(uint8 Port,uint8 Pin,uint8 * val);
status	Dio_write(uint8 Port,uint8 Pin,uint8 val);

#endif /* DIO_H_ */
