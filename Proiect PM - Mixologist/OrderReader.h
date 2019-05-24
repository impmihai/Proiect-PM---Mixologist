/*
 * OrderReader.h
 *
 * Created: 5/24/2019 6:08:03 AM
 *  Author: mihai
 */ 


#ifndef ORDERREADER_H_
#define ORDERREADER_H_

#define ORDER_DDR DDRD
#define ORDER_PORT PORTD
#define ORDER_PIN PIND

#define ORDER_BIT_1 PD0
#define ORDER_BIT_2 PD1
#define ORDER_BIT_3 PD2
#define ORDER_BIT_4 PD3
#define ORDER_BIT_CLK PD4


uint8_t data_available();
void init_orderer();
uint8_t get_orderer_data();

#endif /* ORDERREADER_H_ */