/*
 * Stepper.h
 *
 * Created: 4/27/2019 1:13:59 AM
 *  Author: mihai
 */ 


#ifndef STEPPER_H_
#define STEPPER_H_

#define STEPPER_PORT PORTB
#define STEPPER_FIRST_PIN 0


#define ZERO_STEPPER (STEPPER_PORT &= ~((0b00001111) << STEPPER_FIRST_PIN))
#define SET_STEP1 (STEPPER_PORT |= (0b00000001) << STEPPER_FIRST_PIN)
#define SET_STEP2 (STEPPER_PORT |= (0b00000100) << STEPPER_FIRST_PIN)
#define SET_STEP3 (STEPPER_PORT |= (0b00000010) << STEPPER_FIRST_PIN)
#define SET_STEP4 (STEPPER_PORT |= (0b00001000) << STEPPER_FIRST_PIN)

#define DELAY_BETWEEN_STEPS (1000 / steps_per_second)
#define STEPS_FREQUENCY (1000 / DELAY_BETWEEN_STEPS)
#define COUNT_TO (15625 / STEPS_FREQUENCY)

#define STEPS_PER_MM 3

void setup_stepper(int stepsPerSecond);
void set_speed(uint8_t stepsPerSecond);
void stepper_move(int milimeters);
int get_position();
uint8_t is_moving();

#endif /* STEPPER_H_ */