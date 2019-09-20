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

void WifiClock::set_time(byte sec, byte min, byte hr, byte day, byte month, int year)
{
	_clock.setTime(sec, min, hr, day, month, year);
}

void WifiClock::display_time(bool secs, bool right)
{
	// Configure Time
	Time t = _clock.getTime();
	byte hour = t.hours;
	byte min = t.minutes;
	byte sec = t.seconds;
	
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