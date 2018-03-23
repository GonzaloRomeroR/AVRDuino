#include <avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 1000

int pinout[] = {DDD0, DDD1, DDD2, DDD3, DDD4, DDD5, DDD6,
                DDD7, DDB0, DDB1, DDB2, DDB3, DDB4, DDB5};

int pinD[] = {PORTD0, PORTD1, PORTD2, PORTD3, PORTD4, PORTD5, PORTD6,
              PORTD7, PORTB0, PORTB1, PORTB2, PORTB3, PORTB4, PORTB5};

// int pinA[] = {PORTC0, PORTC1, PORTC2, PORTC3, PORTC4, PORTC5};

int getPort(int pin) {
  if (pin <= 7) {
    return PORTD;
  } else {
    return PORTB;
  }
}

int getDDPort(int pin) {
  if (pin <= 7) {
    return DDRD;
  } else {
    return DDRB;
  }
}

void setPin(int pin, int state) {
  int port = getDDPort(pin);
  if (!state) {
    port |= _BV(pinout[pin]);
  } else {
    port &= ~_BV(pinout[pin]);
  }
  // return port;
}

void pinOn(int pin) {
  int puerto = getPort(pin);
  puerto |= _BV(pinD[pin]);
  // return puerto;
}

void pinOff(int pin) {
  int puerto = getPort(pin);
  puerto &= ~_BV(pinD[pin]);
  // return puerto;
}

int main(void) {
  /* set pin 5 of PORTB for output*/
  DDRD |= _BV(DDD7);
  DDRD |= _BV(pinout[2]);
  setPin(8, 0);
  setPin(12, 1);
  // int pines[] = {2, 8, 5, 7, 12};
  // for (int i = 0; i < 5; i++) {
  //   setPin(pines[i], 0);
  // }

  while (1) {
    /* set pin 5 high to turn led on */
    PORTD |= _BV(pinD[7]);
    PORTD |= _BV(pinD[8]);
    pinOn(2);
    pinOn(12);
    // for (int i = 0; i < 5; i++) {
    //   pinOn(pines[i]);
    // }
    _delay_ms(BLINK_DELAY_MS);

    /* set pin 5 low to turn led off */
    PORTD &= ~_BV(pinD[7]);
    PORTD &= ~_BV(pinD[8]);
    pinOff(2);
    pinOff(12);
    // for (int i = 0; i < 5; i++) {
    //   pinOff(pines[i]);
    // }
    _delay_ms(BLINK_DELAY_MS);
  }
}
