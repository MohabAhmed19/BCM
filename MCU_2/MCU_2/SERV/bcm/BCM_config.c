#include "BCM.h"
#include "../../MCAL/dio/DIO_interface.h"
#include "../../MCAL/UART/UART_linking_config.h"



const str_t_bcm_meduim_t str_bcm_instance_ch_0={.comunication_meduim = UART,
	.bcm_properties = &gl_UART_CONFIG_CH_1
};
