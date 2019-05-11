/*
 * Stepper.c
 *
 * Created: 4/27/2019 1:13:45 AM
 *  Author: mihai
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "Stepper.h"

volatile int steps_per_second = 100;


// current step relative to a 1/4 progression
volatile int8_t current_step = 0;

// current position in steps (one step is a 4 power cycle)
volatile int current_position = 0;

// remaining moving in steps (one step is a 4 power cycle)
volatile int remaining_move = 0;

ISR(TIMER0_COMPA_vect) {
	if (remaining_move > 0) { // move positive;
		current_step += 1;
		if (current_step == 4) {
			current_step = 0;
		}
		
		if (current_step == 0) {
			ZERO_STEPPER;
			SET_STEP1;
			} else if (current_step == 1) {
			ZERO_STEPPER;
			SET_STEP2;
			} else if (current_step == 2) {
			ZERO_STEPPER;
			SET_STEP3;
			} else if (current_step == 3) {
			ZERO_STEPPER;
			SET_STEP4;
			current_position += 1;
			remaining_move -= 1;
		}
	} else if(remaining_move < 0) { // move negative;
		current_step -= 1;
		if (current_step == -1) {
			current_step = 3;
		}
		
		if (current_step == 0) {
			ZERO_STEPPER;
			SET_STEP1;
			} else if (current_step == 1) {
			ZERO_STEPPER;
			SET_STEP2;
			} else if (current_step == 2) {
			ZERO_STEPPER;
			SET_STEP3;
			} else if (current_step == 3) {
			ZERO_STEPPER;
			SET_STEP4;
			current_position -= 1;
			remaining_move += 1;
		}
	} else {
		ZERO_STEPPER;
	}
}

void setup_stepper(int stepsPerSecond) {
	TCCR0A |= (1 << WGM01); // Set mode to CTC;
	TCCR0B |= (1 << CS00) | (1 << CS02); // prescaler 1024
	TIMSK0 |= (1 << OCIE0A); // activate interrupt
	set_speed(stepsPerSecond);
	sei();
}

void set_speed(uint8_t stepsPerSecond) {
	steps_per_second = stepsPerSecond;
	OCR0A = COUNT_TO;
}

//volatile int remaining_move = 0;
volatile int position;

void set_position(int milimeters) {
	remaining_move  = milimeters;
}

uint8_t is_moving() {
	return remaining_move == 0;	
}

int get_position() {
	return current_position;
}

void stepper_move(int milimeters) {
	remaining_move = milimeters;
}