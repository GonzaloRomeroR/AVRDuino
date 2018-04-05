#include "./lib/easyavr/A4988.h"
#include "./lib/easyavr/A4988_interrups.h"
#include "./lib/easyavr/core.h"

#include "./lib/thrdparty/uart.h"

#define FALSE 0
#define TRUE 1
#define NUM_STEPPERS 4

volatile int count[NUM_STEPPERS];
volatile int delay;

STEPPER *PAParray[NUM_STEPPERS];

// Timer0 overflow interruption, checks enabled steppers setep's left and
// moves them accordingly until there is no one left.
ISR(TIMER0_OVF_vect, ISR_NOBLOCK) {
  // increases each stepper's count assigned variable
  for (uint8_t i = 0; i < NUM_STEPPERS; i++) {
    count[i]++;
    // check if current stepper is enabled
    if (PAParray[i]->enabled) {
      // check if current stepper has any steps left (checking could be merged
      // with above's conditional but I think this way is more readable).
      if (PAParray[i]->motor->stepps > 0) {
        // Calculates amount of overflows until next stepp accordingly to
        // current stepper's RPM
        delay = (60 / PAParray[i]->motor->RPM) * 61;
        // in order to emulate a square shaped wave, the stepper's step pin will
        // turn on in the middle of the dealy and turn off again at it's end.
        if (count[i] >= delay / 2) {
          pinOn(PAParray[i]->motor->step);
          if (count[i] >= delay) {
            PAParray[i]->motor->stepps--;
            pinOff(PAParray[i]->motor->step);
            count[i] = 0;
            // if there are not stepps left the current stepper will be
            // disabled.
            if (PAParray[i]->motor->stepps == 0) {
              PAParray[i]->enabled = FALSE;
              pinOff(PAParray[i]->motor->enable);
            }
          }
        }
      }
    }
  }
}

int main(void) {
  // uart_setup();
  DriveArray STPArray1 = {2, 3, 4, 0, 0, 0, 1.8, 60};
  DriveArray STPArray2 = {5, 6, 7, 0, 0, 0, 1.8, 60};
  DriveArray STPArray3 = {8, 9, 10, 0, 0, 0, 1.8, 60};
  DriveArray STPArray4 = {11, 12, 13, 0, 0, 0, 1.8, 60};

  pololu STP1 = newPololuFA(STPArray1);
  pololu STP2 = newPololuFA(STPArray2);
  pololu STP3 = newPololuFA(STPArray3);
  pololu STP4 = newPololuFA(STPArray4);

  STEPPER PAP1;
  PAP1.motor = &STP1;
  PAP1.enabled = 0;

  STEPPER PAP2;
  PAP2.motor = &STP2;
  PAP2.enabled = 0;

  STEPPER PAP3;
  PAP3.motor = &STP3;
  PAP3.enabled = 0;

  STEPPER PAP4;
  PAP4.motor = &STP4;
  PAP4.enabled = 0;

  PAParray[0] = &PAP1;
  PAParray[1] = &PAP2;
  PAParray[2] = &PAP3;
  PAParray[3] = &PAP4;

  for (uint8_t i = 0; i < NUM_STEPPERS; i++) {
    count[i] = 0;
  }

  rotateNSteps(80, &PAP1, FORWARD);
  rotateNSteps(80, &PAP2, FORWARD);
  rotateNSteps(80, &PAP3, BACKWARD);
  rotateNSteps(80, &PAP4, FORWARD);

  setTimer0(T0_PRESCALER_256);
  // setSpeed(60, &PAP1);
  // setTimer0PS(T0_PRESCALER_64);

  while (1) {
    // busy loop
  }
}
