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
#include "OrderReader.h"
#include "AnalogWrite.h"

typedef struct command {
	uint8_t type;
	uint32_t amount;
	uint32_t delay_ms;
} command;

typedef struct rgb_color {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} rgb_color;

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
	STATE_PAUSE,
};	

enum COMMAND_TYPE {
	COMMAND_MOVE,
	COMMAND_DISPENSE,
	COMMAND_WAIT,
};



int positions[6] = {0, 1100, 2400, 3600, 4850, 6000 };
#define DRINK_JAGGER positions[0]
#define DRINK_GIN positions[1]
#define DRINK_MONA positions[2]
#define DRINK_ROM positions[3]
#define DRINK_COLA positions[4]
#define DRINK_SCHWEEPS positions[5]
#define FINISHED_MOVE 3000
command drinks[11][16];

int current_receipe;
int number_of_dispenses[11] = {0, 5, 7, 5, 7, 5, 7, 5, 7, 6 };
void init_drinks() {
	// JAGGER AND COLA
	drinks[1][0].amount = DRINK_JAGGER;
	drinks[1][0].type = COMMAND_MOVE;
	
	drinks[1][1].amount = 11000;
	drinks[1][1].type = COMMAND_DISPENSE;
	
	drinks[1][2].amount = DRINK_COLA;
	drinks[1][2].type = COMMAND_MOVE;
	
	drinks[1][3].amount = 11000;
	drinks[1][3].type = COMMAND_DISPENSE;
	
	drinks[1][4].amount = FINISHED_MOVE;
	drinks[1][4].type = COMMAND_MOVE;
	
	
	// JAGGER AND DOUBLE COLA
	drinks[2][0].amount = DRINK_JAGGER;
	drinks[2][0].type = COMMAND_MOVE;
	
	drinks[2][1].amount = 11000;
	drinks[2][1].type = COMMAND_DISPENSE;
	
	drinks[2][2].amount = DRINK_COLA;
	drinks[2][2].type = COMMAND_MOVE;
	
	drinks[2][3].amount = 11000;
	drinks[2][3].type = COMMAND_DISPENSE;
	
	drinks[2][4].amount = DRINK_COLA;
	drinks[2][4].type = COMMAND_WAIT;
	
	drinks[2][5].amount = 11000;
	drinks[2][5].type = COMMAND_DISPENSE;
	
	drinks[2][6].amount = FINISHED_MOVE;
	drinks[2][6].type = COMMAND_MOVE;
	
	
	// RUM + COLA
	drinks[3][0].amount = DRINK_ROM;
	drinks[3][0].type = COMMAND_MOVE;
	
	drinks[3][1].amount = 11000;
	drinks[3][1].type = COMMAND_DISPENSE;
	
	drinks[3][2].amount = DRINK_COLA;
	drinks[3][2].type = COMMAND_MOVE;
	
	drinks[3][3].amount = 11000;
	drinks[3][3].type = COMMAND_DISPENSE;
	
	drinks[3][4].amount = FINISHED_MOVE;
	drinks[3][4].type = COMMAND_MOVE;
	
	// ROM AND DOUBLE COLA
	drinks[4][0].amount = DRINK_ROM;
	drinks[4][0].type = COMMAND_MOVE;
	
	drinks[4][1].amount = 11000;
	drinks[4][1].type = COMMAND_DISPENSE;
	
	drinks[4][2].amount = DRINK_COLA;
	drinks[4][2].type = COMMAND_MOVE;
	
	drinks[4][3].amount = 11000;
	drinks[4][3].type = COMMAND_DISPENSE;
	
	drinks[4][4].amount = DRINK_COLA;
	drinks[2][4].type = COMMAND_WAIT;
	
	drinks[4][5].amount = 11000;
	drinks[4][5].type = COMMAND_DISPENSE;
	
	drinks[4][6].amount = FINISHED_MOVE;
	drinks[4][6].type = COMMAND_MOVE;
	
	// MONA + TONIC
	drinks[5][0].amount = DRINK_MONA;
	drinks[5][0].type = COMMAND_MOVE;
	
	drinks[5][1].amount = 11000;
	drinks[5][1].type = COMMAND_DISPENSE;
	
	drinks[5][2].amount = DRINK_SCHWEEPS;
	drinks[5][2].type = COMMAND_MOVE;
	
	drinks[5][3].amount = 11000;
	drinks[5][3].type = COMMAND_DISPENSE;
	
	drinks[5][4].amount = FINISHED_MOVE;
	drinks[5][4].type = COMMAND_MOVE;
	
	
	// MONA AND DOUBLE TONIC
	drinks[6][0].amount = DRINK_MONA;
	drinks[6][0].type = COMMAND_MOVE;
	
	drinks[6][1].amount = 11000;
	drinks[6][1].type = COMMAND_DISPENSE;
	
	drinks[6][2].amount = DRINK_SCHWEEPS;
	drinks[6][2].type = COMMAND_MOVE;
	
	drinks[6][3].amount = 11000;
	drinks[6][3].type = COMMAND_DISPENSE;
	
	drinks[6][4].amount = DRINK_SCHWEEPS;
	drinks[2][4].type = COMMAND_WAIT;
	
	drinks[6][5].amount = 11000;
	drinks[6][5].type = COMMAND_DISPENSE;
	
	drinks[6][6].amount = FINISHED_MOVE;
	drinks[6][6].type = COMMAND_MOVE;
	
	
	// Gin + TONIC
	drinks[7][0].amount = DRINK_GIN;
	drinks[7][0].type = COMMAND_MOVE;
	
	drinks[7][1].amount = 11000;
	drinks[7][1].type = COMMAND_DISPENSE;
	
	drinks[7][2].amount = DRINK_SCHWEEPS;
	drinks[7][2].type = COMMAND_MOVE;
	
	drinks[7][3].amount = 11000;
	drinks[7][3].type = COMMAND_DISPENSE;
	
	drinks[7][4].amount = FINISHED_MOVE;
	drinks[7][4].type = COMMAND_MOVE;
	
	
	// GIN AND DOUBLE TONIC
	drinks[8][0].amount = DRINK_GIN;
	drinks[8][0].type = COMMAND_MOVE;
	
	drinks[8][1].amount = 11000;
	drinks[8][1].type = COMMAND_DISPENSE;
	
	drinks[8][2].amount = DRINK_SCHWEEPS;
	drinks[8][2].type = COMMAND_MOVE;
	
	drinks[8][3].amount = 11000;
	drinks[8][3].type = COMMAND_DISPENSE;
	
	drinks[8][4].amount = DRINK_SCHWEEPS;
	drinks[2][4].type = COMMAND_WAIT;
	
	drinks[8][5].amount = 11000;
	drinks[8][5].type = COMMAND_DISPENSE;
	
	drinks[8][6].amount = FINISHED_MOVE;
	drinks[8][6].type = COMMAND_MOVE;
	
	// ROM + MONA + TONIC
	drinks[9][0].amount = DRINK_ROM;
	drinks[9][0].type = COMMAND_MOVE;
	
	drinks[9][1].amount = 11000;
	drinks[9][1].type = COMMAND_DISPENSE;
	
	drinks[9][2].amount = DRINK_MONA;
	drinks[9][2].type = COMMAND_MOVE;
	
	drinks[9][3].amount = 11000;
	drinks[9][3].type = COMMAND_DISPENSE;
	
	drinks[9][4].amount = DRINK_SCHWEEPS;
	drinks[9][4].type = COMMAND_MOVE;
	
	drinks[9][5].amount = FINISHED_MOVE;
	drinks[9][5].type = COMMAND_MOVE;
	
}

int main(void)
{
	int STATE = STATE_WAITING;
	int known_home_glass = 0;
	setup_steppers();
	
	setup_stepper_glass(3);
	set_position_glass(15000);
	stepper_move_glass(15000);
	
	setup_stepper_disp(2);
	set_position_disp(0);
	stepper_move_disp(0);
	
	initAnalogWrite();
	init_orderer();
	init_drinks();

	rgb_color p;
	p.r = 0;
	p.g = 0;
	p.b = 255;
	//
	uint8_t current_command = 0;
	uint8_t max_command = 0;
	
	//analogWrite(p.r, p.g, p.b);
		DDRD |= (1 << PD7);
		//DDRB = 0xFF;
	sei();
    while (1) 
    {
			PORTD &= ~0b10000000;
					if (STATE != STATE_POURING) {
						if (p.r > 0 && p.b == 0) {
							p.r--;
							p.g++;
						}
						if (p.g > 0 && p.r == 0) {
							p.g--;
							p.b++;
						}
						if (p.b > 0 && p.g == 0) {
							p.r++;
							p.b--;
						}
						_delay_us(200);
					
					}
					
					//rgbColour[0] = 255;
					//rgbColour[1] = 255;
					//rgbColour[2] = 255;
					
					analogWrite(p.r, p.g, p.b);
		if (STATE == STATE_WAITING) {
			if (!known_home_glass) {
				STATE = STATE_HOMING;
				stepper_move_glass(0);
				stepper_move_disp(0);
			} else {
				if (current_receipe == 0) {
					uint8_t data = get_orderer_data();
					if (data) {
						current_command = 0;
						current_receipe = data;
						max_command = number_of_dispenses[data];
						PORTD |= (1 << PD7);
					}
				} else {
					if (current_command != max_command) {
						if (drinks[current_receipe][current_command].type == COMMAND_MOVE) {
							STATE = STATE_MOVING_GLASS;
							stepper_move_glass(drinks[current_receipe][current_command].amount);
						} else if (drinks[current_receipe][current_command].type == COMMAND_DISPENSE) {
							STATE = STATE_POURING;
							p.r = 255;
							p.g = 0;
							p.b = 0;
							analogWrite(p.r, p.g, p.b);					
							stepper_move_disp(drinks[current_receipe][current_command].amount);
						} else if (drinks[current_receipe][current_command].type == COMMAND_WAIT) {
							STATE = STATE_PAUSE;
						}
						current_command ++;
					} else {
						current_receipe = 0;
					}
				}
			}
		} else if (STATE == STATE_HOMING) {
			PORTD |= (1 << PD7);
			if (!is_moving_glass()) {
				known_home_glass = 1;
				STATE = STATE_WAITING;
			}
		} else if (STATE == STATE_MOVING_GLASS) {
			if (!is_moving_glass()) {
				STATE = STATE_WAITING;
			}
		} else if (STATE == STATE_POURING) {
			if (!is_moving_disp()) {
				if (get_position_disp() > 0) {
					_delay_ms(2500);
					stepper_move_disp(0);
				} else {
					STATE = STATE_WAITING;	
				}
			}
		} else if( STATE == STATE_PAUSE) {
			_delay_ms(2000);
			STATE = STATE_WAITING;
		}
    }
}



