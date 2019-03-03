#include <LedControl.h>
#include <Ticker.h>

const int clk = D0;
const int load = D2;
const int din = D1;
const int decr_but = D3;
const int incr_but = D4;
const int mode_but = D5;
const int r_led = D6;
const int g_led = D7;
const int b_led = D8;
const int dig0 = 2;
const int dig1 = 1;
const int dig2 = 0;
const int dig3 = 5;
const int dig4 = 4;
const int dig5 = 3;

LedControl lc = LedControl(din, clk, load, 1);
const float timPeriod = 0.1;  //timer period in seconds
Ticker timer;

volatile int count = -1;

void displayCount(void)
{
  count++;
  if (count > 999999)
    count = 0;
  int a = count % 10;
  int b = (count / 10) % 10;
  int c = (count / 100) % 10;
  int d = (count / 1000) % 10;
  int e = (count / 10000) % 10;
  int f = count / 100000;
  lc.clearDisplay(0);
  lc.setDigit(0, dig0, a, false);
  if (count >= 10)
    lc.setDigit(0, dig1, b, false);
  if (count >= 100)
    lc.setDigit(0, dig2, c, false);
  if (count >= 1000)
    lc.setDigit(0, dig3, d, false);
  if (count >= 10000)
    lc.setDigit(0, dig4, e, false);
  if (count >= 100000)
    lc.setDigit(0, dig5, f, false);
}

void change_r(void)
{
  digitalWrite(r_led, !digitalRead(mode_but));
}

void change_g(void)
{
  digitalWrite(g_led, !digitalRead(incr_but));
}

void change_b(void)
{
  digitalWrite(b_led, !digitalRead(decr_but));
}

void setup() {
  //setup MAX7219
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);

  //setup timer
  timer.attach(timPeriod, displayCount);

  //setup LEDs
  pinMode(r_led, OUTPUT);
  pinMode(g_led, OUTPUT);
  pinMode(b_led, OUTPUT);

  //setup buttons
  pinMode(mode_but, INPUT_PULLUP);
  pinMode(incr_but, INPUT_PULLUP);
  pinMode(decr_but, INPUT_PULLUP);

  //attach interupts to buttons
  attachInterrupt(digitalPinToInterrupt(mode_but), change_r, CHANGE);
  attachInterrupt(digitalPinToInterrupt(incr_but), change_g, CHANGE);
  attachInterrupt(digitalPinToInterrupt(decr_but), change_b, CHANGE);
}

void loop() {
}
