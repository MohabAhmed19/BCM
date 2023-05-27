/*
 * MCU_1.c
 *
 * Created: 5/27/2023 11:11:09 AM
 * Author : mohab
 */ 

//#include <avr/io.h>
#include "APP/app.h"

int main(void)
{
	APP1_init();
    /* Replace with your application code */
    while (1) 
    {
		APP1();
    }
}

