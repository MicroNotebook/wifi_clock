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

#include <unordered_map>
#include "WifiClock.h"
#include "Clock.h"

void WifiClock::schedule_event(Time t, void (*func)(void))
{
	_schedule.insert({t, func});
}

void WifiClock::remove_event(Time t)
{
	if (_schedule.find(t) != _schedule.end()) {
		_schedule.erase(t);
	}
}

void WifiClock::check_schedule(void)
{
	Time t = _clock.getTime();
	if (_schedule.find(t) != _schedule.end()) {
		_schedule[t]();
	}
}

bool WifiClock::event_scheduled(Time t)
{
	return _schedule.find(t) != _schedule.end();
}

bool WifiClock::event_scheduled(void)
{
	Time t = _clock.getTime();
	return _schedule.find(t) != _schedule.end();
}