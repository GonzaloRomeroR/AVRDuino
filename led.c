#include "./lib/easyavr/A4988.h"
#include "./lib/easyavr/A4988_interrups.h"
#include "./lib/easyavr/core.h"

#include "./lib/thrdparty/uart.h"

#define FALSE 0
#define TRUE 1
#define NUM_STEPPERS 4

volatile int count[NUM_STEPPERS];
volatile int delay;

// char *dialog[] = {"Stepper 1 on the run\n\r", "Stepper 2 on the run\n\r",
// "Stepper 3 on the run\n\r", "Stepper 4 on the run\n\r"};

STEPPER *PAParray[NUM_STEPPERS];

ISR(TIMER0_OVF_vect, ISR_NOBLOCK) {

  for (uint8_t i = 0; i < NUM_STEPPERS; i++) {
    count[i]++;
    if (PAParray[i]->enabled) {
      if (PAParray[i]->motor->stepps > 0) {
        delay = (60 / PAParray[i]->motor->RPM) * 61;
        if (count[i] >= delay / 2) {
          pinOn(PAParray[i]->motor->step);
          if (count[i] >= delay) {
            PAParray[i]->motor->stepps--;
            pinOff(PAParray[i]->motor->step);
            // uart_puts(dialog[i]);
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
  // uart_setup();
  DriveArray STPArray1 = {2, 3, 4, 0, 0, 0, 1.8, 30};
  DriveArray STPArray2 = {5, 6, 7, 0, 0, 0, 1.8, 60};
  DriveArray STPArray3 = {8, 9, 10, 0, 0, 0, 1.8, 60};
  DriveArray STPArray4 = {11, 12, 13, 0, 0, 0, 1.8, 30};

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
  PAParray[3] = &PAP3;

  for (uint8_t i = 0; i < NUM_STEPPERS; i++) {
    count[i] = 0;
  }

  rotateNSteps(10, &PAP1, FORWARD);
  rotateNSteps(20, &PAP2, FORWARD);
  rotateNSteps(20, &PAP3, FORWARD);
  rotateNSteps(60, &PAP4, FORWARD);

  setTimer0(T0_PRESCALER_256);
  // setSpeed(60, &PAP1);
  // setTimer0PS(T0_PRESCALER_64);

  while (1) {
    // busy loop
  }
}
