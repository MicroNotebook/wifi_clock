#include "WifiClock.h"

/********************************
* This function is similar to	*
* the other write_led function, *
* however this one sets or 		*
* clears the three LEDs on the 	*
* right of the board.			*
********************************/
void WifiClock::write_led(int led, byte state)
{
	digitalWrite(led, state);
}

void WifiClock::set_led(int led1, int led2, int led3)
{
	digitalWrite(led1, HIGH);
	if (led2 != -1) {
		digitalWrite(led2, HIGH);
	}
	if (led3 != -1) {
		digitalWrite(led3, HIGH);
	}
}

void WifiClock::clear_led(int led1, int led2, int led3)
{
	digitalWrite(led1, LOW);
	if (led2 != -1) {
		digitalWrite(led2, LOW);
	}
	if (led3 != -1) {
		digitalWrite(led3, LOW);
	}
}

void WifiClock::toggle_led(int led1, int led2, int led3)
{
	digitalWrite(led1, !digitalRead(led1));
	if (led2 != -1) {
		digitalWrite(led2, !digitalRead(led2));
	}
	if (led3 != -1) {
		digitalWrite(led3, !digitalRead(led3));
	}
}