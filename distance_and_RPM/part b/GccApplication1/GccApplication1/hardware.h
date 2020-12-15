 /******************************************************************************
 *
 * Module:  hardware
 * File Name: hardware.h
 * Description: describe where the devices connected to microcontroller
 * Author: MOATASEM ELSAYED
 *
 *******************************************************************************/

#ifndef HARDWARE_H_
#define HARDWARE_H_
#include "micro.h"

#define LCD_4_MODE
#define LCD_DATA_DIR		GPIO_PORTC_CONTROL  
#define LCD_DATA_VAL		GPIO_PORTC_DATA 
#define LCD_CONTROL_DIR		GPIO_PORTC_CONTROL  
#define LCD_CONTROL_VAL		GPIO_PORTC_DATA

#define RS_PIN		2  
#define RW_PIN		1
#define ENABLE_PIN  3  

#if defined(LCD_8_MODE)
#define lcdmode	LCD8MODE
#elif	defined(LCD_4_MODE)
#define lcdmode	LCD4MODE
#endif

#endif