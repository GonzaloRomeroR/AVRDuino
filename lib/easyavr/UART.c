#include "UART.h"



void initializeUART(long int f_cpu, unsigned int ubrr)
{
	UBRR0 = f_cpu/16/ubrr-1;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
  UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}


int echoChar(char c, FILE *stream)
{
	while(!(UCSR0A & (1<<UDRE0)) );
	UDR0 = c;
	return 0;
}


int getChar(FILE *stream)
{
	while ( !(UCSR0A & (1<<RXC0)) );
	return UDR0;
}
