#include "A4988.h"

A4988 *newPololu(int dir, int step, int enable, int MS1, int MS2, int MS3,
                 double degrees_per_step, int RPM) {
  pololu *drive;
  drive->dir = dir;
  drive->step = step;
  drive->enable = enable;
  drive->MS1 = MS1;
  drive->MS2 = MS2;
  drive->MS3 = MS3;
  drive->degrees_per_step = degrees_per_step;
  drive->RPM = RPM;
  return drive;
}

A4988 *newPololuFA(DriveArray array) {
  pololu *drive;
  drive->dir = (int)array[0];
  drive->step = (int)array[1];
  drive->enable = (int)array[2];
  drive->MS1 = (int)array[3];
  drive->MS2 = (int)array[4];
  drive->MS3 = (int)array[5];
  drive->degrees_per_step = array[6];

  for (uint8_t i = 0; i < 6; i++) {
    /* code */
    setPin((int)array, OUTPUT);
  }

  return drive;
}

void rotateNSteps(int n, A4988 *drive) {
  int delay = 60 / drive->RPM;
  for (uint8_t i = 0; i < n; i++) {
    pinOn(drive->step);
    // _delay_ms(delay / 2);
    _delay_ms(400);
    pinOff(drive->step);
    _delay_ms(400);
    // _delay_ms(delay / 2);
  }
}
