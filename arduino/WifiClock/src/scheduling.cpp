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