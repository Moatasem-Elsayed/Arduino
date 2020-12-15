/*
 * GccApplication1.c
 *
 * Created: 02/06/2020 18:56:13
 *  Author: M
 */ 


#include "config.h"
#include "LCD.h"
unsigned short int no_pulses=0;
unsigned int distance_per_1rotation,distance;
int main(void)
{
	lcd_init();
	DDRA=0x00;
	DDRB=0x00;
    while(1)
    {
		  distance_per_1rotation = (2*3.14*0.1)*100;// 62.8 cm approximilty 62 cm 
		  distance=(distance_per_1rotation*((float)no_pulses/360));
		 // RPM=PPS*60*(0.5/360);
		no_pulses=PINA|(PINB<<8);
		lcd_out(1,1,"dis=");
		lcd_out(2,2,convert_data(distance));
		lcd_send_string("cm");
        //TODO:: Please write your application code 
    }
}