/*
 * OrderReader.c
 *
 * Created: 5/24/2019 6:08:14 AM
 *  Author: mihai
 */ 


#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "OrderReader.h"

volatile int is_data = 0;
volatile int data = 0;

ISR(PCINT3_vect) {
	is_data = 1;
	data = ((ORDER_PIN & (1 << ORDER_BIT_1)) != 0) + ((ORDER_PIN & (1 << ORDER_BIT_2)) != 0) * 2 + ((ORDER_PIN & (1 << ORDER_BIT_3)) != 0) * 4 + ((ORDER_PIN & (1 << ORDER_BIT_4))  != 0) * 8;
	PORTD ^= (1 << PD7);
}

void init_orderer() {
	ORDER_DDR &= ~((1 << ORDER_BIT_CLK) | (1 << ORDER_BIT_1) | (1 << ORDER_BIT_2) | (1 << ORDER_BIT_3) | (1 << ORDER_BIT_4));
	ORDER_PORT |= (1 << ORDER_BIT_CLK) | (1 << ORDER_BIT_1) | (1 << ORDER_BIT_2) | (1 << ORDER_BIT_3) | (1 << ORDER_BIT_4);
	
	PCICR |= (1 << PCIE3);
	PCMSK3 |= (1 << PCINT28);
}

uint8_t get_orderer_data() {
	if (is_data == 0) {
		return 0;
	} else {
		is_data = 0;
		return data;
	}
}
