/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 29 April , 2023                      */
/* Version : V02                                  */
/* Hint    : implementation of UART APIs          */
/**************************************************/

/*** INCLUDE LIBRARIES **/
#include "../../UTILITIES/bit_manipulation.h"
#include "../../UTILITIES/registers.h"
#include "../../UTILITIES/standard_types.h"
/** INCLUDE LOWER LAYERS INTERFACE FILES **/
#include "../dio/DIO_interface.h"


/*** INCLUDE DRIVER FILES ***/
#include "UART_interface.h"


char str_send[100];
char str_receive[100];
static uint16_t send_n=0;
static uint16_t receive_n=0;

/**************************************************************/
/** FUNCTION TO INITIALIZE THE UART                          **/
/** ARGUMENTS : VOID                                         **/
/** RETURNS   : uart_errorstatus                             **/
/**************************************************************/
uart_errorstatus UART_init(str_UART_CONFG *a_UART_CONFG)
{
		/** SET DIRECTIONS OF TX AND RX PINS **/
		DIO_setpindir(DIO_PORTD , DIO_PIN1 , DIO_PIN_OUTPUT);  /** SET TX PIN AS OUTPUT **/
		DIO_setpindir(DIO_PORTD , DIO_PIN0 , DIO_PIN_INPUT);   /** SET RX PIN AS INPUT  **/
		
		/* Set baud rate */
// 		UBRRH = 0 ;
// 		UBRRL = (uint8_t)103 ;
// 		
// 		/* Enable receiver and transmitter */
// 		UCSRB = (1<<3)|(1<<4);
// 		
// 		/* Set frame format: 8data, 2stop bit */
// 		UCSRC = (1<<7)|(1<<2)|(3<<1);
		
// 		UBRRL = 103;       /** ASSIGN UBRRL **/
// 		UBRRH = 0 ;
		
		if( a_UART_CONFG->baud_rate == BaudRate_9600)
		{
			uint32_t u32_a_BRVALUE = 0; /** VARIABLE TO HOLD THE VALUE TO BE STORED IN UBRRL **/
			u32_a_BRVALUE = ((80000) / (16 * 96)) - 1; /** CALCULATE THE UBRRL VALUE **/
			UBRRL = u32_a_BRVALUE;       /** ASSIGN UBRRL **/
		}
		
	
		else if( a_UART_CONFG->baud_rate == BaudRate_4800)
		{
			uint32_t u32_a_BRVALUE = 0; /** VARIABLE TO HOLD THE VALUE TO BE STORED IN UBRRL **/
			u32_a_BRVALUE = ((160000) / (16 * 48)) - 1; /** CALCULATE THE UBRRL VALUE **/
			UBRRL = u32_a_BRVALUE;       /** ASSIGN UBRRL **/
		}
		
		
		else if( a_UART_CONFG->baud_rate == BaudRate_2400)
		{
			uint32_t u32_a_BRVALUE = 0; /** VARIABLE TO HOLD THE VALUE TO BE STORED IN UBRRL **/
			u32_a_BRVALUE = ((F_CPU) / (16 * 2400)) - 1; /** CALCULATE THE UBRRL VALUE **/
			UBRRL = u32_a_BRVALUE;       /** ASSIGN UBRRL **/
		}
		
		
		else if( a_UART_CONFG->baud_rate == BaudRate_115200)
		{
			uint32_t u32_a_BRVALUE = 0; /** VARIABLE TO HOLD THE VALUE TO BE STORED IN UBRRL **/
			u32_a_BRVALUE = ((16000000) / (16 * 115200)) - 1; /** CALCULATE THE UBRRL VALUE **/
			UBRRL = u32_a_BRVALUE ;       /** ASSIGN UBRRL **/
		}
		
		
		/** ENABLE TRANSMISSION AND RECEIVING **/
		set_bit(UCSRB , 3);
		set_bit(UCSRB , 4);
		
		/** SELECT THE FIRST BIT TO WRITE TO THE UCSRC REGISTER **/
 		set_bit(UCSRC , 7);
 			
		if (a_UART_CONFG->data_size == five)
		{
			clear_bit(UCSRC , 1);
			clear_bit(UCSRC , 2);
			clear_bit(UCSRB , 2);
		}
		
		
		else if (a_UART_CONFG->data_size == six)
		{
			set_bit(UCSRC , 1);
			clear_bit(UCSRC , 2);
			clear_bit(UCSRB , 2);
		}
		
		
		else if (a_UART_CONFG->data_size == seven)
		{
			clear_bit(UCSRC , 1);
			set_bit(UCSRC , 2);
			clear_bit(UCSRB , 2);
		}
		
		
		else if (a_UART_CONFG->data_size == eight)
		{
			set_bit(UCSRC , 1);
			set_bit(UCSRC , 2);
			clear_bit(UCSRB , 2);
		}
		
		
		else if (a_UART_CONFG->data_size == nine)
		{
			set_bit(UCSRC , 1);
			set_bit(UCSRC , 2);
			set_bit(UCSRB , 2);
		}
		
		
		if (a_UART_CONFG->parity_mode == no_parity)
		{
			clear_bit(UCSRC , 4);
			clear_bit(UCSRC , 5);
		}
		
		
		else if (a_UART_CONFG->parity_mode == even_parity)
		{
			clear_bit(UCSRC , 4);
			set_bit(UCSRC , 5);
		}
		
		
		else if (a_UART_CONFG->parity_mode == odd_parity)
		{
			set_bit(UCSRC , 4);
			set_bit(UCSRC , 5);
		}
		
		if (a_UART_CONFG->stop_bit == single_bit)
		{
			clear_bit(UCSRC , 3);
		}
		
		
		else if (a_UART_CONFG->stop_bit == double_bit)
		{
			set_bit(UCSRC , 3);
		}
		
		
		/** SET THE UART SYNCRONYZATION MODE **/
		//#if UART_MODE == ASYNCRONOUS_MODE
		    clear_bit(UCSRC , 6);
		  
		//#elif UART_MODE == SYNCRONOUS_MODE
			/** SET THE CLOCK POLARITY IN THE SYNCRONOUS MODE **/
			//#if UART_CLOCK_POLARITY == RISING_EDGE_POLARITY
			//set_bit(UCSRB , 0);
		
			//#elif UART_CLOCK_POLARITY == FALLING_EDGE_POLARITY
			//clear_bit(UCSRB , 0);
			//#endif
       		
			set_bit(UCSRC , 6);
		//#endif
		
		if (a_UART_CONFG->double_speed == doubled)
		{
			set_bit(UCSRA , 1);
		}
		    
		
		else if (a_UART_CONFG->double_speed == not_doubled)
		{
			clear_bit(UCSRA , 1);
		}
		     
		
		//#if MULTI_PROCESSOR_MODE == ENABLE_MULTIPROCESSOR_MODE
		  //  set_bit(UCSRA , 0);
		
		//#elif MULTI_PROCESSOR_MODE == DISABLE_MULTIPROCESSOR_MODE
		     clear_bit(UCSRA , 0);
		//#endif
		
		if (a_UART_CONFG->recieve_int == enable_recieve_int)
		{
			set_bit(UCSRB , 7);
		}
     		
		
		else if (a_UART_CONFG->recieve_int == disable_recieve_int)
		{
			clear_bit(UCSRB , 7);
		}
		      
		

		if (a_UART_CONFG->transmit_int == enable_transmit_int)
		{
			set_bit(UCSRB , 6);
		}
     		
		
		else if (a_UART_CONFG->transmit_int == disable_transmit_int)
		{
			clear_bit(UCSRB , 6);
		}
		    
		
		if (a_UART_CONFG->DRE_int == enable_DRE_int)
		{
			set_bit(UCSRB , 5);
		}
		    
		
		else if (a_UART_CONFG->DRE_int == disable_DRE_int)
		{
			clear_bit(UCSRB , 5);
		}
		return UART_VALID;
}

uart_errorstatus UART_deinit(void)
{
	clear_bit(UCSRB,4);
	clear_bit(UCSRB,3);
	return UART_VALID;
}


/**************************************************************/
/** FUNCTION TO SEND BYTE VIA UART                           **/
/** ARGUMENTS : ua_a_data                                    **/
/** RETURNS   : uart_errorstatus                             **/
/**************************************************************/
uart_errorstatus UART_sendchar(uint8_t ua_a_data)
{
	while( ! ( UCSRA & (1 <<5))); /** HOLD HERE UNTILL DATA REGISTER IS EMPTY (DATA SENT) **/
    
	UDR = ua_a_data ; /** STORE THE DATA IN THE UDR BUFFER TO BE SENT **/
	return UART_VALID;
}

/**************************************************************/
/** FUNCTION TO SEND STRING VIA UART                         **/
/** ARGUMENTS : ua_a_string                                  **/
/** RETURNS   : uart_errorstatus                             **/
/**************************************************************/
uart_errorstatus UART_sendstr(uint8_t * ua_a_string, uint16_t a_n)
{
	uint8_t u8_a_lettercounter = 0 ; /** LETTERS COUNTER **/
		
	while (ua_a_string[u8_a_lettercounter] != '\0')  /** UNTILL THE STRING ISN'T NULL **/
	{
		UART_sendchar(ua_a_string[u8_a_lettercounter]); /** SEND THE LETTER USING UART_sendchar **/
		u8_a_lettercounter++; /** JUMP TO THE NEXT LETTER **/
	}
	send_n = a_n;
	return UART_VALID;
}

/********************************************************************/
/** FUNCTION TO RECEIVE BYTE VIA UART                              **/
/** ARGUMENTS : u8_recdata (POINTER TO STORE THE RECEIVED DATA)    **/
/** RETURNS   : uart_errorstatus                                   **/
/********************************************************************/
uart_errorstatus UART_receivechar(uint8_t * u8_a_recdata)
{
	while( ! (UCSRA & (1 << 7)) ) ; /** WAIT UNTILL THE DATA RECIVE FLAG RAISED **/
	
	*u8_a_recdata =  UDR ;	/** RETURN THE DATA IN UDR **/
	
	return UART_VALID;
}

/***************************************************************************/
/** FUNCTION TO RECEIVE STRING VIA UART                                   **/
/** ARGUMENTS : u8_a_recstring (POINTER TO STORE THE RECEIVED DATA)       **/
/** RETURNS   : uart_errorstatus                                          **/
/***************************************************************************/
uart_errorstatus UART_receivestr(uint8_t * u8_a_recstring, uint16_t a_n)
{
	uint8_t u8_a_lettercounter = 0 ; /** COUNTER TO LETTERS **/
	 
	//UART_receivechar(u8_a_recstring[u8_a_lettercounter]) ; /** RECEIVE THE FIRST CHARACTER **/
	
	while (u8_a_recstring[u8_a_lettercounter] != '\0') /** WHILE STRING ISN'T NULL **/
	{
		
		UART_receivechar(&u8_a_recstring[u8_a_lettercounter]); /** RECEIVE CHARACTER **/
		
		u8_a_lettercounter++ ; /** JUMP TO THE NEXT INDEX **/
		
		if(receive_n == 0)
		{
			return 0;
		}
		memcpy(u8_a_recstring, str_receive, receive_n>=a_n? a_n:receive_n);
		return receive_n>=a_n? a_n:receive_n;
	}
	return UART_VALID;
}



uart_errorstatus UART_dispatcher(const str_UART_CONFG *ptr_str_bcm_meduim)
{
	static uint16_t i=0;
	static uint16_t j=0;
	if(ptr_str_bcm_meduim == NULL)
	{
		return UART_NOT_VALID;
	}
	
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
	return UART_VALID;
}











