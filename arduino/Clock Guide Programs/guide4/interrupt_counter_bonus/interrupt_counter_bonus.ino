#include "LedControl.h"

#define DIN 13
#define CLK 14
#define LOAD 15
#define MODE 9
#define INCR 10
#define DECR 2
#define RLED 0
#define GLED 4
#define BLED 5

LedControl lc = LedControl(DIN, CLK, LOAD, 1);

int i;

void ICACHE_RAM_ATTR mode_callback(void)
{
  int state = !digitalRead(MODE);
  digitalWrite(RLED, state);
  if (state == HIGH) {
    lc.setDigit(0, 5, 1, false);
  } else {
    lc.clearDisplay(0);
    write_num(i);
  }
}

void ICACHE_RAM_ATTR incr_callback(void)
{
  int state = !digitalRead(INCR);
  digitalWrite(GLED, state);
  if (state == HIGH) {
    lc.setDigit(0, 4, 2, false);
  } else {
    lc.clearDisplay(0);
    write_num(i);
  }
}

void ICACHE_RAM_ATTR decr_callback(void)
{
  int state = !digitalRead(DECR);
  digitalWrite(BLED, state);
  if (state == HIGH) {
    lc.setDigit(0, 3, 3, false);
  } else {
    lc.clearDisplay(0);
    write_num(i);
  }
}

void setup() {
  // setup MAX7219
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);

  // setup buttons
  pinMode(MODE, INPUT_PULLUP);
  pinMode(INCR, INPUT_PULLUP);
  pinMode(DECR, INPUT_PULLUP);

  // setup ISRs
  attachInterrupt(digitalPinToInterrupt(MODE), mode_callback, CHANGE);
  attachInterrupt(digitalPinToInterrupt(INCR), incr_callback, CHANGE);
  attachInterrupt(digitalPinToInterrupt(DECR), decr_callback, CHANGE);
  
  // setup LEDs
  pinMode(RLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(BLED, OUTPUT);
  
}

void write_num(int n)
{
  int ones = n % 10;
  int tens = n / 10;
  lc.setDigit(0, 0, ones, false);
  lc.setDigit(0, 1, tens, false);
}

void loop() {
  for (i = 0; i < 60; i++) {
    write_num(i);
    delay(1000);
  }
}
