/*************************************************************************************************
* Copyright (c) 2019 Micronote                                                                   *
*                                                                                                *
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software  *
* and associated documentation files (the "Software"), to deal in the Software without           *
* restriction, including without limitation the rights to use, copy, modify, merge, publish,     *
* distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the  *
* Software is furnished to do so, subject to the following conditions:                           *
*                                                                                                *
* The above copyright notice and this permission notice shall be included in all copies or       *
* substantial portions of the Software.                                                          *
*                                                                                                *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING  *
* BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND     *
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,   *
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, *
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.        *
*************************************************************************************************/

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