#include "LCD.h"

void lcd_init()
{
	PIN_WRITE(LCD_CONTROL_DIR,RS_PIN,OUTPUT);
	PIN_WRITE(LCD_CONTROL_DIR,ENABLE_PIN,OUTPUT);
	PIN_WRITE(LCD_CONTROL_DIR,RW_PIN,OUTPUT);
	PIN_WRITE(LCD_CONTROL_VAL,RW_PIN,GPIO_LOW);
	
	switch (lcdmode)
	{
	case LCD8MODE:
				InitPort(LCD_DATA_DIR,OUTPUT);
				lcd_send_command (LCD8MODE)  ;
				lcd_send_command (DISPLAY_ON_CURRSOR_OFF);
				lcd_send_command (CLEAR_SCREEN)  ;
				lcd_send_command (FIRST_LINE)  ;
		break;
		
	case LCD4MODE:
		HIGHER_NIBBLE_HIGH(LCD_DATA_DIR);
		lcd_send_command (LCD4MODE2)  ;
		lcd_send_command (LCD4MODE3)  ;
		lcd_send_command (LCD4MODE)   ;
		lcd_send_command (DISPLAY_ON_CURRSOR_OFF);
		lcd_send_command (CLEAR_SCREEN)  ;
		lcd_send_command (FIRST_LINE)  ;
		break;
	}	
_delay_ms(200);
}

void lcd_send_command(uint8_t cmd)
{
	
	PIN_WRITE(LCD_CONTROL_VAL,RS_PIN,GPIO_LOW);
	switch (lcdmode)
	{
		case LCD8MODE:
		WritePort(LCD_DATA_VAL,cmd);
		enable_active();
		break;
		
		case LCD4MODE:
		LCD_DATA_VAL=((LCD_DATA_VAL&0x0f)|(cmd&0xf0));
		enable_active();
		LCD_DATA_VAL=((LCD_DATA_VAL&0x0f)|(cmd<<4));
		enable_active();
		break;
	}	
	_delay_ms(1);	
}

void lcd_send_data(uint8_t data)
{
	
	PIN_WRITE(LCD_CONTROL_VAL,RS_PIN,GPIO_HIGH);
	switch (lcdmode)
	{
		case LCD8MODE:
		WritePort(LCD_DATA_VAL,data);
		enable_active();
		break;
		
		case LCD4MODE:
		LCD_DATA_VAL=((LCD_DATA_VAL&0x0f)|(data&0xf0));
		enable_active();
		LCD_DATA_VAL=((LCD_DATA_VAL&0x0f)|(data<<4));
		enable_active();
		break;
	}
	_delay_ms(10);
	
	
}

void lcd_clear(void)
{
	lcd_send_command(CLEAR_SCREEN);
	_delay_ms(1);
}

void lcd_set_cursor(unsigned char x,unsigned char y)
{
	if (y==1)
	{
		lcd_send_command(FIRST_LINE+x);
	}
	else if(y==2) 
	{
		lcd_send_command(SECOND_LINE+x);
	}
	else
	{
		lcd_clear();
		lcd_out(1,0,"row 1 and 2 only ");
	}
}	

void lcd_send_string(char * str)
{
	while (*str!='\0')
	{
		lcd_send_data(*str);
		str++;
	}	
}	
 void lcd_out(unsigned char x,unsigned char y,char *str) 
 {
	 lcd_set_cursor(x,y);
	 lcd_send_string(str);
 }
 
 char * convert_data(unsigned int var)
 {
	 static char data[17];
	 char * arr=&data[16];
	 *arr='\0';
	 if (var==0)
	 {
		 return "0";
	 }
	 while (var !='\0')
	 {
		 arr--;
		 * arr = (var%10)+'0';
		 var=var/10;
		 
	 }
	 
	 return arr ;
	 
 /*another way */
 /*
 itoa(var,data,10); /* 10 for decimal 
 return data;
 */
 }
 void enable_active()
 {
	PIN_WRITE(LCD_CONTROL_VAL,ENABLE_PIN,GPIO_HIGH);
	lcdwait;
	PIN_WRITE(LCD_CONTROL_VAL,ENABLE_PIN,GPIO_LOW);
	lcdwait;
 }
 int str_to_int(char*ptr)
 {
	 char base=0;
	 int number=1;
	 for(uint16 i=0;i<strlen(ptr);i++)
	 {
		number=(ptr[i]-48)+number*base;
		base=10; 
	 }
	 return number;		 	
 }
 void stor_char(char*ptr,char loc)
 {
	 lcd_send_command(0x40+loc*8);
	for(int i=0;i<7;i++)
	{
		lcd_send_data(ptr[i]);
	}
 }
 void lcd_update()
 {
 /*** task 1 ***/
 //lcd_out(0,1,"hello");
 /*** task 2 ***/
 for (uint8 i=0;i<10;i++)
 {
	 lcd_out(i,1,"hello");
	 _delay_ms(2000);
	 lcd_out(0,1,"                  ");
	 _delay_ms(10);
 }
  
 }