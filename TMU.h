/*
 * TMU.h
 *
 *  Created on: Oct 15, 2019
 *      Author: Rafaat
 */

#ifndef TMU_H_
#define TMU_H_


#include "TMU_PBcfg.h"
#include "TMU_PREcfg.h"
#include "TIMER.h"
#include <avr/interrupt.h>


typedef void(*ptrTmuFunctionCallBk_t)(void);

typedef enum {ACTIVE,NOTACTIVE}Activity;
typedef enum {INVALID_ARGUMENT=-500,BUFFER_IS_FULL=-400,NOERROR=1}errorType;


typedef struct{
	uint8 Timer;
	uint8 Reselution;
}TMU_Config_t;

extern TMU_Config_t TMU_Config;


/*
 * Buffer for some information about the counsumers
 * Delay : the time that this consumer called after
 * Periodicity : this consumer will be periodic or oneshot
 * ptrTmuFunctionCallBk_t :Function name of consumer
 */
typedef struct
{
	volatile uint32 delay;
	volatile uint8 Periodicity;
	ptrTmuFunctionCallBk_t FuncName;

}TMU_Buffer;

extern TMU_Buffer TMU_Buffer_arr[NumOfTasks];

errorType TMU_Init(TMU_Config_t *Config);

errorType TMU_Start(uint32 delay, ptrTmuFunctionCallBk_t FuncName, uint8 priodicity,TMU_Config_t *Config);

void TMU_Stop(ptrTmuFunctionCallBk_t FuncName);

void TMU_Dispatcher();

#endif /* TMU_H_ */
