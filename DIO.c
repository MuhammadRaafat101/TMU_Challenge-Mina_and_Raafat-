/*
 * DIO.c
 *
 *  Created on: Sep 20, 2019
 *      Author: Rafaat
 */

#include "DIO.h"


status	Dio_init(void)
{
	status retval = OK;
	uint8 Index=0;

	if(NUM_OF_PINS < MAX_NUM_OF_PINS )
	{
		for(Index = 0; Index < NUM_OF_PINS;Index++ )
		{
			Dio_arr[Index].Init = INITI;
			switch(Dio_arr[Index].Port)
			{
			case PORT_A :
				if(Dio_arr[Index].Dir == OUTPUT)
				{
					DDRA_REG |= (1<<Dio_arr[Index].Pin);
					if (Dio_arr[Index].Out == HIGH)
					{
						PORTA_REG |=1<<Dio_arr[Index].Pin;
					}
					else if(Dio_arr[Index].Out == LOW)
					{
						PORTA_REG &=~(1<<Dio_arr[Index].Pin);

					}
					else{
						Dio_arr[Index].Init = NOTINIT;
						retval =NOK;
					}
			}
			else if(Dio_arr[Index].Dir == INPUT)
				{
					DDRA_REG &= ~(1<<Dio_arr[Index].Pin);
					if (Dio_arr[Index].Res == PULLUP)
					{
						PORTA_REG |=1<<Dio_arr[Index].Pin;

					}else if(Dio_arr[Index].Res == EXTRES )
					{
						PORTA_REG &=~(1<<Dio_arr[Index].Pin);

					}else{

						Dio_arr[Index].Init = NOTINIT;
						retval =NOK;

					}
				}else
				{
					Dio_arr[Index].Init = NOTINIT;
					retval =NOK;
				}
				break;

			case PORT_B :
				if(Dio_arr[Index].Dir == OUTPUT)
				{
					DDRB_REG |= (1<<Dio_arr[Index].Pin);
					if (Dio_arr[Index].Out == HIGH)
					{
						PORTB_REG |=1<<Dio_arr[Index].Pin;

					}else if(Dio_arr[Index].Pin== LOW)
					{
						PORTB_REG &=~(1<<Dio_arr[Index].Pin);

					}else{

						Dio_arr[Index].Init = NOTINIT;
						retval =NOK;

					}

				}else if(Dio_arr[Index].Dir == INPUT)
				{
					DDRB_REG &= ~(1<<Dio_arr[Index].Pin);
					if (Dio_arr[Index].Res == PULLUP)
					{
						PORTB_REG |=1<<Dio_arr[Index].Pin;

					}else if(Dio_arr[Index].Res == EXTRES )
					{
						PORTB_REG &=~(1<<Dio_arr[Index].Pin);

					}else{

						Dio_arr[Index].Init = NOTINIT;
						retval =NOK;

					}
				}
				break;
			case PORT_C :
				if(Dio_arr[Index].Dir == OUTPUT)
				{
					DDRC_REG |= (1<<Dio_arr[Index].Pin);
					if (Dio_arr[Index].Out == HIGH)
					{
						PORTC_REG |=1<<Dio_arr[Index].Pin;

					}else if(Dio_arr[Index].Pin== LOW)
					{
						PORTC_REG &=~(1<<Dio_arr[Index].Pin);

					}else{

						Dio_arr[Index].Init = NOTINIT;
						retval =NOK;

					}

				}else if(Dio_arr[Index].Dir == INPUT)
				{
					DDRC_REG &= ~(1<<Dio_arr[Index].Pin);
					if (Dio_arr[Index].Res == PULLUP)
					{
						PORTC_REG |=1<<Dio_arr[Index].Pin;

					}else if(Dio_arr[Index].Res == EXTRES )
					{
						PORTC_REG &=~(1<<Dio_arr[Index].Pin);

					}else{

						Dio_arr[Index].Init = NOTINIT;
						retval =NOK;

					}
				}
				break;
			case PORT_D :
				if(Dio_arr[Index].Dir == OUTPUT)
				{
					DDRD_REG |= (1<<Dio_arr[Index].Pin);
					if (Dio_arr[Index].Out == HIGH)
					{
						PORTD_REG |=1<<Dio_arr[Index].Pin;

					}else if(Dio_arr[Index].Pin== LOW)
					{
						PORTD_REG &=~(1<<Dio_arr[Index].Pin);

					}else{

						Dio_arr[Index].Init = NOTINIT;
						retval =NOK;

					}

				}else if(Dio_arr[Index].Dir == INPUT)
				{
					DDRD_REG &= ~(1<<Dio_arr[Index].Pin);
					if (Dio_arr[Index].Res == PULLUP)
					{
						PORTD_REG |=1<<Dio_arr[Index].Pin;

					}else if(Dio_arr[Index].Res == EXTRES )
					{
						PORTD_REG &=~(1<<Dio_arr[Index].Pin);

					}else{

						Dio_arr[Index].Init = NOTINIT;
						retval =NOK;

					}
				}else{
					Dio_arr[Index].Init = NOTINIT;
					retval =NOK;
				}
				break;
			}
		}
	}else
	{
		for(Index = 0; Index < NUM_OF_PINS;Index++ )
		{

			Dio_arr[Index].Init = NOTINIT;
		}
		retval=NOK;
	}

	return retval;

}
status	Dio_read(uint8 Port,uint8 Pin,uint8 * val)
{
	uint8 Status;

	return Status;

}
status	Dio_write(uint8 Port,uint8 Pin,uint8 val)
{
	uint8 Status= OK;
	uint8 Index =0;

	for(Index = 0 ; Index<NUM_OF_PINS;Index++)
	{
		if( Dio_arr[Index].Port==Port && Dio_arr[Index].Pin==Pin)
		{

			if((Dio_arr[Index].Init==INITI) && (Dio_arr[Index].Dir == OUTPUT) &&(val == HIGH || val==LOW) )
			{
				switch(Port)
				{
				case PORT_A :

					if(val == HIGH)
					{
						PORTA_REG |= (1 <<Pin);

					}else if(val == LOW)
					{
						PORTA_REG &= ~( 1 <<Pin);
					}
					break;
				case PORT_B :
					if(val == HIGH)
					{
						PORTB_REG |= (1 <<Pin);

					}else if(val == LOW)
					{
						PORTB_REG &= ~( 1 <<Pin);
					}
					break;

				case PORT_C :

					if(val == HIGH)
					{
						PORTC_REG |= (1 <<Pin);

					}else if(val == LOW)
					{
						PORTC_REG &= ~( 1 <<Pin);
					}
					break;

				case PORT_D :

					if(val == HIGH)
					{
						PORTD_REG |= (1 <<Pin);

					}else if(val == LOW)
					{
						PORTD_REG &= ~( 1 <<Pin);
					}
					break;
				}
				Index = NUM_OF_PINS +1;
				break;
			}else{
				Status = NOK;
			}
		}else {
			Status = NOK;
		}
	}
	return Status;
}
