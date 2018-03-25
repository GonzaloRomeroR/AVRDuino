#include "./lib/easyavr/A4988.h"
#include "./lib/easyavr/core.h"

#define FALSE 0
#define TRUE 1
volatile uint8_t count;

int main(void) {
  // DriveArray STPArray = {12, 13, 10, 0, 0, 0, 1.8, 2000};
  DriveArray STPArray = {2, 3, 4, 0, 0, 0, 1.8, 2000};
  pololu STP = newPololuFA(STPArray);

  // implementar rotacion del motor sin _delay_ms (usar timers).
  rotateNSteps(15, &STP, BACKWARD);
  rotateNSteps(15, &STP, FORWARD);
}
