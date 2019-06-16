#ifndef CLOCK_H
#define CLOCK_H

#include "Arduino.h"
#include "Ticker.h"

struct Time {
	byte seconds;
	byte minutes;
	byte hours;
	byte days;
	byte months;
	int years;
	bool PM;
};

class Clock
{
	public:
		Clock(byte sec, byte min, byte hr, byte day=255, byte month=255, int year=-1000);
		Clock(Time time);
		Time getTime(bool military=true);
		void setTime(byte sec, byte min, byte hr, byte day=255, byte month=255, int year=-1000);
		void enableTimer(void); 
		void disableTimer(void);
		void _increase_second(void);

	private:
		Time _t = {0, 0, 0, 1, 1, 0};
		Ticker _timer;

		void _increase_year(void);
		void _increase_month(void);
		void _increase_day(void);
		void _increase_hour(void);
		void _increase_minute(void);
};


#endif