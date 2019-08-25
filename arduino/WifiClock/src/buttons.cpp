#include "WifiClock.h"

int WifiClock::get_button(int button)
{
	return !digitalRead(button);
}

void WifiClock::copy_state(int button, int led)
{
	digitalWrite(led, !digitalRead(button));
}

void WifiClock::mode_button_callback(void (*func)(void), int mode)
{
	if (mode != LOW && mode != CHANGE && mode != RISING && mode != FALLING && mode != HIGH)
		return;
	attachInterrupt(digitalPinToInterrupt(MODE), func, mode);
}

void WifiClock::incr_button_callback(void (*func)(void), int mode)
{
	if (mode != LOW && mode != CHANGE && mode != RISING && mode != FALLING && mode != HIGH)
		return;
	attachInterrupt(digitalPinToInterrupt(INCR), func, mode);
}

void WifiClock::decr_button_callback(void (*func)(void), int mode)
{
	if (mode != LOW && mode != CHANGE && mode != RISING && mode != FALLING && mode != HIGH)
		return;
	attachInterrupt(digitalPinToInterrupt(DECR), func, mode);
}

byte WifiClock::debounce(int button)
{
	byte flag = 0;
	for (int i = 0; i < ACCURACY; i++) {
		flag |= digitalRead(button);
		if (flag) {
			return !flag;
		}
		delayMicroseconds(8);
	}
	return !flag;
}