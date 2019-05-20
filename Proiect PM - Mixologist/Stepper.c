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

volatile int steps_per_second_glass = 100;

volatile int current_position_glass = 0;
volatile int target_position_glass = 0;

// The code for the motor that moves the glass around.

ISR(TIMER0_COMPA_vect) {
	if (current_position_glass < target_position_glass) {
		STEPPER_GLASS_PORT ^= (1 << STEPPER_GLASS_STEP_PIN);
		STEPPER_GLASS_PORT |= (1 << STEPPER_GLASS_DIRECTION_PIN);
		current_position_glass += 1;
	} else if (current_position_glass > target_position_glass) {
		STEPPER_GLASS_PORT ^= (1 << STEPPER_GLASS_STEP_PIN);
		STEPPER_GLASS_PORT &= ~(1 << STEPPER_GLASS_DIRECTION_PIN);
			current_position_glass -= 1;
	}
}

//
ISR (PCINT1_vect)
{
	if ((PINB & (1 << PB3)) == 0) { // HOMNG PAHAR
		current_position_glass = 0;
		PORTD ^= 1 << PD7;	
	} else if ((PINB & (1 << PB4)) == 0) {
		PORTD ^= 1 << PD7;
	}
}

void setup_stepper_glass(int stepsPerSecond) {
	TCCR0A |= (1 << WGM01); // Set mode to CTC;
	TCCR0B |= (1 << CS00) | (1 << CS02); // prescaler 1024
	TIMSK0 |= (1 << OCIE0A); // activate interrupt
	set_speed_glass(stepsPerSecond);
	STEPPER_GLASS_DDR |= (1 << STEPPER_GLASS_STEP_PIN) | (1 << STEPPER_GLASS_ENABLED_PIN) | (1 << STEPPER_GLASS_DIRECTION_PIN);
	
	// ACTIVARE ENDPOINT. MODIFICA AICI DACA SCHIMBI PINUL.
	
	PORTB &= ~(1 << PB4);
	PORTB &= ~(1 << PB3);
	
	DDRB |= 1 << PB4;
	DDRB |= 1 << PB3;
	
	PCICR |= (1 << PCIE1);
	
	PCMSK1 |= (1 << PCINT12);
	PCMSK1 |= (1 << PCINT11);
	
	sei();
}

void set_speed_glass(uint8_t stepsPerSecond) {
	steps_per_second_glass = stepsPerSecond;
	OCR0A = COUNT_TO;
}

//volatile int remaining_move = 0;
volatile int position;

void set_position_glass(int step) {
	current_position_glass  = step;
}
 
uint8_t is_moving_glass() {
	return current_position_glass != target_position_glass;	
}

int get_position_glass() {
	return current_position_glass;
}

void stepper_move_glass(int step) {
	target_position_glass = step;
}