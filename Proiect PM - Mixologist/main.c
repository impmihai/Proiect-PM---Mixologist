/*
 * Proiect PM - Mixologist.c
 *
 * Created: 4/23/2019 9:02:00 PM
 * Author : mihai
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Stepper.h"
#include "AnalogWrite.h"

void setup_timer1() {
	TCCR1A |= (1 << WGM11);
	TCCR1A |= (1 << COM1B1);
	TCCR1B |= (1 << WGM13) | (1 << WGM12);
	TCCR1B |= (1 << CS10) | (1 << CS11);
	ICR1 = 4999; 
}


#define delay 50


int main(void)
{
	//count = 0;
	//setup_timer1();
	//setup_timer2();
	
	setup_stepper(100);
	DDRB = 0xFF;
	DDRD = 0xFF;
	PORTB = 0x00;
	
	//initAnalogWrite();
	stepper_move(100);
	int i, j, k;
    while (1) 
    {
		//for (i = 0; i < 800; i++) {
			//OCR1B = i;
			//_delay_ms(10);
		//}
		//OCR1B = 130;	/* set servo shaft at -90° position */
		//_delay_ms(500);
		//OCR1B = 350;	/* set servo shaft at 0° position */
		//_delay_ms(2500);
		//OCR1B = 600;	/* set servo at +90° position */
		//_delay_ms(2500);
		
//
		//for (i = 0; i < 255; i++) {
			//analogWrite(i);
			//_delay_ms(2);
			//
		//}
		
		/* main loop here */
		//PORTB |= 0b00000001;
		//_delay_ms(delay);
		//PORTB &= 0b00000000;
		//
		//PORTB |= 0b00000100;
		//_delay_ms(delay);
		//PORTB &= 0b00000000;
		//
		//
		//PORTB |= 0b00000010;
		//_delay_ms(delay);
		//PORTB &= 0b00000000;
		//
		//PORTB |= 0b00001000;
		//_delay_ms(delay);
		//PORTB &= 0b00000010;
		
		//_delay_ms(delay);
		
		//OCR1A = 3999 + offset;
//
		//_delay_ms(5000);
//
		//OCR1A = 1999 - offset;
//
		//_delay_ms(5000);
    }
}

