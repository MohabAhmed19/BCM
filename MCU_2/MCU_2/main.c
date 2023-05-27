/*
 * MCU_2.c
 *
 * Created: 5/27/2023 11:33:27 AM
 * Author : mohab
 */ 

//#include <avr/io.h>
#include "APP/app.h"	

int main(void)
{
	APP2_init();
    /* Replace with your application code */
    while (1) 
    {
		APP2();
    }
}

