/*
 * FND_test.c
 *
 * Created: 2018-09-19 오전 10:41:03
 * Author : kccistc
 */ 


#define F_CPU 16000000L

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void display_FND(uint8_t position, uint8_t number);

uint8_t numbers[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x67};
uint8_t fndselect[] = {0x08, 0x04, 0x02, 0x01};

unsigned int fnd_count = 0;

ISR(TIMER0_OVF_vect)
{
	display_Number(fnd_count);
	
	fnd_count ++;
	
	if(fnd_count == 10000)
	{
		fnd_count = 0;
	}
}

int main(void)
{
	TCCR0 |= (1 << CS02 | 1 << CS01 | 1 << CS00);
	TIMSK = 1 << TOIE0;
	sei();
	
	DDRF = 0xff;
	DDRG = 0xff;
	
	PORTG = 0x00;
	
	while (1)
	{
		_delay_ms(100);
		_delay_ms(100);
	}
}

void display_FND(uint8_t position, uint8_t number)
{
	PORTG = PORTG | 0x0f;
	PORTG &= ~fndselect[position];
	PORTF = numbers[number];
}

void display_Number(unsigned int fnd_count1)
{
	display_FND(0,fnd_count1 % 10);
	_delay_ms(1);
	display_FND(1,(fnd_count1 % 100) /10);
	_delay_ms(1);
	display_FND(2,(fnd_count1 % 1000) / 100);
	_delay_ms(1);
	display_FND(3,fnd_count1/1000);
	_delay_ms(1);
}
