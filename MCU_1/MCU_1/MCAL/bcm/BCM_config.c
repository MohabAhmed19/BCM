#include "BCM.h"
#include "../dio/DIO_interface.h"

volatile enu_flag_t transmit_flag=TX_complete;
volatile enu_flag_t receive_flag=flag_default;
volatile enu_flag_t data_register_flag=flag_default;



struct str_bcm_meduim_t str_bcm_instance_ch_0 =
{
	.comunication_meduim =							UART,
	.bcm_properties.double_speed	=				disable_double_speed,
	.bcm_properties.RX_interrupt	=				RX_interrupt_disable,
	.bcm_properties.TX_interrupt	=				TX_interrupt_disable,
	.bcm_properties.Data_Register_Empty_Interrupt=	Data_Register_Empty_Interrupt_disable,
	.bcm_properties.receiver_enable_mode	=		receiver_enable,
	.bcm_properties.transmitter_enable_mode	=		transmitter_enable,
	.bcm_properties.parity_mode	=					no_parity,
	.bcm_properties.stop_bits	=					one_stop_bit,
	.bcm_properties.baudrate	=					baudrate_9600
};

