#ifndef BUTTON_H_
#define BUTTON_H_
#include "hardware.h"
typedef enum
{
	button_1,
	button_2,
	button_3,
}button_number;


#define PULLUP_BUTTON(index)	PIN_WRITE(button_pull,index,GPIO_HIGH)	
#define PULLUP_BUTTONS()		PIN_WRITE(button_pull,button3_pin,GPIO_HIGH),PIN_WRITE(button_pull,button2_pin,GPIO_HIGH),PIN_WRITE(button_pull,button1_pin,GPIO_HIGH)

void buttons_init();
char *buttons_read();

void button_init(button_number no_bt);
char button_read(button_number no_bt);

void button_update();


#endif