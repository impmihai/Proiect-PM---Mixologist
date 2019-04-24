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

volatile uint8_t pinR_pwm;
volatile uint8_t pinG_pwm;
volatile uint8_t pinB_pwm;
volatile uint8_t pinMotor_pwm;
volatile uint8_t count;

ISR(TIMER2_OVF_vect) {
	PORTD &= 0x00;
}

ISR(TIMER2_COMPA_vect) {
	count += 1;
	if (count == 0) {
		//PORTB &=
		PORTB &= ~0b11110000; 
	}
	
	if (count == pinR_pwm) {
		PORTB |= 0b10000000;
	} 
	
	if (count == pinG_pwm) {
		PORTB |= 0b01000000;
	}
	
	if (count == pinB_pwm) {
		PORTB |= 0b00100000;
	}
	
	if (count == pinB_pwm) {
		PORTB |= 0b00010000;
	}
}

void setup_timer2() {
	TCCR2B |= (1<<CS20) ;   //clock select is divided by 64.
	TCCR2A |= (1<<WGM21);              //sets mode to CTC
	OCR2A = 0x7C;                      //sets TOP to 124 so the timer will overflow every 0.5 ms.
	TIMSK2 |= (1<<OCIE2A);              //Output Compare Match A Interrupt Enable
	sei();
}

int state = 0;

int main(void)
{
	count = 0;
	//setup_timer2();
	DDRB = 0xFF;
	DDRD = 0xFF;
	
	int i = 0;
	int j = 0;
	int k = 0;
	
	TCCR1A |= (1 << WGM11) | (1 << COM1A1);
	TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS11);
	ICR1 = 39999;
	int offset = 800;
    while (1) 
    {
		//for (i = 0; i < 255; i++) {
			//pinR_pwm = i;
			//pinG_pwm = 255 - i;
			//pinB_pwm = 0;
			//_delay_ms(1);
		//}
		//for (i = 0; i < 255; i++) {
			//pinB_pwm = i;
			//pinR_pwm = 255 - i;
			//pinG_pwm = 0;
			//_delay_ms(1);
			//
		//}
		//for (i = 0; i < 255; i++) {
			//pinG_pwm = i;
			//pinB_pwm = 255 - i;
			//pinR_pwm = 0;
			//_delay_ms(1);
			//
		//}
		
		OCR1A = 3999 + offset;

		_delay_ms(5000);

		OCR1A = 1999 - offset;

		_delay_ms(5000);

		 
		//
		//for (i = 0; i < 255; i++) {
			//for (j = 0; j < 255; j++) {
				//for (k = 0; k < 255; k++) {
					//pinR_pwm = i;
					//pinG_pwm = j;
					//pinB_pwm = k;
					//_delay_us(1);
				//}
			//}
		//}
    }
}

