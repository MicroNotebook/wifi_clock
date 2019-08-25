#include "WifiClock.h"

WifiClock::WifiClock(void)
{  
  // Initialize LEDs
  pinMode(RLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(BLED, OUTPUT);
  digitalWrite(RLED, LOW);
  digitalWrite(GLED, LOW);
  digitalWrite(BLED, LOW);
  
  // Initialize beeper
  pinMode(BEEPER, OUTPUT);
  digitalWrite(BEEPER, HIGH);
  
  // Initialize buttons with pullup resistors
  pinMode(MODE, INPUT_PULLUP);
  pinMode(INCR, INPUT_PULLUP);
  pinMode(DECR, INPUT_PULLUP);
  
  // Clear 7-segment displays
  _lc.shutdown(0, false);
  _lc.setIntensity(0, 8);
  _lc.clearDisplay(0);
}