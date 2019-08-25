#include "WifiClock.h"

void WifiClock::connect_to_wifi(const char* ssid, const char* password)
{
	WiFi.begin(ssid, password);
	while(WiFi.status() != WL_CONNECTED) {
		delay(500);
	}
}

bool WifiClock::check_connection(void)
{
	return WiFi.status() == WL_CONNECTED;
}

void WifiClock::start_wifi_time(const char* ssid, const char* password)
{
	this->connect_to_wifi(ssid, password);
	_timeClient.begin();
}

void WifiClock::start_wifi_time(const char* ssid, const char* password, short offset)
{
	this->connect_to_wifi(ssid, password);
	_offset = offset;
	_timeClient.begin();
}

void WifiClock::stop_wifi_time(void)
{
	_timeClient.end();
}

void WifiClock::set_time_offset(short offset)
{
	_offset = offset;
}

void WifiClock::set_military_time(bool set)
{
	_military_time = set;
}

void WifiClock::update_time_from_wifi(void)
{
	_timeClient.update();
	_hours = _timeClient.getHours() + _offset;
	_pm = _hours >= 12;
	_minutes = _timeClient.getMinutes();
	_seconds = _timeClient.getSeconds();
}

unsigned short WifiClock::_correct_hours(void)
{
	unsigned short hours;
	if (_military_time) {
		hours = _hours;
	} else {
		if (_hours > 12) { // 1300 - 2300 hours
			hours = _hours - 12;
		} else if (_hours != 0) { // 0100 - 1200 hours
			hours = _hours;
		} else { // 0000 hours
			hours = 12;
		}
	}
	return hours;
}

void WifiClock::display_time(bool display_pm_light, int pin)
{
	unsigned short hours = this->_correct_hours();
	
	_lc.setDigit(0, 5, hours / 10, false);
	_lc.setDigit(0, 4, hours % 10, false);
	_lc.setDigit(0, 3, _minutes / 10, false);
	_lc.setDigit(0, 2, _minutes % 10, false);
	_lc.setDigit(0, 1, _seconds / 10, false);
	_lc.setDigit(0, 0, _seconds % 10, false);
	
	if (display_pm_light) {
		if (pin == RLED || pin == BLED || pin == GLED) {
			digitalWrite(pin, _pm);
		}
	}
}

void WifiClock::update_and_display_time(bool display_pm_light, int pin)
{
	this->update_time_from_wifi();
	this->display_time(display_pm_light, pin);
}