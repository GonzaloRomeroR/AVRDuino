#ifndef CORE
#define CORE
#include <avr/io.h>
int pinout[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
int pinD[] = {0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5};

// int pinout[] = {DDD0, DDD1, DDD2, DDD3, DDD4, DDD5, DDD6,
//                 DDD7, DDB0, DDB1, DDB2, DDB3, DDB4, DDB5};
//
// int pinD[] = {PORTD0, PORTD1, PORTD2, PORTD3, PORTD4, PORTD5, PORTD6,
//               PORTD7, PORTB0, PORTB1, PORTB2, PORTB3, PORTB4, PORTB5};

// int pinA[] = {PORTC0, PORTC1, PORTC2, PORTC3, PORTC4, PORTC5};

int *getPort(int pin);
int *getDDPort(int pin);
void setPin(int pin, int state);
void pinOn(int pin);
void pinOff(int pin);

#endif
