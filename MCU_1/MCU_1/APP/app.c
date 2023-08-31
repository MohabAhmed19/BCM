/*
 * app.c
 *
 * Created: 5/27/2023 11:16:32 AM
 *  Author: mohab
 */ 
#include "app.h"
#include "../SERV/bcm/BCM.h"

void send_callback(void)
{
	LED_TOGGLE(DIO_PORTC, DIO_PIN0);
}

void receive_callback(uint8_t *ptr,int n_data)
{
	//DIO_setpinvalue(DIO_PORTC, DIO_PIN2, DIO_PIN_HIGH);
	if(!strcmp(ptr,"Confirm BCM operating"))
	{
		LED_TOGGLE(DIO_PORTC, DIO_PIN1);
	}
	
}

void APP1_init(void)
{
	if(SUCCESS == bcm_init(&str_bcm_instance_ch_0,send_callback,receive_callback))
	{
		LED_init(DIO_PORTC, DIO_PIN0);
		LED_init(DIO_PORTC, DIO_PIN1);
		TMR0_delayms(1000);
		bcm_send_n(&str_bcm_instance_ch_0,"BCM Operating\r", 14);
	}
}

void APP1(void)
{
	bcm_dispatcher(&str_bcm_instance_ch_0);
}