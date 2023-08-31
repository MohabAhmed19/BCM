/*
 * UART_linking_config.c
 *
 * Created: 8/28/2023 10:20:39 PM
 *  Author: mohab
 */ 
#include "UART_linking_config.h"

const str_UART_CONFG gl_UART_CONFIG_CH_1 =
{
	.double_speed = not_doubled,
	.data_size = eight,
	.parity_mode = odd_parity,
	.stop_bit = single_bit,
	.baud_rate = BaudRate_9600,
	.transmit_int = disable_transmit_int,
	.recieve_int = disable_recieve_int,
	.DRE_int = disable_DRE_int,
};