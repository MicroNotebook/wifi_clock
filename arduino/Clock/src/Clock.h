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
		// Constructors
		Clock(byte sec, byte min, byte hr, byte day=255, byte month=255, int year=-1000);
		Clock(Time time);
		Clock(void);
		
		// returns the time
		// if military = true, return the time in 24 hour mode
		// else, return the time in 12 hour mode
		Time getTime(bool military);
		
		// set the time with either a time sturcture,
		// or the individual elements
		// if any of the entries are invalid, they will be skipped over
		void setTime(Time time);
		void setTime(byte sec, byte min, byte hr, byte day=255, byte month=255, int year=-1000);
		
		// start the timer for the clock
		void startClock(void); 
		
		// stop the timer for the clock
		void stopClock(void);
		
		// this function should not be used
		// this is used to update the time with the timer
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