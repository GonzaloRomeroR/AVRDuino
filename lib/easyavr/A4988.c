#include "A4988.h"

void setPololu(pololu *drive, int dir, int step, int enable, int MS1, int MS2,
               int MS3, double degrees_per_step, int RPM) {
  drive->dir = dir;
  drive->step = step;
  drive->enable = enable;
  drive->MS1 = MS1;
  drive->MS2 = MS2;
  drive->MS3 = MS3;
  drive->degrees_per_step = degrees_per_step;
  drive->RPM = RPM;
  setPin(dir, OUTPUT);
  setPin(step, OUTPUT);
  setPin(enable, OUTPUT);
  setPin(MS1, OUTPUT);
  setPin(MS2, OUTPUT);
  setPin(MS3, OUTPUT);
}

void setPololuFA(pololu *drive, DriveArray array) {
  drive->dir = (int)array[0];
  drive->step = (int)array[1];
  drive->enable = (int)array[2];
  drive->MS1 = (int)array[3];
  drive->MS2 = (int)array[4];
  drive->MS3 = (int)array[5];
  drive->degrees_per_step = array[6];
  drive->RPM = (int)array[7];

  for (uint8_t i = 0; i < 6; i++) {
    setPin((int)array[i], OUTPUT);
  }
}

A4988 newPololu(int dir, int step, int enable, int MS1, int MS2, int MS3,
                double degrees_per_step, int RPM) {
  pololu drive;
  drive.dir = dir;
  drive.step = step;
  drive.enable = enable;
  drive.MS1 = MS1;
  drive.MS2 = MS2;
  drive.MS3 = MS3;
  drive.degrees_per_step = degrees_per_step;
  drive.RPM = RPM;
  setPin(dir, OUTPUT);
  setPin(step, OUTPUT);
  setPin(enable, OUTPUT);
  setPin(MS1, OUTPUT);
  setPin(MS2, OUTPUT);
  setPin(MS3, OUTPUT);
  return drive;
}

A4988 newPololuFA(DriveArray array) {
  pololu drive;
  drive.dir = (int)array[0];
  drive.step = (int)array[1];
  drive.enable = (int)array[2];
  drive.MS1 = (int)array[3];
  drive.MS2 = (int)array[4];
  drive.MS3 = (int)array[5];
  drive.degrees_per_step = array[6];

  for (uint8_t i = 0; i < 6; i++) {
    setPin((int)array[i], OUTPUT);
  }

  return drive;
}

void setSpeed(int speed, pololu *drive) { drive->RPM = speed; };

void rotateNSteps(int n, A4988 *drive, int dir) {
  pinOn(drive->enable);
  if (dir) {
    pinOn(drive->dir);
  } else {
    pinOff(drive->dir);
  }
  int delay = 60 / drive->RPM;
  for (uint8_t i = 0; i < n; i++) {
    pinOn(drive->step);
    // Reeplaces this with timers/interruptions
    _delay_ms(RPM_DELAY);
    pinOff(drive->step);
    _delay_ms(RPM_DELAY);
  }
  pinOff(drive->enable);
}
