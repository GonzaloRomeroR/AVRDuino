//All code taken from this post http://www.justgeek.de/a-simple-simplex-uart-for-debugging-avrs/
//with just a minor tweaks to fit into the current project.
//All content of this site is licensed under the CC BY-NC-SA 3.0 license unless otherwise specified.
#ifndef __UART_H
#define __UART_H
#include <stdint.h>
#include <avr/io.h>

// Baud rate
#define UART_BPS 9600
#define UART_TX_DDR  DDRD
#define UART_TX_PORT PORTD
#define UART_TX_PIN  PD1

extern uint8_t uart_setup(void);
extern void uart_putc(char c);
extern void uart_puts(char* s);

#endif
