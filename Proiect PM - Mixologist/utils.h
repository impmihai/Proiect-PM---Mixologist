/*
 * utils.h
 *
 * Created: 4/24/2019 3:41:17 AM
 *  Author: mihai
 */ 


#ifndef UTILS_H_
#define UTILS_H_

#define PA0 0;
#define PA1 1;
#define PA2 2;
#define PA3 3;
#define PA4 4;
#define PA5 5;
#define PA6 6;
#define PA7 7;

#define PB0 8;
#define PB1 9;
#define PB2 10;
#define PB3 11;
#define PB4 12;
#define PB5 13;
#define PB6 14;
#define PB7 15;

#define PC0 16;
#define PC1 17;
#define PC2 18;
#define PC3 19;
#define PC4 20;
#define PC5 21;
#define PC6 22;
#define PC7 23;

#define PD0 32;
#define PD1 33;
#define PD2 34;
#define PD3 35;
#define PD4 36;
#define PD5 37;
#define PD6 38;
#define PD7 39;

#define GET_PORT(A) (((A) & (1 << 6)) ? PORTD : (((A) & (1 << 5)) ? PORTC : (((A) & (1 << 4)) ? PORTB : (((A) & (1 << 4)) ? PORTA : NULL))))


#endif /* UTILS_H_ */