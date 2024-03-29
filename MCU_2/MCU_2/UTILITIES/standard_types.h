/***********************************************************************************/
/* Author    : Mustafa Mohammed Abdou                                              */
/* Date      : 26 Feb 2020                                                         */
/* Version   : V01                                                                 */
/* Hint      : typef for standard types                                            */
/***********************************************************************************/

/* HEADER FILE GUARD */
#ifndef STANDARD_TYPES_H
#define STANDARD_TYPES_H

#define nullPtr ((void*)0)

#define NULL 0

typedef unsigned char uint8_t;          /* 1-BYTE UNSIGNED DATA (0 - 255)                */
typedef signed char   sint8_t;          /* 1-BYTE SIGNED DATA   (0 - 127) or (-1 - -128) */

typedef unsigned short int  uint16_t;   /* 2-BYTES UNSIGNED DATA   */
typedef signed short int    sint16_t;   /* 2-BYTES SIGNED DATA     */

typedef unsigned long int  uint32_t;     /* 4-BYTES UNSIGNED DATA  */
typedef signed long int    sint32_t;     /* 4-BYTES SIGNED DATA    */


typedef float  float32;                 /* 4-BYTES FLOATING DATA */
typedef double double64;                /* 8-BYTES FLOATING DATA */

/*typedef enum err_state
{
	SUCCESS,FAIL
}err_state;*/
typedef enum pin_dir
{
	INPUT,OUTPUT
}pin_dir;

typedef enum pin_state
{
	LOW,HIGH
}pin_state;

#endif /* STANDARD_TYPES_H */
