#include <WifiClock.h>

WifiClock wc = WifiClock(); // make instance of WifiClock

const float period = 0.1;
byte check = 0;
byte state = 0;

// button interrupts
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

// timer interrupts
void countUp(void)
{
  wc.increment_num(1);
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

// timers
Ticker timer1;
Ticker timer2;

void setup() {
  //attach interupts to buttons
  wc.mode_button_callback(change_r, CHANGE);
  wc.incr_button_callback(change_g, CHANGE);
  wc.decr_button_callback(change_b, CHANGE);

  //attach timer ISR
  timer1.attach(period, countUp);
  timer2.attach(0.5, playSound);
  wc.write_num(0, 0x0, true, false);
}

void loop() {
  if (wc.get_button(MODE) && wc.get_button(DECR) && wc.get_button(INCR)) { // if all buttons pressed
    check = !check;
  }
  delay(100);
}
