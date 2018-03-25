#include "./lib/easyavr/A4988.h"
#include "./lib/easyavr/core.h"
#include <util/delay.h>

#define PIN 6
#define FALSE 0
#define TRUE 1

DriveArray STP = {2, 3, 4, 5, 6, 1.8, 120};
int main(void) {
  pololu *stp = newPololuFA(STP);
  rotateNSteps(200, stp);
}
