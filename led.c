#include "./lib/easyavr/A4988.h"
#include "./lib/easyavr/A4988_interrups.h"
#include "./lib/easyavr/core.h"

#define FALSE 0
#define TRUE 1
#define NUM_STEPPERS 2

volatile int count[2];
volatile int delay;

STEPPER *PAParray[NUM_STEPPERS];

ISR(TIMER0_OVF_vect, ISR_NOBLOCK) {
  count[0]++;
  count[1]++;
  for (uint8_t i = 0; i < NUM_STEPPERS; i++) {
    if (PAParray[i]->enabled) {
      delay = (60 / PAParray[i]->motor->RPM) * 61;
      if (PAParray[i]->motor->stepps > 0) {
        if (count[i] >= delay / 2) {
          pinOn(PAParray[i]->motor->step);
          if (count[i] >= delay) {
            PAParray[i]->motor->stepps--;
            pinOff(PAParray[i]->motor->step);
            count[i] = 0;
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
  DriveArray STPArray1 = {2, 3, 4, 0, 0, 0, 1.8, 30};
  DriveArray STPArray2 = {5, 6, 12, 0, 0, 0, 1.8, 60};

  pololu STP1 = newPololuFA(STPArray1);
  pololu STP2 = newPololuFA(STPArray2);

  STEPPER PAP1;
  PAP1.motor = &STP1;
  PAP1.enabled = 0;

  STEPPER PAP2;
  PAP2.motor = &STP2;
  PAP2.enabled = 0;

  PAParray[0] = &PAP1;
  PAParray[1] = &PAP2;

  for (uint8_t i = 0; i < NUM_STEPPERS; i++) {
    count[i] = 0;
  }

  rotateNSteps(5, &PAP1, FORWARD);
  rotateNSteps(10, &PAP2, FORWARD);

  setTimer0(T0_PRESCALER_256);

  // setSpeed(60, &PAP1);
  // setTimer0PS(T0_PRESCALER_64);

  while (1) {
  }
}
