/*
 * Proiect PM - Mixologist.c
 *
 * Created: 4/23/2019 9:02:00 PM
 * Author : mihai
 */ 
#define F_CPU 8000000UL

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

enum STATES {
	STATE_WAITING,
	STATE_HOMING,
	STATE_MOVING_GLASS,
	STATE_POURING,
};	

int main(void)
{
	DDRD = 0b10000000;
	int STATE = 0;
	int known_home_glass = 0;
	setup_stepper_glass(150);
	set_position_glass(15000);
	stepper_move_glass(15000);
	
	//initAnalogWrite();
	int i, j, k;
	unsigned int rgbColour[3];
	  // Start off with red.
	  rgbColour[0] = 255;
	  rgbColour[1] = 0;
	  rgbColour[2] = 0;
	
	sei();
	int pas = 0;
    while (1) 
    {
		PORTD &= ~0b10000000;
		if (STATE == STATE_WAITING) {
			PORTD |= 0b10000000;
		
			if (!known_home_glass) {
				STATE = STATE_HOMING;
				stepper_move_glass(0);
			} else {
				if (get_position_glass() < 300)
					stepper_move_glass(300);
			}
		} else if (STATE == STATE_HOMING) {
			if (!is_moving_glass()) {
				known_home_glass = 1;
				STATE = STATE_WAITING;
			}
		} else if (STATE == STATE_MOVING_GLASS) {
			if (!is_moving_glass()) {
				STATE = STATE_POURING;
			}
		} else if (STATE == STATE_POURING) {
			// EMPTY
			STATE = STATE_WAITING;
		}
		
		//if (pas == 0) {
			//if (!is_moving_1()) {
				//stepper_move_1(-100);
				//pas = 1;
			//}
			//
		//} else if (pas == 1) {
			//if (!is_moving_1()) {
				//stepper_move_1(0);
				//pas = 0;
			//}
			//
		//}
		
		
    }
}

