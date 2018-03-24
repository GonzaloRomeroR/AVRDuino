#include "./lib/easyavr/core.h"
// #include <avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 1000
#define TEST_PIN 7
#define OUTPUT 0
#define INPUT 1

int main(void) {
  setPin(2, OUTPUT);
  pinOn(2);
}
