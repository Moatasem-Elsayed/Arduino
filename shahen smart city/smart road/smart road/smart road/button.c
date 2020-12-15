#include "button.h"
#include "led.h"
static flag_rising,flag_falling;
void buttons_init()
{
	PIN_WRITE(buttondir,button1_pin,INPUT);
	PIN_WRITE(buttondir,button2_pin,INPUT);
	PIN_WRITE(buttondir,button3_pin,INPUT);
	
}

void button_init(button_number no_bt)
{
switch(no_bt)
{
	case button_1:PIN_WRITE(buttondir,button1_pin,INPUT);break;
	case button_2:PIN_WRITE(buttondir,button2_pin,INPUT);break;
	case button_3:PIN_WRITE(buttondir,button3_pin,INPUT);break;
}	
}

char button_read(button_number no_bt)
{
	char x;
	switch(no_bt)
	{
		case button_1:x=GET_PIN(buttonval,button1_pin);break;
		case button_2:x=GET_PIN(buttonval,button2_pin);break;
		case button_3:x=GET_PIN(buttonval,button3_pin);break;
	}
return x; }
char* buttons_read()
{
	static char button_value[3]={0};
		for (int i=0;i<3;i++)
		{
		button_value[i]=button_read(i);	
		}
		return button_value;
}
	 
	


void button_update()
{
	/**********************************************************************
									task1
	**********************************************************************/
	if(button_read(button_1)==0)
	{
		led_write(ledred,GPIO_HIGH);
	}
	if(button_read(button_2)==1)
	{
		led_write(ledyellow,GPIO_HIGH);
	}
	if(button_read(button_3)==0)
	{
		led_write(ledgreen,GPIO_HIGH);
	}
	
	/**********************************************************************
									task2
	**********************************************************************/
	/*char *readval;
		readval=buttons_read();
		for(int i=0;i<3;i++)
		{
			if(readval[i]==0)
			{
				led_write(i,GPIO_HIGH);
			}
		}
	*/
}