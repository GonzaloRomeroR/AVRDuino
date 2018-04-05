#include "./lib/easyavr/A4988.h"
#include "./lib/easyavr/A4988_interrups.h"
#include "./lib/easyavr/core.h"
#include "./lib/easyavr/UART.h"
#include "./lib/easyavr/I2CSlave.h"

#define BAUD 9600
#define FALSE 0
#define TRUE 1
#define NUM_STEPPERS 4
#define I2C_ADDR 0x8

char datum;
int newCoordinateX = 0;
int newCoordinateY = 0;
int Diameter = 0;

volatile int count[NUM_STEPPERS];
volatile int delay;

FILE uart_io = FDEV_SETUP_STREAM(echoChar, getChar, _FDEV_SETUP_RW);

uint8_t counter;
uint8_t counterI2C;

char command[10];
char buffer[10];

STEPPER *PAParray[NUM_STEPPERS];


void commandInterpreter(void)
{
	switch (command[0]){
		case 'M':
		printf("Motor \r\n");
		default:
		break;
	}
}

ISR(USART_RX_vect)
{
	char data;
	data=getChar(&uart_io);
	echoChar(data, &uart_io);
	switch(data)
	{
		case ':':
		counter=0;
		break;
		case '\r' :
		command[counter]=0;
		commandInterpreter();
		break;
		default:
		command[counter++]=data;
		break;
	}
}


void interpreterI2C(){
	switch (buffer[0]){
		case 'X':
		newCoordinateX = atoi(&buffer[1]);
		break;
		case 'Y':
		newCoordinateY = atoi(&buffer[1]);
		break;
		case 'D':
		Diameter = atoi(&buffer[1]);
		default:
		break;
	}
}

void I2C_received(uint8_t received_data)
{
  datum = received_data;
	switch(datum)
	{
		case 'X':
		counterI2C = 0;
		buffer[counterI2C++]=datum;
		break;
		case 'Y':
		counterI2C = 0;
		buffer[counterI2C++]=datum;
		break;
		case 'D':
		counterI2C = 0;
		buffer[counterI2C++] = datum;
		break;
		case 'F' :
		buffer[counterI2C]=0;
		interpreterI2C();
		break;
		default:
		buffer[counterI2C++] = datum;
		break;
	}
}

void I2C_requested()
{
  I2C_transmitByte(datum);
}

void setupI2C()
{
  I2C_setCallbacks(I2C_received, I2C_requested);
  I2C_init(I2C_ADDR);
}


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




int * calculateSpeed(int stepsPAP1, int stepsPAP2, int stepsPAP3, int stepsPAP4){
  int stepsVector[] = {stepsPAP1, stepsPAP2, stepsPAP3, stepsPAP4};
  int maximumValue = stepsVector[0];
  int furthestPosition;
  for (int i = 0; i < 4; i++){
    if (stepsVector[i] > maximumValue){
      maximumValue = stepsVector[i];
      furthestPosition = i;
    }
  }
  static int speedVector[4];
  speedVector[furthestPosition] = 30;  //Parametro a variar

  if(maximumValue != 0){
    for (int i = 0; i < 4; i++){
      speedVector[i] = (float)stepsVector[i] / (float)maximumValue * speedVector[furthestPosition];
      if (speedVector[i] == 0){
        speedVector[i] == 1;
      }
    }
  }
  else{
    for (int i = 0; i < 4; i++){
      speedVector[i] = 1;
    }
  }
  return speedVector;
}


int main(void) {

  setupI2C();
  initializeUART(F_CPU, BAUD);
  stdout = stdin = &uart_io;
  counter = 0;
  UCSR0B|= (1<<RXCIE0);
  printf("Inicializando: \r\n");
  sei();


  DriveArray STPArray1 = {2, 3, 4, 0, 0, 0, 1.8, 30};
  DriveArray STPArray2 = {5, 6, 7, 0, 0, 0, 1.8, 30};
  DriveArray STPArray3 = {8, 9, 10, 0, 0, 0, 1.8, 30};
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
  PAParray[3] = &PAP4;

  for (uint8_t i = 0; i < NUM_STEPPERS; i++) {
    count[i] = 0;
  }


  int distance1 = 150;
  int distance2 = 300;
  int distance3 = 100;
  int distance4 = 500;
  int * speedVector;

  speedVector = calculateSpeed(distance1, distance2, distance3, distance4);

  setSpeed(*(speedVector+0), &PAP1);
  setSpeed(*(speedVector+1), &PAP2);
  setSpeed(*(speedVector+2), &PAP3);
  setSpeed(*(speedVector+3), &PAP4);

  rotateNSteps(distance1, &PAP1, FORWARD);
  rotateNSteps(distance2, &PAP2, FORWARD);
  rotateNSteps(distance3, &PAP3, FORWARD);
  rotateNSteps(distance4, &PAP4, FORWARD);

  setTimer0(T0_PRESCALER_1024);
  setTimer0PS(T0_PRESCALER_8);

  while (1) {
    printf("CoordenadaX: %d\r\n", newCoordinateX);
		printf("CoordenadaY: %d\r\n", newCoordinateY);
		printf("Diametro: %d\r\n", Diameter);
		_delay_ms(3000);
  }
}
