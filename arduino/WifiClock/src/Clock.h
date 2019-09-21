#ifndef CLOCK_H
#define CLOCK_H

#include "Arduino.h"
#include "Ticker.h"

/****************************************/
/************ Time Structure ************/
/****************************************/
struct Time {
    short seconds;
    short minutes;
    short hours;
    short days;
    short months;
    int years;
    bool PM;
    
    bool operator==(const Time &other) const
    {
        return (seconds == other.seconds)
            && (minutes == other.minutes)
            && (hours == other.hours)
            && (days == other.days)
            && (months == other.months)
            && (years == other.years)
            && (PM == other.PM);
    }
};

namespace std {
    template <>
    struct hash<Time>
    {
        size_t operator()(const Time& t) const
        {
            return (hash<short>()(t.seconds))
                ^ ((hash<short>()(t.minutes) << 1) >> 1)
                ^ (hash<short>()(t.hours) << 1)
                ^ ((hash<short>()(t.days) << 1) >> 1)
                ^ (hash<short>()(t.months) << 1)
                ^ ((hash<int>()(t.years) << 1) >> 1)
                ^ (hash<bool>()(t.PM) << 1);
        }
    };
}


/*************************************/
/************ Clock Class ************/
/*************************************/
class Clock
{
	public:
		// Constructors
		Clock(short sec, short min, short hr, short day=-1, short month=-1, int year=-1000);
		Clock(Time time);
		Clock(void);
		
		// returns the time
		// if military = true, return the time in 24 hour mode
		// else, return the time in 12 hour mode
		Time getTime(void);
		
		// set the time with either a time sturcture,
		// or the individual elements
		// if any of the entries are invalid, they will be skipped over
		void setTime(Time time);
		void setTime(short sec, short min, short hr, short day=-1, short month=-1, int year=-1000);
		
		// start the timer for the clock
		void startClock(void); 
		
		// stop the timer for the clock
		void stopClock(void);
		

	private:
		Time _t = {0, 0, 0, 1, 1, 0};
		Ticker _timer;

		void _increase_year(void);
		void _increase_month(void);
		void _increase_day(void);
		void _increase_hour(void);
		void _increase_minute(void);
		void _increase_second(void);
};


#endif