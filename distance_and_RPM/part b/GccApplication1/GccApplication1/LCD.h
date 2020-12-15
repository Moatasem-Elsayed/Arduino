#ifndef L_C_D_h
#define L_C_D_h
#include "hardware.h"

typedef enum{
	CLEAR_SCREEN=1,
	RETURN_HOME=2,
	FIRST_LINE=0x80,
	SECOND_LINE=0xc0,
	LCD8MODE=0x38,
	LCD4MODE=0x28,
	LCD4MODE2=0x33,
	LCD4MODE3=0x32,
	DISPLAY_ON_CURRSOR_OFF=0x0c,
}LCD_COMMANDS;

void lcd_init();
void lcd_send_command(LCD_COMMANDS cmd);
void lcd_send_data(uint8_t data);
void lcd_set_cursor(uint8_t x,uint8_t y);
void lcd_send_string(char * str);
void lcd_out(uint8_t x,uint8_t y,char *str) ;
char * convert_data(unsigned int var);
int str_to_int(char*ptr);
void stor_char(char*ptr,char loc);
void lcd_clear(void);
void lcd_update();

#define lcdwait    _delay_us(100)
#endif




