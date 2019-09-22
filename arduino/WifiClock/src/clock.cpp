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

#include "Clock.h"
#include "Ticker.h"
#include "Arduino.h"

Clock::Clock(short sec, short min, short hr, short day, short month, int year)
{
	this->setTime(sec, min, hr, day, month, year);
}

Clock::Clock(Time time)
{
	this->setTime(time);
}

Clock::Clock(void)
{
	/* NOP */
}

Time Clock::getTime(void)
{
	return _t;
}

void Clock::setTime(Time time)
{
	if (time.seconds < 60 && time.seconds >= 0) {
		_t.seconds = time.seconds;
	}
	if (time.minutes < 60 && time.minutes >= 0) {
		_t.minutes = time.minutes;
	}
	if (time.hours < 24 && time.hours >= 0) {
		_t.hours = time.hours;
	}
	if (time.days > 0 && time.days <= 31) {
		_t.days = time.days;
	}
	if (time.months > 0 && time.months <= 12) {
		_t.months = time.months;
	}
	if (time.years > -1000 && time.years <= 9999) {
		_t.years = time.years;
	}
	if (_t.hours >= 12) {
		_t.PM = true;
	} else {
		_t.PM = false;
	}
}

void Clock::setTime(short sec, short min, short hr, short day, short month, int year)
{
	if (sec < 60 && sec >= 0) {
		_t.seconds = sec;
	}
	if (min < 60 && min >= 0) {
		_t.minutes = min;
	}
	if (hr < 24 && hr >= 0) {
		_t.hours = hr;
	}
	if (day > 0 && day <= 31) {
		_t.days = day;
	}
	if (month > 0 && month <= 12) {
		_t.months = month;
	}
	if (year > -1000 && year <= 9999) {
		_t.years = year;
	}
	if (_t.hours >= 12) {
		_t.PM = true;
	} else {
		_t.PM = false;
	}
}

void Clock::startClock(void)
{
	_timer.attach(1.0, [this](void){ this->_increase_second(); });
}

void Clock::stopClock(void)
{
	_timer.detach();
}

void Clock::_increase_year(void)
{
	_t.years++;
	if (_t.years > 9999) {
		_t.years = 9999;
	}
}

void Clock::_increase_month(void)
{
	_t.months++;
	if (_t.months > 12) {
		_t.months = 1;
		_increase_year();
	}
}

void Clock::_increase_day(void)
{
	_t.days++;
	switch (_t.months)
	{ 
		// 31 day months
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			if (_t.days > 31) {
				_t.days = 1;
				_increase_month();
			}
			break;

		// 30 day months
		case 4:
		case 6:
		case 9:
		case 11:
			if (_t.days > 30) {
				_t.days = 1;
				_increase_month();
			}
			break;

		// February
		default:
			if ((_t.years % 4 == 0 && _t.years % 100 != 0) || (_t.years % 400 == 0)) {  // if leap year
				if (_t.days > 29) {
				  _t.days = 1;
				  _increase_month();
				}
			} else {
				if (_t.days > 28) {
				  _t.days = 1;
				  _increase_month();
				}
			}
	}
}

void Clock::_increase_hour(void)
{
	_t.hours++;
	if (_t.hours > 24) {
		_t.hours = 0;
		_increase_day();
	}
	if (_t.hours >= 12) {
		_t.PM = true;
	}
}

void Clock::_increase_minute(void)
{
	_t.minutes++;
	if (_t.minutes >= 60) {
		_t.minutes = 0;
		_increase_hour();
	}
}

void Clock::_increase_second(void)
{
	_t.seconds++;
	if (_t.seconds >= 60) {
		_t.seconds = 0;
		_increase_minute();
	}
}