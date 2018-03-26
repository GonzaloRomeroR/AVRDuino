#include "A4988_interrups.h"
void setTimer0(enum t0_prescaler PS) {
  // TCCR0B |= _BV(CS02) | _BV(CS00); // Set timer to click at F_CPU / 1024.
  TCCR0B |= PS;
  // Enable timer overflow interrupts.
  TIMSK0 |= _BV(TOIE0);
  TCNT0 = 0; // Reset timer/counter zero.
  // Enable interrupts.
  sei();
};

void setTimer0PS(enum t0_prescaler ps) { TCCR0B = ps; };
