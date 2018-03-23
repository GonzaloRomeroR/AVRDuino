#include <avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 1000

int pinout[] = {DDD0, DDD1, DDD2, DDD3, DDD4, DDD5, DDD6,
                DDD7, DDB0, DDB1, DDB2, DDB3, DDB4, DDB5};

int pinD[] = {PORTD0, PORTD1, PORTD2, PORTD3, PORTD4, PORTD5, PORTD6,
              PORTD7, PORTB0, PORTB1, PORTB2, PORTB3, PORTB4, PORTB5};

int pinA[] = {PORTC0, PORTC1, PORTC2, PORTC3, PORTC4, PORTC5};

int *getPort(int pin) {
  int D[] = {DDRD, PORTD};
  int B[] = {DDRB, PORTB};
  if (pin <= 7) {
    return (int *)*D;
  } else {
    return (int *)*B;
  }
}

void setPin(int pin, int state) {
  int *port = getPort(pin);
  if (state) {
    port[0] |= _BV(pinout[pin]);
  } else {
    port[0] &= ~_BV(pinout[pin]);
  }
}

void pinOn(int pin) {
  int *puerto = getPort(pin);
  puerto[1] |= _BV(pinD[pin]);
}

void pinOff(int pin) {
  int *puerto = getPort(pin);
  puerto[1] &= ~_BV(pinD[pin]);
}

int main(void) {
  /* set pin 5 of PORTB for output*/
  // DDRD |= _BV(DDD7);
  setPin(7, 1);

  while (1) {
    /* set pin 5 high to turn led on */
    // PORTD |= _BV(pinD[7]);
    pinOn(7);
    _delay_ms(BLINK_DELAY_MS);

    /* set pin 5 low to turn led off */
    // PORTD &= ~_BV(pinD[7]);
    pinOff(7);
    _delay_ms(BLINK_DELAY_MS);
  }
}
