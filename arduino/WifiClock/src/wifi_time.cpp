#include "WifiClock.h"
#include "Clock.h"

void WifiClock::connect_to_wifi(const char* ssid, const char* password, bool disp)
{
	WiFi.begin(ssid, password);
	if (disp) {
		// C
		_lc.setLed(0, 3, 1, true);
		_lc.setLed(0, 3, 4, true);
		_lc.setLed(0, 3, 5, true);
		_lc.setLed(0, 3, 6, true);
		
		// o
		_lc.setLed(0, 2, 3, true);
		_lc.setLed(0, 2, 4, true);
		_lc.setLed(0, 2, 5, true);
		_lc.setLed(0, 2, 7, true);
		
		// n
		_lc.setLed(0, 1, 3, true);
		_lc.setLed(0, 1, 5, true);
		_lc.setLed(0, 1, 7, true);
		
		// n.
		_lc.setLed(0, 0, 3, true);
		_lc.setLed(0, 0, 5, true);
		_lc.setLed(0, 0, 7, true);
		_lc.setLed(0, 0, 0, true);
	}
	while(WiFi.status() != WL_CONNECTED) {
		delay(500);
	}
	if (disp) {
		_lc.clearDisplay(0);
	}
}

bool WifiClock::check_connection(void)
{
	return WiFi.status() == WL_CONNECTED;
}

void WifiClock::start_wifi_time(const char* ssid, const char* password, bool disp)
{
	this->connect_to_wifi(ssid, password, disp);
	_timeClient.begin();
}

void WifiClock::start_wifi_time(const char* ssid, const char* password, short offset, bool disp)
{
	this->connect_to_wifi(ssid, password, disp);
	_offset = offset;
	_timeClient.begin();
}

void WifiClock::stop_wifi_time(void)
{
	_timeClient.end();
}

void WifiClock::set_wifi_time_offset(short offset)
{
	_offset = offset;
}

void WifiClock::set_time_wifi(void)
{
	// update the time
	_timeClient.update();
	
	// correct hours
	short c_hours = _timeClient.getHours() + _offset;
	if (c_hours >= 24) {
		c_hours -= 24;
	} else if (c_hours < 0) {
		c_hours += 24;
	}

	// make the time struct
	Time t = {
		.seconds = _timeClient.getSeconds(),
		.minutes = _timeClient.getMinutes(),
		.hours   = c_hours,			// corrected hours
		.days    = -1,				// invalid and not set
		.months  = -1,				// invalid and not set
		.years   = -1000,			// invalid and not set
		.PM      = false			// this will be corrected by the set function
	};

	// set the time
	_clock.setTime(t);
}