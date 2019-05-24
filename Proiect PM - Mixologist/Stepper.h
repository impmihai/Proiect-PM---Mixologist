/*
 * Stepper.h
 *
 * Created: 4/27/2019 1:13:59 AM
 *  Author: mihai
 */ 


// The code for the motor that moves the glass around.
#ifndef STEPPER_H_
#define STEPPER_H_

#define STEPPER_GLASS_DDR DDRC
#define STEPPER_GLASS_PORT PORTC
#define STEPPER_GLASS_DIRECTION_PIN 4
#define STEPPER_GLASS_STEP_PIN 5
#define STEPPER_GLASS_ENABLED_PIN 6

#define STEPPER_DISP_DDR DDRB
#define STEPPER_DISP_PORT PORTB 
#define STEPPER_DISP_DIRECTION_PIN 7
#define STEPPER_DISP_STEP_PIN 6
#define STEPPER_DISP_ENABLED_PIN 5
//
//#define COUNT_TO_GLASS ((15625 / steps_per_second_glass) - 1);
//#define COUNT_TO_CIRCLE ((15625 / steps_per_second_glass) - 1);

#define STEPS_PER_MM 3

void setup_steppers();

void setup_stepper_glass(int ms_for_a_step);
void set_speed_glass(uint8_t ms_for_a_step);
void stepper_move_glass(int step);
int get_position_glass();
void set_position_glass(int step);
uint8_t is_moving_glass();

void setup_stepper_disp(int ms_for_a_step);
void set_speed_disp(uint8_t ms_for_a_step);
void stepper_move_disp(int step);
int get_position_disp();
void set_position_disp(int step);
uint8_t is_moving_disp();

#endif /* STEPPER_H_ */