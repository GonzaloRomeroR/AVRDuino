#include "./lib/easyavr/core.h"
#include <util/delay.h>

#define OUTPUT 0
#define INPUT 1
#define PIN 6

int main(void) {
  setPin(PIN, OUTPUT);
  pinOn(PIN);
}
