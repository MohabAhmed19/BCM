

/* HEADER FILE GUARD */
#ifndef BCM_H
#define BCM_H

#include "../../UTILITIES/bit_manipulation.h"
#include "../../UTILITIES/registers.h"
#include "../../UTILITIES/standard_types.h"
#include "../../MCAL/UART/UART_interface.h"



typedef enum
{
	SUCCESS, null_pointer_error, double_speed_error, RX_interrupt_error, TX_interrupt_error, Data_Register_Empty_Interrupt_error, 
	receiver_enable_mode_error, transmitter_enable_mode_error, parity_mode_error, stop_bit_error, baudrate_error, wrong_type_error
}enu_system_status_t;


typedef enum
{
	UART, SPI, I2C
}enu_meduim_t;



typedef struct
{
	enu_meduim_t		comunication_meduim;
	str_UART_CONFG		*bcm_properties;
} str_t_bcm_meduim_t;





enu_system_status_t bcm_init(const str_t_bcm_meduim_t* ptr_str_bcm_meduim,
												void (*send_callback)(void),
												void (*receive_callback)(uint8_t*,int) );

enu_system_status_t bcm_deinit(const str_t_bcm_meduim_t* ptr_str_bcm_meduim);

enu_system_status_t bcm_send(const str_t_bcm_meduim_t* ptr_str_bcm_meduim, const uint8_t ar_data);

enu_system_status_t bcm_send_n(const str_t_bcm_meduim_t* ptr_str_bcm_meduim, const uint8_t* ar_data, int n);

enu_system_status_t bcm_receive(const str_t_bcm_meduim_t* ptr_str_bcm_meduim, const uint8_t *ar_data);

enu_system_status_t bcm_receive_n(const str_t_bcm_meduim_t* ptr_str_bcm_meduim, const uint8_t* ar_data,int n);



enu_system_status_t bcm_dispatcher(const str_t_bcm_meduim_t* ptr_str_bcm_meduim);

extern const str_t_bcm_meduim_t str_bcm_instance_ch_0;

#endif /* STANDARD_TYPES_H */
