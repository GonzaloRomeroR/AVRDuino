#include "./lib/easyavr/A4988.h"
#include "./lib/easyavr/core.h"

#define FALSE 0
#define TRUE 1
volatile uint8_t count;
pololu STP;

// DriveArray STP = {2, 3, 4, 5, 6, 1.8, 2000};
int main(void) {

  // pololu *stp = newPololuFA(STP);
  STP.dir = 2;
  STP.step = 3;
  STP.enable = 4;
  STP.MS1 = 0;
  STP.MS2 = 0;
  STP.MS3 = 0;
  STP.degrees_per_step = 1.8;
  STP.RPM = 120;
  setPin(2, OUTPUT);
  setPin(3, OUTPUT);
  setPin(4, OUTPUT);
  pololu *stp = &STP;
  // implementar rotacion del motor sin _delay_ms (usar timers).
  rotateNSteps(15, stp, FORWARD);
  rotateNSteps(15, stp, BACKWARD);
}
