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
#include "Arduino.h"

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