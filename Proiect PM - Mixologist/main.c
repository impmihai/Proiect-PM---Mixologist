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

volatile uint8_t tot_overflow;

//
//ISR (TIMER0_OVF_vect)    // Timer1 ISR
//{
	//PORTD ^= 0b10000000;
//}

//ISR(TIMER1_OVF_vect)
//{
	//// keep a track of number of overflows
	//tot_overflow++;
	//
	//// check for number of overflows here itself
	//// 61 overflows = 2 seconds delay (approx.)
	//if (tot_overflow >= 61) // NOTE: '>=' used instead of '=='
	//{
		//PORTD ^= (1 << 7);  // toggles the led
		//// no timer reset required here as the timer
		//// is reset every time it overflows
		//
		//tot_overflow = 0;   // reset overflow counter
	//}
//}

//void timer1_init()
//{
	//// set up timer with prescaler = 8
	//TCCR1B |= (1 << CS11);
	//
	//// initialize counter
	//TCNT1 = 0;
	//
	//// enable overflow interrupt
	//TIMSK1 |= (1 << TOIE1);
	//
	//// enable global interrupts
	//sei();
	//
	//// initialize overflow counter variable
	//tot_overflow = 0;
//}

ISR(TIMER0_COMPB_vect) {
	// clear the output pin on OCR0 match
	PORTD &= 0b00000000;
}

volatile uint8_t counter;
volatile uint8_t pin_pwm;
ISR(TIMER0_COMPA_vect) {
	// clear the output pin on OCR0 match
	if (counter == pin_pwm) {
		PORTB ^= 0b11111111;
	}
	counter++;
}

ISR(TIMER0_OVF_vect) {
	// set the output pin at timer overflow
	PORTD |= 0b11111111;
	PORTB &= 0b00000000;
}

int main(void)
{

	DDRD = 0b10000000;
	DDRB = 0b11111111;
	TCCR0A |= 1 << WGM00 | 1 << WGM01;
	TCCR0B |= 1 << CS00;
	OCR0B = 0;
	counter = 0;
	TIMSK0 |= ((1 << OCIE0B) | (1 << OCIE0A) | (1 << TOIE0)); // use both interrupts
	sei();
	//TCCR1A |= (1 << COM0A1); // Enable output pe timer.
	//TCCR1A |= (1 << WGM00) | (1 << WGM01);
	//TCCR1B |= (1 << WGM02) | (1 << CS11);
	//OCR0A = 255;
    /* Replace with your application code */
	//timer1_init();
    while (1) 
    {
		int i = 0;
		for (i = 0; i < 255; i++) {
			OCR0B = i;
			pin_pwm = i;
	
			_delay_ms(2);
		}
		//PORTD = 0b10000000;
		//_delay_ms(500);
		//PORTD = 0b00000000;
		//_delay_ms(500);
    }
}

