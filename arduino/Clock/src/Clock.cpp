#include "Clock.h"
#include "Arduino.h"

Clock::Clock(byte sec, byte min, byte hr, byte day, byte month, int year)
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

Clock::Clock(Time time)
{
  _t = time;
}

Time Clock::getTime(bool military)
{
	Time temp = _t;
	if (!military) {
		if (temp.hours == 0) {
			temp.hours = 12;
		} else if (temp.hours > 12) {
			temp.hours -= 12;
		}
	}
	return temp;
}

void Clock::setTime(byte sec, byte min, byte hr, byte day, byte month, int year)
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

void Clock::disableTimer(void)
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

void Clock::enableTimer(void)
{
	_timer.attach(1.0, [this](void){ this->_increase_second(); });
}