#ifndef PAP
#define PAP
#define FORWARD 1
#define BACKWARD 0
#include "core.h"
#include <util/delay.h>
#define RPM_DELAY 50

//A4988 driver struct and function declarations, you may use the custom pololu
//type if you find it more convenient.

typedef struct a4988 {
        int dir;
        int step;
        int enable;
        int MS1;
        int MS2;
        int MS3;
        double degrees_per_step;
        int RPM;
} A4988;

typedef A4988 pololu;
typedef double DriveArray[8];
//set existing A4988 struct manually or from an existing DriveArray array.
void setPololu(pololu *drive, int dir, int step, int enable, int MS1, int MS2,
               int MS3, double degrees_per_step, int RPM);

void setPololuFA(pololu *drive, DriveArray array);

//initializes pololu struct manually.
A4988 newPololu(int dir, int step, int enable, int MS1, int MS2, int MS3, double degrees_per_step, int RPM);

//initializes pololu struct from DriveArray array;
A4988 newPololuFA(DriveArray array);

void setSpeed(int speed, pololu *drive);
void rotateNSteps(int n, A4988 *drive, int dir);

#endif
