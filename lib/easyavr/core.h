#ifndef CORE
#define CORE
#define OUTPUT 0
#define INPUT 1

#include <avr/io.h>


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
