/*
 * Stepper.h
 *
 * Created: 4/27/2019 1:13:59 AM
 *  Author: mihai
 */ 


// The code for the motor that moves the glass around.
#ifndef STEPPER_H_
#define STEPPER_H_

#define STEPPER_GLASS_DDR DDRD
#define STEPPER_GLASS_PORT PORTD
#define STEPPER_GLASS_STEP_PIN 4
#define STEPPER_GLASS_DIRECTION_PIN 3
#define STEPPER_GLASS_ENABLED_PIN 2

#define COUNT_TO ((15625 / steps_per_second_glass) - 1);

#define STEPS_PER_MM 3

void setup_stepper_glass(int stepsPerSecond);
void set_speed_glass(uint8_t stepsPerSecond);
void stepper_move_glass(int step);
int get_position_glass();
void set_position_glass(int step);
uint8_t is_moving_glass();

#endif /* STEPPER_H_ */