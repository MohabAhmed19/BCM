/*
 * app.c
 *
 * Created: 5/27/2023 11:16:32 AM
 *  Author: mohab
 */ 
#include "app.h"

void send_callback(void)
{
	DIO_togglepin(DIO_PORTC, DIO_PIN0);
}

void receive_callback(uint8_t *ptr,int n_data)
{
	//DIO_setpinvalue(DIO_PORTC, DIO_PIN2, DIO_PIN_HIGH);
	if(!strcmp(ptr,"Confirm BCM operating"))
	{
		DIO_togglepin(DIO_PORTC, DIO_PIN1);
	}
	
}

void APP1_init(void)
{
	int buffer[20];
	str_bcm_instance_ch_0.receive_callback=receive_callback;
	str_bcm_instance_ch_0.send_callback=send_callback;
	if(SUCCESS == bcm_init(&str_bcm_instance_ch_0))
	{
		DIO_setpindir(DIO_PORTC, DIO_PIN0, DIO_PIN_OUTPUT);
		DIO_setpindir(DIO_PORTC, DIO_PIN1, DIO_PIN_OUTPUT);
	};
	TMR0_delayms(1000);
	bcm_send_n("BCM Operating\r", 14);
}

void APP1(void)
{
	bcm_dispatcher(&str_bcm_instance_ch_0);
}