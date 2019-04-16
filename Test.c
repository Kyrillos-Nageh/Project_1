/*
 * Test.c
 *
 *  Created on: Feb 25, 2019
 *      Author: Kyrillos Nageh
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "OS.h"
#define OS_TIMER_UPDATE_REGISTER(TIME)		TCNT0=TIME

Task ptr;

Task ptr2;

void task_1(void)
{

	PORTA^=(1<<1);
	//_delay_ms(200);

}
void task_2(void)
{
	PORTA^=(1<<0);
	//_delay_ms(200);
}
int main()
{
	DDRA|=(1<<0)|(1<<1);
	OS_Init();
	OS_Start();
	ptr.Ptr2Function= task_1;
	ptr.Period= 1000;
	ptr.Delay= 0;
	ptr.Priority= 0;
	ptr.AutoStart=0;
	ptr2.Ptr2Function= task_2;
	ptr2.Period= 1000;
	ptr2.Delay= 300;
	ptr2.Priority= 0;
	ptr2.AutoStart=0;
	OS_CreatTask(&ptr);
	OS_CreatTask(&ptr2);
	while(1)
	{
		OS_DispatchTasks();
	}
	return 0;
}

ISR(TIMER0_OVF_vect)
{

	OS_TIMER_UPDATE_REGISTER(216);
	OS_Algorithm();

}
