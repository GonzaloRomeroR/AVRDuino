#include "core.h"

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

// _BV(binary) === 1 << binary

void setPin(int pin, int state) {
  int *port = getDDPort(pin);
  if (state) {
    *port |= _BV(pinout[pin]);
  } else {
    *port &= ~_BV(pinout[pin]);
  }
}

void pinOn(int pin) {
  int *puerto = getPort(pin);
  *puerto |= _BV(pinD[pin]);
}

void pinOff(int pin) {
  int *puerto = getPort(pin);
  *puerto &= ~_BV(pinD[pin]);
}
