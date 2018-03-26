#include "./lib/easyavr/A4988.h"
#include "./lib/easyavr/A4988_interrups.h"
#include "./lib/easyavr/core.h"

#define FALSE 0
#define TRUE 1
#define NUM_STEPPERS 2

volatile int count;

STEPPER *PAParray[4];

ISR(TIMER0_OVF_vect) {
  count++;
  for (uint8_t i = 0; i < NUM_STEPPERS; i++) {
    if (PAParray[i]->enabled) {

      int delay = (60 / PAParray[i]->motor->RPM) * 61;
      if (PAParray[i]->motor->stepps > 0) {
        if (count >= delay / 2) {
          pinOn(PAParray[i]->motor->step);
        }
      }
      if (count >= delay) {
        if (PAParray[i]->motor->stepps > 0) {
          PAParray[i]->motor->stepps--;
          pinOff(PAParray[i]->motor->step);
          count = 0;
          if (PAParray[i]->motor->stepps == 0) {
            PAParray[i]->enabled = FALSE;
            pinOff(PAParray[i]->motor->enable);
          }
        }
      }
    }
  }
}

int main(void) {

  DriveArray STPArray1 = {2, 3, 4, 0, 0, 0, 1.8, 120};
  DriveArray STPArray2 = {12, 11, 10, 0, 0, 0, 1.8, 200};

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

  setTimer0(T0_PRESCALER_1024);
  count = 0;

  setSpeed(240, &STP1);

  rotateNSteps(200, &PAP1, FORWARD);
  rotateNSteps(200, &PAP2, FORWARD);

  while (1) {
    /* code */
  }
}
