#include "LedControl.h"

#define DIN 13
#define CLK 14
#define LOAD 15

LedControl lc = LedControl(DIN, CLK, LOAD, 1);

void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
}

void write_num(int n)
{
  int ones = n % 10;
  int tens = n / 10;
  lc.setDigit(0, 0, ones, false);
  lc.setDigit(0, 1, tens, false);
}

void loop() {
  for (int i = 0; i < 60; i++) {
    write_num(i);
    delay(1000);
  }
}
