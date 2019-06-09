#include "WifiClock.h"

WifiClock wc = WifiClock();
const float period = 0.1;
volatile int count = -1;
byte check = 0;
byte state = 0;

void ICACHE_RAM_ATTR change_r(void)
{
  wc.copy_state(MODE, RLED);
}

void ICACHE_RAM_ATTR change_g(void)
{
  wc.copy_state(INCR, GLED);
}

void ICACHE_RAM_ATTR change_b(void)
{
  wc.copy_state(DECR, BLED);
}

void countUp(void)
{
  count++;
  wc.write_num_f(count, 0x0, true, false);
}

void playSound(void)
{
  if (check) {
    state = !state;
    if (state) {
      wc.play_note(NOTE_C5);
    } else {
      wc.stop_note();
    }
  } else {
    state = 0;
    wc.stop_note();
  }
}

Ticker timer;

void setup() {
  //attach interupts to buttons
  wc.mode_button_callback(change_r, CHANGE);
  wc.incr_button_callback(change_g, CHANGE);
  wc.decr_button_callback(change_b, CHANGE);

  //attach timer ISR
  wc.timer_callback(period, countUp);
  timer.attach(0.5, playSound);
}

void loop() {
  if (wc.get_button(MODE) && wc.get_button(DECR) && wc.get_button(INCR)) {
    check = !check;
  }
  delay(100);
}
