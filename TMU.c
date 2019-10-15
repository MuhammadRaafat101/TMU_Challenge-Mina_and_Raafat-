/*
 * TMU.c
 *
 *  Created on: Oct 15, 2019
 *      Author: Rafaat
 */
#include "TMU.h"


static uint32 Flag=0;		/* This Flag describe the numbers of Millis*/
static uint8 Resolution=0;	/*the resolution of the timer*/

static uint8_t ConsumerNumber=0;	/*Consumer Number */
static uint8_t CallFuncOnce=0;		/* a flag to make the called function called once*/


TMU_Buffer TMU_Buffer_arr[NumOfTasks];


/************************************************************************
 * @Function name 			-TMU_Init
 *
 * @brief					- This Function is used by user to initialize the timer and Resolution
 *
 * @param[in]				- a pointer to a structure which contains the cofiguration of Timer Selected and Resolution
 *
 * @return					- in case of error happens it return a number with the error code and it's type
 * 								else it returns NOERROR
 *
 *
 * @note					- none
 *
 */


errorType TMU_Init(TMU_Config_t *Config)
{
	errorType error=NOERROR;
	if(Config != NULL)						/* check if the pointer points to null or not*/
	{
		Timer_Init(Config->Timer);			/*Initialize the timer selected*/
		Timer_SetPrescaler(Config->Timer);	/*set the prescaler for the timer selected*/
		Resolution= Config ->Reselution;	/* Set the resolution*/
		sei();								/*Enable the global interrupt*/
		error=NOERROR;						/*return NOERROR*/
	}
	else if(Config == NULL)
	{
		error=INVALID_ARGUMENT;				/*return Invalid argument*/
		return error;
	}
	else
	{
	}
	return error;
}


/************************************************************************
 * @Function name 			-TMU_Start
 *
 * @brief					- This Function is for starting the new consumer
 *
 * @param[in]				-  delay that the consumer must start execution after
 * @param[in]				-  Function name to be executed
 * @param[in]				-  Periodicity if the consumer is periodic or not
 * @param[in]				-  pointer to a the configuration structure
 *
 *
 * @return					-  Error type
 *
 *
 * @note					- none
 *
 */



errorType TMU_Start(uint32 delay, ptrTmuFunctionCallBk_t FuncName, uint8 priodicity,TMU_Config_t *Config)
{
	errorType error = NOERROR;
	if(ConsumerNumber< NumOfTasks)									/* checks if the buffer is full or not*/
	{
		TMU_Buffer_arr[ConsumerNumber].FuncName=FuncName;			/*Set the function name*/
		TMU_Buffer_arr[ConsumerNumber].delay=delay;					/*set the delay*/
		TMU_Buffer_arr[ConsumerNumber].Periodicity=priodicity;		/*set the periodicity*/

		ConsumerNumber++;											/* increment the counter to the next empty place*/
		Timer_Start(Config->Timer);									/* Start timing*/
		error = NOERROR;											 /*return No Error*/
	}
	else
	{
		error = BUFFER_IS_FULL;										/*return buffer is full*/
	}
return  error;														/*return error*/
}



/************************************************************************
 * @Function name 			-TMU_Stop
 *
 * @brief					- This Function is for Stopping a consumer
 *
 * @param[in]				-  pointer to a the configuration structure
 *
 *
 * @return					-  Error type
 *
 *
 * @note					- none
 *
 */


void TMU_Stop(ptrTmuFunctionCallBk_t FuncName)
{
	for(uint8 Counter=0;Counter<ConsumerNumber;Counter++)
	{
		if(TMU_Buffer_arr[Counter].FuncName == FuncName)
		{
			TMU_Buffer_arr[Counter].FuncName =TMU_Buffer_arr[ConsumerNumber-1].FuncName;
		}
	}
	ConsumerNumber--;
}

/************************************************************************
 * @Function name 			-TMU_Dispatcher
 *
 * @brief					- This Function is for handle the timing between consumers
 *
 *
 *
 * @return					- None
 *
 *
 * @note					- none
 *
 */


void TMU_Dispatcher()
{
	if(CallFuncOnce ==1 )							/*This flag is to prevent the called function to be called more than one time during the reselution*/
	{
		for(uint8 x =0 ; x<ConsumerNumber;x++)
		{
			if( (Flag %(TMU_Buffer_arr[x].delay) == 0) )		/*Check if it is the time to execute the function or not*/
			{

				(*TMU_Buffer_arr[x].FuncName)();				/*Call the consumer*/

			}
		}
		CallFuncOnce=0;
	}
}

ISR(TIMER0_OVF_vect)
{
	static uint32 counter=0;
	counter++;
	if(counter%(4*Resolution) == 0)			/* This ecuation is to give the user the varity of selectiog his resolution*/
	{
		Flag++;
		CallFuncOnce=1;
	}

}
