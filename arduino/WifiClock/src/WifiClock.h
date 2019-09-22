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

#ifndef WIFICLOCK_H
#define WIFICLOCK_H

// built in header files
#include <unordered_map>
#include "Arduino.h"

// ESP8266 header files
#include "ESP8266WiFi.h"
#include "WiFiUdp.h"
#include "Ticker.h"

// dependency header files
#include "LedControl.h"
#include "NTPClient.h"

// project header files
#include "NoteConstants.h"
#include "BoardConstants.h"
#include "Clock.h"

// constants
#define MAX_INT      999999
#define MIN_INT      -99999
#define MAX_HEX      0xFFFFFF
#define MIN_HEX      0x000000
#define MAX_FLOAT    999999.0
#define MIN_FLOAT    -99999.0

#define ACCURACY     64

#define CURR_NOTHING 0
#define CURR_INT     0
#define CURR_HEX     0
#define CURR_FLOAT   0

typedef void (*function_t)(void);
typedef std::unordered_map<Time, function_t> Schedule;

class WifiClock
{	
  public:
	// Constructor
    WifiClock(void);
	
	// Display Control Functions
    void display_brightness(int value);
    void display_clear(void);
	void write_led(int digit, int led, bool state);
	void write_digit(int digit, int value);
	
	// Display Write Functions
    void write_num(int value, byte dp=0, bool right=true, bool zeros=true);
    void write_num(double value);
	void write_hex(unsigned int value);
    void increment_num(int val);
	void increment_num(double val);
    void decrement_num(int val);
	void decrement_num(double val);
	int get_curr_int(void);
	unsigned int get_curr_hex(void);
	double get_curr_float(void);
	
	// LED Functions
	static void write_led(int led, byte state);
	static void set_led(int led1, int led2=-1, int led3=-1);
	static void clear_led(int led1, int led2=-1, int led3=-1);
	static void toggle_led(int led1, int led2=-1, int led3=-1);
	
	// Button Functions
	static int get_button(int button);
	static void copy_state(int button, int led);
	static void mode_button_callback(void (*func)(void), int mode);
    static void incr_button_callback(void (*func)(void), int mode);
    static void decr_button_callback(void (*func)(void), int mode);
	static byte debounce(int button);
	
	// Beeper Functions
	static void play_note(float frequency);
	static void stop_note(void);
	
	// Timing Functions
	void start_clock(bool wifi);
	void stop_clock(void);
	Time get_time(void);
	void set_time(Time time);
	void set_time(short sec, short min, short hr, short day, short month, int year);
	void set_military_time(bool set);
	void display_time(bool secs=true, bool right=true, bool display_pm_light=true, int pin=RLED);
	void display_date(byte pos=0);
	void display_day(byte pos=0);
	void display_month(byte pos=0);
	void display_year(byte pos=0);
	
	// Scheduling Functions
	void schedule_event(Time t, void (*func)(void));
	void remove_event(Time t);
	void check_schedule(void);
	bool event_scheduled(Time t);
	bool event_scheduled(void);
	
	// Wifi Time Functions
	bool connect_to_wifi(const char* ssid, const char* password, bool disp=false);
	bool check_connection(void);
	void start_wifi_time(const char* ssid, const char* password, bool disp=false);
	void start_wifi_time(const char* ssid, const char* password, short offset, bool disp=false);
	void stop_wifi_time(void);
	void set_wifi_time_offset(short offset);
	void set_time_wifi(void);
	
	
  private:
	LedControl _lc = LedControl(DIN, CLK, LOAD, 1);	// Initialize MAX7219
	
	// variables to allow for easy update of the display
	byte _curr_type = CURR_NOTHING;	// 0: nothing
									// 1: int
									// 2: hex
									// 3: float
	int _curr_int = 0;
	unsigned int _curr_hex = 0x0;
	double _curr_float = 0.0;
	byte _curr_dp = 0x0;
	bool _curr_right = true;
	bool _curr_zeros = true;
	
	// variables used for wifi time keeping
	WiFiUDP _ntpUDP;
	NTPClient _timeClient = NTPClient(_ntpUDP);
	
	// variables used for scheduling
	Schedule _schedule;
	
	// variables used for time keeping
	Ticker _wifi_timer;
	Clock _clock;
	short _offset = 0;
	bool _military_time = false;
	bool _wifi_clock_set = false;
	bool _clock_set = false;
	
	// Display Helper Functions
	int _count(int n);
	byte _place_decimal(double f);
	int _getDig(double f, int ub);
	bool _check_int(int val, bool add);
	bool _check_hex(unsigned int val, bool add);
	bool _check_float(double val, bool add);
	void _easy_write(byte digit, byte val);
	void _multi_display(byte five, byte four, byte three, byte two, byte one, byte zero);
	
	// Beeper Helper Functions
	static void _play(void);
	
	// Timing Helper Functions
	short _correct_hours(short hour);
};

#endif