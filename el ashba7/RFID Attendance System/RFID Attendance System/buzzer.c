#include <avr/io.h>
#include <util/delay.h>

void buzzer_on()
{
	PORTA = 0xff;
	_delay_ms(500);
	PORTA = 0x00;
	_delay_ms(500);
}
