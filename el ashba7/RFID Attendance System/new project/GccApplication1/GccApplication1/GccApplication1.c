/*
 * GccApplication1.c
 *
 * Created: 4/8/2018 10:51:53 AM
 *  Author: M
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include "macros.h"
#include "AVR_UART.h"
#include "lcd.h"
#include <string.h>
#include <util/delay.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
//char Name[10][20]={"Group 25", "Enas Emad","Baher Mohammed","Bassel Akram","Bassam Hatem","Dina Saad","Karim Akram","Nada Hesham","Nihal Abdelaziz", "Nour Abdelwahab"};
int flag=0,flag1,flag2,i;
int recv;
int x[26];
char*recv_text;
unsigned int cnt1=0,cnt2=0,cnt3=0;
unsigned char attendance=0,abscent=0 ;

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>

#define buffer_size 64



// 
// char buffer[buffer_size];
// uint8_t readpos = 0;
// uint8_t writepos = 0;

// ISR(USART_RXC_vect)
// {
// 	
// 	buffer[writepos] = UDR;
// 	writepos++;
// 	if(writepos>=buffer_size)
// 	{
// 		writepos = 0;
// 		
// 		for(int i=0;i<buffer_size;i++)
// 		buffer[i] = 0;
// 		
// 	}
// }

void intr_init();
void att();
ISR(INT0_vect){
	 att();
// 	attendance=cnt1+cnt2+cnt3;
// 	abscent=3-attendance;
// 	
// 	char*att_text=convertData(attendance);
// 	char*abs_text=convertData(abscent);
// 	lcd_delete();
// 	lcd_out(0,0,"attendance=");
// 	lcd_out(13,0,att_text);
// 		lcd_out(1,1,"abscent=");
// 		lcd_out(9,1,abs_text);
// 		
	cnt1=cnt2=cnt3=attendance=abscent=0;
// 		_delay_ms(1000);

	
}

int main(void)
{
		lcd_init();
		UART_INIT();
		//intr_init();
		lcd_out(3,0,"Welcome..");
		lcd_out(3,1,"CUFE 2021");
		_delay_ms(500);
		LCD_Clear();
		lcd_out(3,0,"RFID Att.");
		lcd_out(4,1,"System..");
		_delay_ms(500);
		LCD_Clear();
	
  
        		
        		lcd_out(0,0,"Insert ID Card..");

  //intr_init();
   
  while (1){
	  lcd_out(0,0,"Insert ID Card..");
int r=UART_Read();
_delay_ms(10);
char*text=convertData(r);
lcd_out(1,1,text);
_delay_ms(10);
r=0;
 if(strcmp(text,"8")==0 && flag==0){flag++;} else if(strcmp(text,"212")==0 && flag==1){flag++;}else if(strcmp(text,"136")==0 && flag==2){flag++;}else if(strcmp(text,"148")==0 && flag==3){flag++;}
 	if(flag==4){lcd_out(1,1,"abd el kder");_delay_ms(10);flag=0; cnt1=1; }
 		
// 			
// 	if(strcmp(text,"40")==0 && flag1==0){flag1++;} else if(strcmp(text,"222")==0 && flag1==1){flag1++;}else if(strcmp(text,"40")==0 && flag1==2){flag1++;}else if(strcmp(text,"222")==0 && flag1==3){flag1++;}
// if(flag1==4){lcd_out(1,1,"sara");_delay_ms(10);flag1=0;cnt2=1;}
// // 	lcd_out(6,1,"c2=");
// // 	lcd_out(10,1,convertData(cnt2));
// 	
// if(strcmp(text,"40")==0 && flag2==0){flag2++;} else if(strcmp(text,"148")==0 && flag2==1){flag2++;}else if(strcmp(text,"40")==0 && flag2==2){flag2++;}else if(strcmp(text,"148")==0 && flag2==3){flag2++;}
// if(flag2==4){lcd_out(1,1,"Reem");_delay_ms(10);flag2=0;cnt3=1;}
// 	lcd_out(11,1,"c3=");
// 	lcd_out(14,1,convertData(cnt3));
	
//_delay_ms(1);
lcd_out(1,1,"                      ");
  
}}



void intr_init(){

	CLR_BIT(DDRD,2);

	SET_BIT(PORTD,2);
	MCUCR |= (1<<1); // falling edge
	GICR |=(1<<6); // enable INT0 set pin6
	SREG |=(1<<7); // set GIE pin7
}
void att(){
	
	if(cnt1==0 && cnt2==0 &&cnt3==0){lcd_out(0,0,"attendace is 0");lcd_out(1,1,"abscent is 3"); _delay_ms(1000);}
		if(cnt1==0 && cnt2==0 &&cnt3==1){lcd_out(0,0,"attendace is 1");lcd_out(1,1,"abscent is 2");_delay_ms(1000);}
			if(cnt1==0 && cnt2==1 &&cnt3==0){lcd_out(0,0,"attendace is 1");lcd_out(1,1,"abscent is 2");_delay_ms(1000);}
				if(cnt1==0 && cnt2==1 &&cnt3==1){lcd_out(0,0,"attendace is 2");lcd_out(1,1,"abscent is 1");_delay_ms(1000);}
				
				if(cnt1==1 && cnt2==0 &&cnt3==0){lcd_out(0,0,"attendace is 1");lcd_out(1,1,"abscent is 2");_delay_ms(1000);}
			if(cnt1==1 && cnt2==0 &&cnt3==1){lcd_out(0,0,"attendace is 2");lcd_out(1,1,"abscent is 1");_delay_ms(1000);}
		if(cnt1==1 && cnt2==1 &&cnt3==0){lcd_out(0,0,"attendace is 2");lcd_out(1,1,"abscent is 1");_delay_ms(1000);_delay_ms(1000);}
	if(cnt1==1&& cnt2==1 &&cnt3==1){lcd_out(0,0,"attendace is 3");lcd_out(1,1,"abscent is 0");_delay_ms(1000);}
		
	
}