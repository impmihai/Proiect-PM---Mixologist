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

volatile int ticks_for_step_glass = 100;
volatile int ticks_glass = 0;

volatile int ticks_for_step_disp = 100;
volatile int ticks_disp = 0;

volatile int current_position_glass = 0;
volatile int target_position_glass = 0;

volatile int current_position_disp = 0;
volatile int target_position_disp = 0;

// The code for the motor that moves the glass around.


ISR(TIMER0_COMPA_vect) {
	ticks_glass ++;
	if (ticks_glass == ticks_for_step_glass) {
		ticks_glass = 0;
	}
	
	if (ticks_glass == 0) {
		if (current_position_glass < target_position_glass) {
			STEPPER_GLASS_PORT &= ~(1 << STEPPER_GLASS_ENABLED_PIN);
			STEPPER_GLASS_PORT ^= (1 << STEPPER_GLASS_STEP_PIN);
			STEPPER_GLASS_PORT |= (1 << STEPPER_GLASS_DIRECTION_PIN);
			current_position_glass += 1;
		} else if (current_position_glass > target_position_glass) {
			STEPPER_GLASS_PORT &= ~(1 << STEPPER_GLASS_ENABLED_PIN);
			STEPPER_GLASS_PORT ^= (1 << STEPPER_GLASS_STEP_PIN);
			STEPPER_GLASS_PORT &= ~(1 << STEPPER_GLASS_DIRECTION_PIN);
			current_position_glass -= 1;
		} else {
			STEPPER_GLASS_PORT |= (1 << STEPPER_GLASS_ENABLED_PIN);
		}
	}
	
	
	ticks_disp ++;
	if (ticks_disp == ticks_for_step_disp) {
		ticks_disp = 0;
	}
	
	if (ticks_disp == 0) {
		if (current_position_disp < target_position_disp) {
			STEPPER_DISP_PORT &= ~(1 << STEPPER_DISP_ENABLED_PIN);
			STEPPER_DISP_PORT ^= (1 << STEPPER_DISP_STEP_PIN);
			STEPPER_DISP_PORT |= (1 << STEPPER_DISP_DIRECTION_PIN);
			current_position_disp += 1;
		} else if (current_position_disp > target_position_disp) {
			STEPPER_DISP_PORT &= ~(1 << STEPPER_DISP_ENABLED_PIN);
			STEPPER_DISP_PORT ^= (1 << STEPPER_DISP_STEP_PIN);
			STEPPER_DISP_PORT &= ~(1 << STEPPER_DISP_DIRECTION_PIN);
			current_position_disp -= 1;
		} else {
			STEPPER_DISP_PORT |= (1 << STEPPER_DISP_ENABLED_PIN);
		}
	}
}

//
ISR (PCINT1_vect)
{
	if ((PINB & (1 << PB3)) == 0) { // HOMNG PAHAR
		current_position_glass = 0;
	}
}

ISR (PCINT2_vect) {
	if ((PINC & (1 << PC7)) == 0) { // HOMING DISPENSER
		current_position_disp = 0;
		PORTD ^= (1 << PD7);
	}
}
void setup_steppers() {
	TCCR0A |= (1 << WGM01); // Set mode to CTC;
	TCCR0B |= (1 << CS00) | (1 << CS02); // prescalar 1024
	OCR0A = 3; // perioada de ~ 1ms
	TIMSK0 |= (1 << OCIE0A); // activate interrupt
	
	// ACTIVARE ENDPOINT. MODIFICA AICI DACA SCHIMBI PINUL.
	
	PORTC &= ~(1 << PC7);
	PORTB &= ~(1 << PB3);
	
	DDRC |= 1 << PC7;
	DDRB |= 1 << PB3;
	
	PCICR |= (1 << PCIE1) | (1 << PCIE2);
	
	PCMSK2 |= (1 << PCINT23);
	PCMSK1 |= (1 << PCINT11);
	
	sei();
}

void setup_stepper_glass(int ms_for_a_step) {
	set_speed_glass(ms_for_a_step);
	STEPPER_GLASS_DDR |= (1 << STEPPER_GLASS_STEP_PIN) | (1 << STEPPER_GLASS_ENABLED_PIN) | (1 << STEPPER_GLASS_DIRECTION_PIN);
}

void setup_stepper_disp(int ms_for_a_step) {
	set_speed_disp(ms_for_a_step);
	STEPPER_DISP_DDR |= (1 << STEPPER_DISP_STEP_PIN) | (1 << STEPPER_DISP_ENABLED_PIN) | (1 << STEPPER_DISP_DIRECTION_PIN);
}

void set_speed_glass(uint8_t ms_for_a_step) {
	ticks_for_step_glass = ms_for_a_step;
}

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



void set_speed_disp(uint8_t ms_for_a_step) {
	ticks_for_step_disp = ms_for_a_step;
}

void set_position_disp(int step) {
	current_position_disp  = step;
}

uint8_t is_moving_disp() {
	return current_position_disp != target_position_disp;
}

int get_position_disp() {
	return current_position_disp;
}

void stepper_move_disp(int step) {
	target_position_disp = step;
}