

/* HEADER FILE GUARD */
#ifndef BCM_H
#define BCM_H

#include "../../UTILITIES/bit_manipulation.h"
#include "../../UTILITIES/registers.h"
#include "../../UTILITIES/standard_types.h"

#define UART_frequency 8000000



typedef enum
{
	enable_double_speed, disable_double_speed
}enu_double_speed_mode;

typedef enum
{
	no_parity, even_parity, odd_parity
}enu_parity_mode;

typedef enum
{
	one_stop_bit, two_stop_bit
}enu_stop_bits_number;

typedef enum
{
	baudrate_2400, baudrate_4800, baudrate_9600, baudrate_14_4k, baudrate_19_2k,baudrate_28_8k, baudrate_38_4k,
	baudrate_57_6k, baudrate_76_8k, baudrate_115_2k, baudrate_230_4k, baudrate_250k
}enu_baudrate_mode;

typedef enum
{
	RX_interrupt_enable, RX_interrupt_disable
}enu_RX_interrupt_mode;

typedef enum
{
	TX_interrupt_enable, TX_interrupt_disable
}enu_TX_interrupt_mode;

typedef enum
{
	Data_Register_Empty_Interrupt_Enable, Data_Register_Empty_Interrupt_disable
}enu_data_register_empty_interrupt_mode;

typedef enum
{
	receiver_enable, receiver_disable
}enu_receiver_enable;

typedef enum
{
	transmitter_enable, transmitter_disable
}enu_transmitter_enable;

typedef enum
{
	SUCCESS, NULL_PIONTER, double_speed_error, RX_interrupt_error, TX_interrupt_error, Data_Register_Empty_Interrupt_error, 
	receiver_enable_mode_error, transmitter_enable_mode_error, parity_mode_error, stop_bit_error, baudrate_error
}enu_system_status_t;

typedef enum
{
	flag_default, TX_complete, RX_complete, data_register_empty
}enu_flag_t;

typedef enum
{
	UART, SPI, I2C
}enu_meduim_t;

typedef struct str_bcm_instance_t
{
	enu_double_speed_mode				    double_speed;
	enu_RX_interrupt_mode			        RX_interrupt;
	enu_TX_interrupt_mode   			    TX_interrupt;
	enu_data_register_empty_interrupt_mode	Data_Register_Empty_Interrupt;
	enu_receiver_enable                     receiver_enable_mode;
	enu_transmitter_enable                  transmitter_enable_mode;
	enu_parity_mode    				        parity_mode;
	enu_stop_bits_number				    stop_bits;
	enu_baudrate_mode 				        baudrate;
	volatile enu_flag_t transmit_flag;
	volatile enu_flag_t receive_flag;
	volatile enu_flag_t data_register_flag;
}str_bcm_instance_t;

typedef struct str_bcm_meduim_t
{
	enu_meduim_t			comunication_meduim;
	struct str_bcm_instance_t		bcm_properties;
	void (*send_callback)(void);
	void (*receive_callback)(uint8_t *ptr,int n_data);
}str_bcm_meduim_t;




enu_system_status_t bcm_init(str_bcm_meduim_t* ptr_str_bcm_meduim);

enu_system_status_t bcm_deinit(str_bcm_meduim_t* ptr_str_bcm_meduim);

void bcm_send(uint8_t ar_data);

void bcm_send_n(const uint8_t* ar_data, int n);

void bcm_receive(uint8_t *ar_data);

int bcm_receive_n(uint8_t* ar_data,int n);

enu_system_status_t bcm_dispatcher(str_bcm_meduim_t* ptr_str_bcm_meduim);

extern struct str_bcm_meduim_t str_bcm_instance_ch_0;

#endif /* STANDARD_TYPES_H */
