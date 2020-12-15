/*
 * UART_AVR.c
 *
 * Created: 6/7/2016 3:10:10 PM
 *  Author: Ahmed
 */ 
#include "AVR_UART.h"

void UART_INIT()
{
UBRRL = (uint8_t)(MYUBRR) ;    //send the low  8 bits of the UBRR
UBRRH = (uint8_t)(MYUBRR>>8);//send the high 4 bits of the UBRR
UCSRB |=((1<<4)|(1<<3));     //Enable transmit and enable RXENn TXENn
UCSRC |= (1<<UCSZ0) | (1<<UCSZ1) | (1<<URSEL);    //Frame with 8 bit data , 1 stop bit, no parity UCSZn1 UCSZn0 , Asynchornous mode 
//UCSRC |=(1<<UPM0)|(1<<UPM1);
}


void UART_Transmit( int data)
{  while( !(UCSRA & (1<<5)) ) ;// wait until the buffer is empty UDREn
	UDR=data;
}

uint8_t UART_Read()
{ while( !(UCSRA & (1<<7)) ) ;//wait until the receiving complete RXCn
	return UDR;
}

void UART_Transmit_string (char * str)
{
	unsigned char i =0 ;
	 while(str[i]!=0)
	    {UART_Transmit(str[i]) ; i++;}
}