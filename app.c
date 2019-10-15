


#include "timer.h"
#include "dio.h"
#include "Reg.h"
#include "TMU.h"


void System_Init();
void Led1_Toggle();
void Led2_Toggle();
int main(void){

	System_Init();


	while(1)
	{
	TMU_Dispatcher();


	}
	return 0;
}


void System_Init()
{

	Dio_init();
	TMU_Init(&TMU_Config);
	TMU_Start(500,Led2_Toggle,1,&TMU_Config);
	TMU_Start(250,Led1_Toggle,1,&TMU_Config);
	TMU_Stop(Led2_Toggle);

}
void Led1_Toggle()
{
	PORTA_REG ^=1<<PIN0;
}
void Led2_Toggle()
{
	PORTA_REG ^=1<<PIN1;
}


