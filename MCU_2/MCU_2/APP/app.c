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
	if(!strcmp(ptr,"BCM Operating"))
	{
		DIO_togglepin(DIO_PORTC, DIO_PIN1);
		TMR0_delayms(500);
		bcm_send_n(&str_bcm_instance_ch_0,"Confirm BCM operating\r",22);
	}
	
}


void APP2_init(void)
{

	
	if(SUCCESS ==bcm_init(&str_bcm_instance_ch_0,send_callback,receive_callback))
	{
		LED_init(DIO_PORTC, DIO_PIN0);
		LED_init(DIO_PORTC, DIO_PIN1);
	}
}

void APP2(void)
{
	bcm_dispatcher(&str_bcm_instance_ch_0);
}