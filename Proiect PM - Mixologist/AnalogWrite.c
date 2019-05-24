/*
 * CFile1.c
 *
 * Created: 4/23/2019 9:19:37 PM
 *  Author: mihai
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "AnalogWrite.h"

volatile uint8_t pinR_pwm;
volatile uint8_t pinG_pwm;
volatile uint8_t pinB_pwm;
volatile uint8_t pinMotor_pwm;
volatile uint8_t count;

ISR(TIMER2_COMPA_vect) {
	count += 1;
	if (count == 0) {
		//PORTB &=
		//PORTD &= ~(1 << PD7);
		PORTC &= ~((1 << PC0) | (1 << PC1) | (1 << PC2));
	}
	
	if (count == pinR_pwm) {
		//PORTD |= (1 << PD71);
		PORTC |= (1 << PC0);
	}
	
	if (count == pinG_pwm) {
		PORTC |= (1 << PC1);
	}
	
	if (count == pinB_pwm) {
		PORTC |= (1 << PC2);
	}
}



void initAnalogWrite() {
	TCCR2B |= (1<<CS20) ;   //clock select is divided by 64.
	TCCR2A |= (1<<WGM21);              //sets mode to CTC
	OCR2A = 0x7C;                      //sets TOP to 124 so the timer will overflow every 0.5 ms.
	TIMSK2 |= (1<<OCIE2A);              //Output Compare Match A Interrupt Enable
	sei();
	
	//PORTD |= (1 << PD7);
	DDRC |= (1 << PC0) | (1 << PC1) | (1 << PC2);
}

void analogWrite(int r, int g, int b) {
	pinR_pwm = 255 - r;
	pinG_pwm = 255 - g;
	pinB_pwm = 255 -  b;
}