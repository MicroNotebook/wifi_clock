#include "WifiClock.h"

volatile byte _currPlay = 0;

void WifiClock::play_note(float frequency)
{
  timer1_detachInterrupt();
  timer1_attachInterrupt(_play);
  timer1_enable(TIM_DIV16, TIM_EDGE, TIM_LOOP);
  timer1_write(2500000 / frequency);
}

void WifiClock::stop_note(void)
{
	timer1_disable();
	digitalWrite(BEEPER, HIGH);
}

void WifiClock::_play(void)
{
  _currPlay = !_currPlay;
  digitalWrite(BEEPER, _currPlay);
}