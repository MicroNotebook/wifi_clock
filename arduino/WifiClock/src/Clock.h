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