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
  int seconds = n % 60;
  int minutes = n / 60;
  int secOnes = seconds % 10;
  int secTens = seconds / 10;
  int minOnes = minutes % 10;
  int minTens = minutes / 10;
  lc.setDigit(0, 0, secOnes, false);
  lc.setDigit(0, 1, secTens, false);
  lc.setDigit(0, 2, minOnes, false);
  lc.setDigit(0, 3, minTens, false);
}

void loop() {
  for (int i = 0; i < 3600; i++) {
    write_num(i);
    delay(1000);
  }
}
