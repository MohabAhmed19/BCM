#include "BCM.h"
#include "../../MCAL/UART/UART_interface.h"
#include "../../MCAL/dio/DIO_interface.h"
#include<string.h>




enu_system_status_t bcm_init(const str_t_bcm_meduim_t* ptr_str_bcm_meduim,
												void (*send_callback)(void),
												void (*receive_callback)(uint8_t*,int) )
{	
	if(ptr_str_bcm_meduim == NULL)
	return null_pointer_error;
	
	if(ptr_str_bcm_meduim->comunication_meduim==UART)
	{
		ptr_str_bcm_meduim->bcm_properties->receive_callback=receive_callback;
		ptr_str_bcm_meduim->bcm_properties->send_callback=send_callback;
		UART_init(ptr_str_bcm_meduim->bcm_properties);
	}
	else if(ptr_str_bcm_meduim->comunication_meduim==I2C)
	{
		//to do handling I2C
	}
	else if(ptr_str_bcm_meduim->comunication_meduim==SPI)
	{
		//to do handling SPI
	}
	else
	{
		return wrong_type_error;
	} 
	return SUCCESS;
}

enu_system_status_t bcm_deinit(const str_t_bcm_meduim_t* ptr_str_bcm_meduim)
{
	if(ptr_str_bcm_meduim == NULL)
	{
		return null_pointer_error;
	}
	else
	{
		if(ptr_str_bcm_meduim->comunication_meduim==UART)
		{
			UART_deinit();
		}
		else if(ptr_str_bcm_meduim->comunication_meduim==I2C)
		{
			//to do handling I2C
		}
		else if(ptr_str_bcm_meduim->comunication_meduim==SPI)
		{
			//to do handling SPI
		}
		else
		{
			return wrong_type_error;
		}	
	}
	
	return SUCCESS;
}

enu_system_status_t bcm_send(const str_t_bcm_meduim_t* ptr_str_bcm_meduim, uint8_t ar_data)
{
	if(ptr_str_bcm_meduim->comunication_meduim==UART)
	{
		UART_sendchar(ar_data);
	}
	
	else if(ptr_str_bcm_meduim->comunication_meduim==I2C)
	{
		//to do handling I2C
	}
	else if(ptr_str_bcm_meduim->comunication_meduim==SPI)
	{
		//to do handling SPI
	}
	else
	{
		return wrong_type_error;
	}
	return SUCCESS;
}

enu_system_status_t bcm_send_n(const str_t_bcm_meduim_t* ptr_str_bcm_meduim, const uint8_t* ar_data, int n)
{
	if(ptr_str_bcm_meduim->comunication_meduim==UART)
	{
		UART_sendstr(ar_data, n);
	}
	
	else if(ptr_str_bcm_meduim->comunication_meduim==I2C)
	{
		//to do handling I2C
	}
	else if(ptr_str_bcm_meduim->comunication_meduim==SPI)
	{
		//to do handling SPI
	}
	else
	{
		return wrong_type_error;
	}
	return SUCCESS;
}

enu_system_status_t bcm_receive(const str_t_bcm_meduim_t* ptr_str_bcm_meduim, const uint8_t *ar_data)
{
	if(ptr_str_bcm_meduim->comunication_meduim==UART)
	{
		UART_receivechar(ar_data);
	}
	else if(ptr_str_bcm_meduim->comunication_meduim==I2C)
	{
		//to do handling I2C
	}
	else if(ptr_str_bcm_meduim->comunication_meduim==SPI)
	{
		//to do handling SPI
	}
	else
	{
		return wrong_type_error;
	}
	return SUCCESS;
}

enu_system_status_t bcm_receive_n(const str_t_bcm_meduim_t* ptr_str_bcm_meduim, const uint8_t* ar_data,int n)
{
	if(ptr_str_bcm_meduim->comunication_meduim==UART)
	{
		UART_receivestr(ar_data,n);
	}
	
	else if(ptr_str_bcm_meduim->comunication_meduim==I2C)
	{
		//to do handling I2C
	}
	else if(ptr_str_bcm_meduim->comunication_meduim==SPI)
	{
		//to do handling SPI
	}
	else
	{
		return wrong_type_error;
	}
	return SUCCESS;
}


enu_system_status_t bcm_dispatcher(const str_t_bcm_meduim_t* ptr_str_bcm_meduim)
{
	if(ptr_str_bcm_meduim == NULL)
	{
		return null_pointer_error;
	}
	if(ptr_str_bcm_meduim->comunication_meduim==UART)
	{
		UART_dispatcher(ptr_str_bcm_meduim->bcm_properties);
	}
		
	
	else if(ptr_str_bcm_meduim->comunication_meduim==I2C)
	{
		//to do handling I2C
	}
	else if(ptr_str_bcm_meduim->comunication_meduim==SPI)
	{
		//to do handling SPI
	}
	else
	{
		return wrong_type_error;
	}
	return SUCCESS;
}

