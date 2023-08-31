/**************************************************/
/* Author  : Mohab Ahmed                          */
/* Date    : 29 April , 2023                      */
/* Version : V02                                  */
/* Hint    : interface file of UART               */
/**************************************************/

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

/*** INCLUDE DRIVER FILES ***/


#include "../../UTILITIES/standard_types.h"
#include "UART_PRECONFIG.h"



/** TYPEDEFINITION TO RETURN ERROR STATUS FORM THE FUNCTION **/
typedef enum {UART_VALID , UART_NOT_VALID} uart_errorstatus;




/*********************************************************/
/* enum for Speed of the UART                            */
/*********************************************************/
typedef enum
{
	not_doubled, doubled
}en_double_speed;

/**********************************************************/
/* enum for data size of the transmitted data the UART*/
/**********************************************************/
typedef enum
{
	five, six, seven, eight, nine
}en_data_size;

/**********************************************************/
/* enum for parity mode of the UART                       */
/**********************************************************/
typedef enum
{
	no_parity, even_parity, odd_parity
}en_parity_mode;

/**********************************************************/
/* enum for stop bits number in the UART                  */
/**********************************************************/
typedef enum
{
	single_bit, double_bit
}en_stop_bit;

/**********************************************************/
/* enum for baud rate of the UART                         */
/**********************************************************/
typedef enum
{
	BaudRate_2400, BaudRate_4800, BaudRate_9600, BaudRate_115200
}en_baud_rate;

/**********************************************************/
/* enum for transmit complete interrupt of the UART       */
/**********************************************************/
typedef enum
{
	enable_transmit_int, disable_transmit_int
}en_transmit_int;

/**********************************************************/
/* enum for receive complete interrupt of the UART        */
/**********************************************************/
typedef enum
{
	enable_recieve_int, disable_recieve_int
}en_recieve_int;

/**********************************************************/
/* enum for data register empty interrupt of the UART     */
/**********************************************************/
typedef enum
{
	enable_DRE_int, disable_DRE_int
}en_DRE_int;

typedef struct
{
	en_double_speed		double_speed;
	en_data_size		data_size;
	en_parity_mode		parity_mode;
	en_stop_bit			stop_bit;
	en_baud_rate		baud_rate;
	en_transmit_int		transmit_int;
	en_recieve_int		recieve_int;
	en_DRE_int			DRE_int;
	void (*send_callback)(void);
	void (*receive_callback)(uint8_t *ptr,int n_data);
}str_UART_CONFG;


/**************************************************************/
/** FUNCTION TO INITIALIZE THE UART                          **/
/** ARGUMENTS : VOID                                         **/
/** RETURNS   : uart_errorstatus                             **/
/**************************************************************/  
uint8_t UART_init(str_UART_CONFG *a_UART_CONFG);


uart_errorstatus UART_deinit(void);

/**************************************************************/
/** FUNCTION TO SEND BYTE VIA UART                           **/
/** ARGUMENTS : ua_a_data                                    **/
/** RETURNS   : uart_errorstatus                             **/
/**************************************************************/
uint8_t UART_sendchar(uint8_t ua_a_data);

/**************************************************************/
/** FUNCTION TO SEND STRING VIA UART                         **/
/** ARGUMENTS : ua_a_string                                  **/
/** RETURNS   : uart_errorstatus                             **/
/**************************************************************/
uint8_t UART_sendstr(uint8_t * ua_a_string, uint16_t a_n);

/********************************************************************/
/** FUNCTION TO RECEIVE BYTE VIA UART                              **/
/** ARGUMENTS : u8_recdata (POINTER TO STORE THE RECEIVED DATA)    **/
/** RETURNS   : uart_errorstatus                                   **/
/********************************************************************/
uint8_t UART_receivechar(uint8_t * u8_a_recdata);


/***************************************************************************/
/** FUNCTION TO RECEIVE STRING VIA UART                                   **/
/** ARGUMENTS : u8_a_recstring (POINTER TO STORE THE RECEIVED DATA)       **/
/** RETURNS   : uart_errorstatus                                          **/
/***************************************************************************/
uint8_t UART_receivestr(uint8_t * u8_a_recstring, uint16_t a_n);

/***************************************************************************/
/** handels tasks within the UART                                         **/
/** ARGUMENTS : void                                                      **/
/** RETURNS   : uart_errorstatus                                          **/
/***************************************************************************/
//uart_errorstatus uart_dispatcher(void);


uint8_t UART_dispatcher(const str_UART_CONFG *ptr_str_bcm_meduim);

#endif /* UART_INTERFACE_H_ */