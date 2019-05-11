/*
 * CFile1.c
 *
 * Created: 4/23/2019 9:19:37 PM
 *  Author: mihai
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "AnalogWrite.h"

volatile uint8_t pinR_pwm;
volatile uint8_t pinG_pwm;
volatile uint8_t pinB_pwm;
volatile uint8_t pinMotor_pwm;
volatile uint8_t count;

//ISR(TIMER2_OVF_vect) {
//PORTD &= 0x00;
//}
//
ISR(TIMER2_COMPA_vect) {
	count += 1;
	if (count == 0) {
		//PORTB &=
		PORTD &= ~0b11110000;
	}
	
	if (count == pinR_pwm) {
		PORTD |= 0b10000000;
	}
	
	if (count == pinG_pwm) {
		PORTD |= 0b01000000;
	}
	
	if (count == pinB_pwm) {
		PORTD |= 0b00100000;
	}
	
	if (count == pinB_pwm) {
		PORTD |= 0b00010000;
	}
}



void initAnalogWrite() {
	TCCR2B |= (1<<CS20) ;   //clock select is divided by 64.
	TCCR2A |= (1<<WGM21);              //sets mode to CTC
	OCR2A = 0x7C;                      //sets TOP to 124 so the timer will overflow every 0.5 ms.
	TIMSK2 |= (1<<OCIE2A);              //Output Compare Match A Interrupt Enable
	sei();
}

void analogWrite(int duty) {
	pinR_pwm = duty;
	pinG_pwm = duty;
	pinB_pwm = duty;
}