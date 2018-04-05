#ifndef UART_H

#define UART_H
#define BAUD 9600

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

void initializeUART(long int f_cpu, unsigned int);
int echoChar(char,FILE *stream);
int getChar(FILE *stream);

#endif
