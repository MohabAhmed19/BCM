/*
 * LED.c
 *
 * Created: 4/6/2023 8:26:35 AM
 *  Author: Mohab
 */ 


#include "LED.h"


uint8_t LED_init(uint8_t Port_number, uint8_t Pin_number)
{
	uint8_t error=0;
	if(DIO_setpindir(Port_number, Pin_number, DIO_PIN_OUTPUT) == 0 )
	{
		error=0;
	}
	else
	{
		error=1;
	}
	return error;
}


uint8_t LED_ON(uint8_t Port_number, uint8_t Pin_number)
{
	uint8_t error=0;
	if(DIO_setpinvalue(Port_number, Pin_number, DIO_PIN_HIGH) == 0)
	{
		error=0;
	}
	else
	{
		error=1;
	}
	return error;
}

uint8_t LED_OFF(uint8_t Port_number, uint8_t Pin_number)
{
	uint8_t error=0;
	if(DIO_setpinvalue(Port_number, Pin_number, DIO_PIN_LOW) == 0)
	{
		error=0;
	}
	else
	{
		error=1;
	}
	return error;
}

uint8_t LED_TOGGLE(uint8_t Port_number, uint8_t Pin_number)
{
	uint8_t error=0;
	if(DIO_togglepin(Port_number, Pin_number) == 0)
	{
		error=0;
	}
	else
	{
		error=1;
	}
	return error;
}