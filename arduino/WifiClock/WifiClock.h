#ifndef WIFICLOCK_H
#define WIFICLOCK_H

#include "Arduino.h"
#include "LedControl.h"
#include "Ticker.h"

#define RLED	0
#define GLED	4
#define BLED	5

#define BEEPER	16

#define MODE	9
#define INCR	10
#define DECR	2

#define CLK		14
#define DIN		13
#define LOAD	15

#define DIG0	0
#define DIG1	1
#define DIG2	2
#define DIG3	3
#define DIG4	4
#define DIG5	5

class WifiClock
{
  public:
    WifiClock(void);
	void attach_interrupt(int button, void (*func)(void), int mode);
    /*void connect_to_wifi(char* ssid, char* password);
    void set_time(int hour, int minute, int second);
    void set_time_ntp(int utc_offset);
    void start_clock24(void);*/
    void display_brightness(int value);
    void display_clear(void);
    void write_num(int value);
	void write_num(float value);
    void write_num(int value, byte dp);
	void write_num_f(int value, byte dp, bool right, bool zeros);
    void write_hex(int value);
    void toggle_led(int led);
	void set_led(int led);
	void set_led(int led1, int led2);
	void set_led(int led1, int led2, int led3);
	void clear_led(int led);
	void clear_led(int led1, int led2);
	void clear_led(int led1, int led2, int led3);
	void copy_state(int button, int led);
	int  get_button(int button);
    /*void increment_num(void);
    void increment_num(byte hex);
    void decrement_num(void);
    void decrement_num(byte hex);
    void mode_button_callback(void);
    void incr_button_callback(void);
    void decr_button_callback(void);
    void clock_timer_callback(void);*/
    void timer_callback(void (*func)(void), float period);
  private:
    const int _digits[6] = {DIG0, DIG1, DIG2, DIG3, DIG4, DIG5};
    const char _hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	LedControl _lc = LedControl(DIN, CLK, LOAD, 1);					// Initialize MAX7219
	Ticker _timer;													// Initialize timer
	
	int _count(int n);
	byte _place_decimal(float f);
	int _get6(float f);
	/*void _update_clock24(void);
    byte _debounce(int button);*/
};

#endif