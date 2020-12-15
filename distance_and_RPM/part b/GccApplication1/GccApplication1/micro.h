 /******************************************************************************
 * Module: Micro
 * File Name: Micro.h
 * Description: list the names of micros , GPIOS macros and data types 
 * Author: Moatasem El sayed
 *******************************************************************************/
#ifndef __MAIN_H__
#define __MAIN_H__

#include "config.h"


/* GPIO definitions */
/* GPIO Pins */
#define PIN_0              (0)
#define PIN_1              (1)
#define PIN_2              (2)
#define PIN_3              (3)
#define PIN_4              (4)
#define PIN_5              (5)
#define PIN_6              (6)
#define PIN_7              (7)

/* GPIO Port Registers redefinition */
#define GPIO_PORTA_DATA         (PORTA)
#define GPIO_PORTA_CONTROL      ( DDRA)
#define GPIO_PORTA_INPUT        ( PINA)

#define GPIO_PORTB_DATA         (PORTB)
#define GPIO_PORTB_CONTROL      ( DDRB)
#define GPIO_PORTB_INPUT        ( PINB)

#define GPIO_PORTC_DATA         (PORTC)
#define GPIO_PORTC_CONTROL      ( DDRC)
#define GPIO_PORTC_INPUT        ( PINC)

#define GPIO_PORTD_DATA         (PORTD)
#define GPIO_PORTD_CONTROL      ( DDRD)
#define GPIO_PORTD_INPUT        ( PIND)

#define GPIO_PORTE_DATA         (PORTE)
#define GPIO_PORTE_CONTROL      ( DDRE)
#define GPIO_PORTE_INPUT        ( PINE)

/****directions for GPIOS**/
#define INPUT		0
#define	OUTPUT		1

/**Values of OUTPUT**/

#define GPIO_HIGH	1
#define	GPIO_LOW	0

/*	MACROS FOR PIN 	*/

#define PIN_WRITE(reg,pin,data) (reg)=(reg&(~(1<<pin)))|(data<<pin)
#define GET_PIN(reg,index) 	((reg>>index)&0x01)
#define TOG_PIN(reg,pin)	reg=^(1<<(pin))

/* 	MACROS TO PORT	*/
#define InitPort(CONTROL, DIRECTION)   ((CONTROL) = (DIRECTION)?(~GPIO_LOW):(GPIO_LOW))
#define WritePort(PORT, DATA)          ((PORT) = (DATA))
#define PORT_MASK(reg,val)		(reg)|=(val)
#define ReadPort(PORT)                 (PORT)


/*	LOWER NIBBLE 0-3	*/

#define get_lower(reg) 			(reg)&0x0f
#define LOWER_NIBBLE_HIGH(reg) 		reg=((reg&0xf0)|0x0f)
#define LOWER_NIBBLE_VALUE(reg,data) 	reg=(reg&0xF0)|data&0X0F

/*	HIGHER NIBBLE 4-8	*/

#define GET_HIGHER(reg) 						(reg)&(0xF0)
#define HIGHER_NIBBLE_HIGH(reg) 				(reg)=((reg&0x0f)|(0xf0))
#define HIGHER_NIBBLE_VALUE(reg,data) 			(reg)=(reg&0x0f)|(data<<4)

/* OTHER peripherals*/

// FOR EXAMPLE #define GLOBAL_INTERRUPT_ENABLE	(SREG |= 1<<7)

/* DATA TYPES	*/

typedef unsigned char         uint8;          /*           0 .. 255             */
typedef signed char           sint8;          /*        -128 .. +127            */
typedef unsigned short        uint16;         /*           0 .. 65535           */
typedef signed short          sint16;         /*      -32768 .. +32767          */
typedef unsigned long         uint32;         /*           0 .. 4294967295      */
typedef signed long           sint32;         /* -2147483648 .. +2147483647     */
typedef unsigned long long    uint64;         /*       0..18446744073709551615  */
typedef signed long long      sint64;
typedef float                 float32;
typedef double                float64;

/* Boolean Data Type */
typedef unsigned char bool;

/* Boolean Values */
#ifndef FALSE
#define FALSE       (0u)
#endif
#ifndef TRUE
#define TRUE        (1u)
#endif
#endif