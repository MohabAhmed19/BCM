#include "BCM.h"
#include "../dio/DIO_interface.h"
#include<string.h>


char str_send[100];
char str_receive[100];
static uint16_t send_n=0;
static uint16_t receive_n=0;

enu_system_status_t bcm_init(str_bcm_meduim_t* ptr_str_bcm_meduim)
{	
	if(!ptr_str_bcm_meduim)  //check for null pointer
	{
		return NULL_PIONTER;
	}
	else if(UART == ptr_str_bcm_meduim->comunication_meduim)
	{
		//DIO_setpindir(DIO_PORTD , DIO_PIN1 , DIO_PIN_OUTPUT);  /** SET TX PIN AS OUTPUT **/
		//DIO_setpindir(DIO_PORTD , DIO_PIN0 , DIO_PIN_INPUT);   /** SET RX PIN AS INPUT  **/
		//check for double speed mode
		if(disable_double_speed == ptr_str_bcm_meduim->bcm_properties.double_speed)
		{
			clear_bit(UCSRA,1);
		}
		else if(enable_double_speed == ptr_str_bcm_meduim->bcm_properties.double_speed)
		{
			set_bit(UCSRA,1);
		}
		else
		{
			return double_speed_error;
		}
		
		//check for RX complete interrupt enable
		if(RX_interrupt_enable == ptr_str_bcm_meduim->bcm_properties.RX_interrupt)
		{
			set_bit(SREG,7);
			set_bit(UCSRB,7);
		}
		else if(RX_interrupt_disable == ptr_str_bcm_meduim->bcm_properties.RX_interrupt)
		{
			clear_bit(UCSRB,7);
		}
		else
		{
			return RX_interrupt_error;
		}
		
		//check for TX complete interrupt enable
		if(TX_interrupt_enable == ptr_str_bcm_meduim->bcm_properties.TX_interrupt)
		{
			set_bit(SREG,7);
			set_bit(UCSRB,6);
		}
		else if(TX_interrupt_disable == ptr_str_bcm_meduim->bcm_properties.TX_interrupt)
		{
			clear_bit(UCSRB,6);
		}
		else
		{
			return TX_interrupt_error;
		}
		
		//check for Data Register Empty Interrupt Enable
		if(Data_Register_Empty_Interrupt_Enable == ptr_str_bcm_meduim->bcm_properties.Data_Register_Empty_Interrupt)
		{
			set_bit(SREG,7);
			set_bit(UCSRB,5);
		}
		else if(Data_Register_Empty_Interrupt_disable == ptr_str_bcm_meduim->bcm_properties.Data_Register_Empty_Interrupt)
		{
			clear_bit(UCSRB,5);
		}
		else
		{
			return Data_Register_Empty_Interrupt_error;
		}
		
		//check for Receiver Enable
		if(receiver_enable == ptr_str_bcm_meduim->bcm_properties.receiver_enable_mode)
		{
			set_bit(UCSRB,4);
		}
		else if(receiver_disable == ptr_str_bcm_meduim->bcm_properties.receiver_enable_mode)
		{
			clear_bit(UCSRB,4);
		}
		else
		{
			return receiver_enable_mode_error;
		}
		
		//check for Transmitter Enable
		if(transmitter_enable == ptr_str_bcm_meduim->bcm_properties.transmitter_enable_mode)
		{
			set_bit(UCSRB,3);
		}
		else if(transmitter_disable == ptr_str_bcm_meduim->bcm_properties.transmitter_enable_mode)
		{
			clear_bit(UCSRB,3);
		}
		else
		{
			return transmitter_enable_mode_error;
		}
		
		//check for parity mode
		if(no_parity == ptr_str_bcm_meduim->bcm_properties.parity_mode)
		{
			set_bit(UCSRC,7);
			clear_bit(UCSRC,5);
			clear_bit(UCSRC,4);
		}
		else if(even_parity == ptr_str_bcm_meduim->bcm_properties.parity_mode)
		{
			set_bit(UCSRC,7);
			set_bit(UCSRC,5);
			clear_bit(UCSRC,4);
		}
		else if(odd_parity == ptr_str_bcm_meduim->bcm_properties.parity_mode)
		{
			set_bit(UCSRC,7);
			set_bit(UCSRC,5);
			set_bit(UCSRC,4);
		}
		else
		{
			return parity_mode_error;
		}
		
		//check for Stop Bit Select
		if(one_stop_bit == ptr_str_bcm_meduim->bcm_properties.stop_bits)
		{
			set_bit(UCSRC,7);
			clear_bit(UCSRC,3);
		}
		else if(two_stop_bit == ptr_str_bcm_meduim->bcm_properties.stop_bits)
		{
			set_bit(UCSRC,7);
			set_bit(UCSRC,3);
		}
		else
		{
			set_bit(UCSRC,7);
			return stop_bit_error;
		}
		
		//check for the selected baudrate
		uint16_t UBRR=0;
		clear_bit(UCSRC,7);
		if(baudrate_2400 == ptr_str_bcm_meduim->bcm_properties.baudrate)
		{
			if(disable_double_speed == ptr_str_bcm_meduim->bcm_properties.double_speed)
			{
				UBRR = ((UART_frequency/100) / (16 * 24)) - 1;
			}
			else
			{
				UBRR = (UART_frequency / (8 * 2400)) - 1;
			}
			UBRRH = (uint8_t)(UBRR>>8);
			UBRRL = (uint8_t)UBRR;
		}
		else if(baudrate_4800 == ptr_str_bcm_meduim->bcm_properties.baudrate)
		{
			if(disable_double_speed == ptr_str_bcm_meduim->bcm_properties.double_speed)
			{
				UBRR = ((UART_frequency/100) / (16 * 48)) - 1;
			}
			else
			{
				UBRR = ((UART_frequency/100) / (8 * 48)) - 1;
			}
			UBRRH = (uint8_t)(UBRR>>8);
			UBRRL = (uint8_t)UBRR;
		}
		else if(baudrate_9600 == ptr_str_bcm_meduim->bcm_properties.baudrate)
		{
			if(disable_double_speed == ptr_str_bcm_meduim->bcm_properties.double_speed)
			{
				//UBRR = ((UART_frequency/100) / (16 * 96)) - 1;
				UBRR = 51;
			}
			else
			{
				UBRR = ((UART_frequency/100) / (8 * 96)) - 1;
			}
			UBRRH = (uint8_t)(UBRR>>8);
			UBRRL = (uint8_t)UBRR;
		}
		else if(baudrate_14_4k == ptr_str_bcm_meduim->bcm_properties.baudrate)
		{
			if(disable_double_speed == ptr_str_bcm_meduim->bcm_properties.double_speed)
			{
				UBRR = ((UART_frequency/100) / (16 * 144)) - 1;
			}
			else
			{
				UBRR = ((UART_frequency/100) / (8 * 144)) - 1;
			}
			UBRRH = (uint8_t)(UBRR>>8);
			UBRRL = (uint8_t)UBRR;
		}
		else if(baudrate_19_2k == ptr_str_bcm_meduim->bcm_properties.baudrate)
		{
			if(disable_double_speed == ptr_str_bcm_meduim->bcm_properties.double_speed)
			{
				UBRR = ((UART_frequency/100) / (16 * 192)) - 1;
			}
			else
			{
				UBRR = ((UART_frequency/100) / (8 * 192)) - 1;
			}
			UBRRH = (uint8_t)(UBRR>>8);
			UBRRL = (uint8_t)UBRR;
		}
		else if(baudrate_28_8k == ptr_str_bcm_meduim->bcm_properties.baudrate)
		{
			if(disable_double_speed == ptr_str_bcm_meduim->bcm_properties.double_speed)
			{
				UBRR = ((UART_frequency/100) / (16 * 288)) - 1;
			}
			else
			{
				UBRR = ((UART_frequency/100) / (8 * 288)) - 1;
			}
			UBRRH = (uint8_t)(UBRR>>8);
			UBRRL = (uint8_t)UBRR;
		}
		else if(baudrate_38_4k == ptr_str_bcm_meduim->bcm_properties.baudrate)
		{
			if(disable_double_speed == ptr_str_bcm_meduim->bcm_properties.double_speed)
			{
				UBRR = ((UART_frequency/100) / (16 * 384)) - 1;
			}
			else
			{
				UBRR = ((UART_frequency/100) / (8 * 384)) - 1;
			}
			UBRRH = (uint8_t)(UBRR>>8);
			UBRRL = (uint8_t)UBRR;
		}
		else if(baudrate_57_6k == ptr_str_bcm_meduim->bcm_properties.baudrate)
		{
			if(disable_double_speed == ptr_str_bcm_meduim->bcm_properties.double_speed)
			{
				UBRR = ((UART_frequency/100) / (16 * 576)) - 1;
			}
			else
			{
				UBRR = ((UART_frequency/100) / (8 * 576)) - 1;
			}
			UBRRH = (uint8_t)(UBRR>>8);
			UBRRL = (uint8_t)UBRR;
		}
		else if(baudrate_76_8k == ptr_str_bcm_meduim->bcm_properties.baudrate)
		{
			if(disable_double_speed == ptr_str_bcm_meduim->bcm_properties.double_speed)
			{
				UBRR = ((UART_frequency/100) / (16 * 768)) - 1;
			}
			else
			{
				UBRR = ((UART_frequency/100) / (8 * 768)) - 1;
			}
			UBRRH = (uint8_t)(UBRR>>8);
			UBRRL = (uint8_t)UBRR;
		}
		else if(baudrate_115_2k == ptr_str_bcm_meduim->bcm_properties.baudrate)
		{
			if(disable_double_speed == ptr_str_bcm_meduim->bcm_properties.double_speed)
			{
				UBRR = ((UART_frequency/100) / (16 * 1152)) - 1;
			}
			else
			{
				UBRR = ((UART_frequency/100) / (8 * 1152)) - 1;
			}
			UBRRH = (uint8_t)(UBRR>>8);
			UBRRL = (uint8_t)UBRR;
		}
		else if(baudrate_230_4k == ptr_str_bcm_meduim->bcm_properties.baudrate)
		{
			if(disable_double_speed == ptr_str_bcm_meduim->bcm_properties.double_speed)
			{
				UBRR = ((UART_frequency/100) / ((long int)16 * (long int)2304)) - 1;
			}
			else
			{
				UBRR = ((UART_frequency/100) / (8 * 2304)) - 1;
			}
			UBRRH = (uint8_t)(UBRR>>8);
			UBRRL = (uint8_t)UBRR;
		}
		else if(baudrate_250k == ptr_str_bcm_meduim->bcm_properties.baudrate)
		{
			if(disable_double_speed == ptr_str_bcm_meduim->bcm_properties.double_speed)
			{
				UBRR = ((UART_frequency/10000) / (16 * 25)) - 1;
			}
			else
			{
				UBRR = ((UART_frequency/10000) / (8 * 25)) - 1;
			}
			UBRRH = (uint8_t)(UBRR>>8);
			UBRRL = (uint8_t)UBRR;
		}
		else
		{
			return baudrate_error;
		}
		set_bit(UCSRC,7);
		set_bit(UCSRC,1);
		set_bit(UCSRC,2);
		clear_bit(UCSRC , 6);
		clear_bit(UCSRB,2);
		ptr_str_bcm_meduim->bcm_properties.transmit_flag=TX_complete;
		ptr_str_bcm_meduim->bcm_properties.receive_flag=flag_default;
		ptr_str_bcm_meduim->bcm_properties.data_register_flag=flag_default;
	}
	else if(SPI == ptr_str_bcm_meduim->comunication_meduim)
	{
		//
	}
	else if(I2C == ptr_str_bcm_meduim->comunication_meduim)
	{
		//
	}
	return SUCCESS;
}

enu_system_status_t bcm_deinit(str_bcm_meduim_t* ptr_str_bcm_meduim)
{
	clear_bit(UCSRB,4);
	clear_bit(UCSRB,3);
}

void bcm_send(uint8_t ar_data)
{
	UDR = ar_data;
}

void bcm_send_n(const uint8_t* ar_data, int n)
{
	memcpy(str_send, ar_data, n);
	send_n = n;
}

void bcm_receive(uint8_t *ar_data)
{
	*ar_data = UDR;
}

int bcm_receive_n(uint8_t* ar_data,int n)
{
	if(receive_n == 0)
	{
		return 0;
	}
	memcpy(ar_data, str_receive, receive_n>=n? n:receive_n);
	return receive_n>=n? n:receive_n;
}


enu_system_status_t bcm_dispatcher(str_bcm_meduim_t* ptr_str_bcm_meduim)
{
	
	static uint16_t i=0;
	static uint16_t j=0;
	if((read_bit(UCSRA, 6) == 1 && i<send_n) || (i==0 && send_n>0))
	{
		set_bit(UCSRA,6);
		bcm_send(str_send[i]);
		i++;
	}
	if(read_bit(UCSRA, 7) == 1)
	{
		bcm_receive(&str_receive[j]);
		j++;
	}
	if(i!=0 && i==send_n)
	{
		ptr_str_bcm_meduim->send_callback();
		i=0;
		send_n=0;
	}
	
	if(j>0 && str_receive[j-1]=='\r')
	{
		str_receive[j-1]='\0';
		ptr_str_bcm_meduim->receive_callback(str_receive, j);
		j=0;
	}
	
}

