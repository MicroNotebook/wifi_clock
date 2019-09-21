#include "WifiClock.h"
#include "Clock.h"

void WifiClock::start_clock(void)
{
	_clock.startClock();
}

void WifiClock::stop_clock(void)
{
	_clock.stopClock();
}

Time WifiClock::get_time(void)
{
	return _clock.getTime();
}

void WifiClock::set_time(Time time)
{
	_clock.setTime(time);
}

void WifiClock::set_time(short sec, short min, short hr, short day, short month, int year)
{
	_clock.setTime(sec, min, hr, day, month, year);
}

void WifiClock::set_military_time(bool set)
{
	_military_time = set;
}

short WifiClock::_correct_hours(short hour)
{
	short returned_hours;
	if (_military_time) {
		returned_hours = hour;
	} else {
		if (hour > 12) { // 1300 - 2300 hours
			returned_hours = hour - 12;
		} else if (hour != 0) { // 0100 - 1200 hours
			returned_hours = hour;
		} else { // 0000 hours
			returned_hours = 12;
		}
	}
	return returned_hours;
}

void WifiClock::display_time(bool secs, bool right, bool display_pm_light, int pin)
{
	// Configure Time
	Time t = _clock.getTime();
	short hour = this->_correct_hours(t.hours);
	short min = t.minutes;
	short sec = t.seconds;
	
	// Display Time
	if (secs) {			// seconds
		_multi_display(hour / 10, hour % 10, min / 10, min % 10, sec / 10, sec % 10);
	} else {
		if (right) {	// no seconds, right aligned
			_multi_display(255, 255, hour / 10, hour % 10, min / 10, min % 10);
			
		} else {		// no seconds, left aligned
			_multi_display(hour / 10, hour % 10, min / 10, min % 10, 255, 255);
		}
		_curr_type = 0;
	}
	
	// display PM led if desired
	if (display_pm_light) {
		if (pin == RLED || pin == BLED || pin == GLED) {
			digitalWrite(pin, t.PM);
		}
	}
}

void WifiClock::display_date(byte pos)
{
  // Configure Date
  Time t = _clock.getTime();
  byte day = t.days;
  byte month = t.months;
  
  // Display Date
  if (pos <= 2) {
    _lc.setDigit(0, pos++, day % 10, false);
    _lc.setDigit(0, pos++, day / 10, false);
    _lc.setDigit(0, pos++, month % 10, false);
    _lc.setDigit(0, pos, month / 10, false);
	_curr_type = 0;
  }
}

void WifiClock::display_day(byte pos)
{
  byte day = (_clock.getTime()).days;
  if (pos <= 4) {
    _lc.setDigit(0, pos++, day % 10, false);
    _lc.setDigit(0, pos, day / 10, false);
	_curr_type = 0; 
  }
}

void WifiClock::display_month(byte pos)
{
  byte month = (_clock.getTime()).months;
  if (pos <= 4) {
    _lc.setDigit(0, pos++, month % 10, false);
    _lc.setDigit(0, pos, month / 10, false);
	_curr_type = 0;
  }
}

void WifiClock::display_year(byte pos)
{
  // Configure Date
  int year = (_clock.getTime()).years;
  
  // Display Date
  if (pos <= 2) {
    for(int i = pos ; i < pos + 4; i++) {
      _lc.setDigit(0, i, year % 10, false);
      year /= 10;
    }
	_curr_type = 0;
  }
}