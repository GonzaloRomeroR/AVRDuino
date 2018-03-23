#include <avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 1000
#define TEST_PIN 9

int *pinout[] = {(int *)DDD0, (int *)DDD1, (int *)DDD2, (int *)DDD3,
                 (int *)DDD4, (int *)DDD5, (int *)DDD6, (int *)DDD7,
                 (int *)DDB0, (int *)DDB1, (int *)DDB2, (int *)DDB3,
                 (int *)DDB4, (int *)DDB5};

int *pinD[] = {(int *)PORTD0, (int *)PORTD1, (int *)PORTD2, (int *)PORTD3,
               (int *)PORTD4, (int *)PORTD5, (int *)PORTD6, (int *)PORTD7,
               (int *)PORTB0, (int *)PORTB1, (int *)PORTB2, (int *)PORTB3,
               (int *)PORTB4, (int *)PORTB5};

// int pinA[] = {PORTC0, PORTC1, PORTC2, PORTC3, PORTC4, PORTC5};

int *getPort(int pin) {
  if (pin <= 7) {
    return (int *)&PORTD;
  } else {
    return (int *)&PORTB;
  }
}

int *getDDPort(int pin) {
  if (pin <= 7) {
    return (int *)&DDRD;
  } else {
    return (int *)&DDRB;
  }
}

void setPin(int pin, int state) {
  int *port = getDDPort(pin);
  if (!state) {
    *port |= _BV(*pinout[pin]);
  } else {
    *port &= ~_BV(*pinout[pin]);
  }
}

void pinOn(int pin) {
  int *puerto = getPort(pin);
  *puerto |= _BV(*pinD[pin]);
}

void pinOff(int pin) {
  int *puerto = getPort(pin);
  *puerto &= ~_BV(*pinD[pin]);
}

int main(void) {
  setPin(TEST_PIN, 0);
  pinOn(TEST_PIN);
  _delay_ms(BLINK_DELAY_MS);
  pinOff(TEST_PIN);
  _delay_ms(BLINK_DELAY_MS);
  pinOn(TEST_PIN);
}
