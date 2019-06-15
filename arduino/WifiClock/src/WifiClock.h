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

#define NOTE_C3		130.8
#define NOTE_CS3	138.6
#define NOTE_DF3	138.6
#define NOTE_D3		146.8
#define NOTE_DS3	155.6
#define NOTE_EF3	155.6
#define NOTE_E3		164.8
#define NOTE_F3		174.6
#define NOTE_FS3	185.0
#define NOTE_GF3	185.0
#define NOTE_G3		196.0
#define NOTE_GS3	207.7
#define NOTE_AF3	207.7
#define NOTE_A3		220.0
#define NOTE_AS3	233.1
#define NOTE_BF3	233.1
#define NOTE_B3		246.9

#define NOTE_C4		261.6
#define NOTE_CS4	277.2
#define NOTE_DF4	277.2
#define NOTE_D4		293.7
#define NOTE_DS4	311.1
#define NOTE_EF4	311.1
#define NOTE_E4		329.6
#define NOTE_F4		349.2
#define NOTE_FS4	370.0
#define NOTE_GF4	370.0
#define NOTE_G4		392.0
#define NOTE_GS4	415.3
#define NOTE_AF4	415.3
#define NOTE_A4		440.0
#define NOTE_AS4	466.2
#define NOTE_BF4	466.2
#define NOTE_B4		493.9

#define NOTE_C5		523.3
#define NOTE_CS5	554.4
#define NOTE_DF5	554.4
#define NOTE_D5		587.3
#define NOTE_DS5	622.3
#define NOTE_EF5	622.3
#define NOTE_E5		659.3
#define NOTE_F5		698.5
#define NOTE_FS5	740.0
#define NOTE_GF5	740.0
#define NOTE_G5		784.0
#define NOTE_GS5	830.6
#define NOTE_AF5	830.6
#define NOTE_A5		880.0
#define NOTE_AS5	932.3
#define NOTE_BF5	932.3
#define NOTE_B5		987.8

#define MAX_INT		999999
#define MIN_INT		-99999
#define MAX_HEX		0xFFFFFF
#define MIN_HEX		0x000000
#define MAX_FLOAT	999999.0
#define MIN_FLOAT	-99999.0

class WifiClock
{	
  public:  
    WifiClock(void);
    /*void connect_to_wifi(char* ssid, char* password);
    void set_time(int hour, int minute, int second);
    void set_time_ntp(int utc_offset);
    void start_clock24(void);*/
    void display_brightness(int value);
    void display_clear(void);
	void write_num(double value);
    void write_num(int value, byte dp=0, bool right=true, bool zeros=true);
    void write_hex(unsigned int value);
	void write_digit(int digit, int value);
	void write_led(int digit, int led, bool state);
    void toggle_led(int led1, int led2=-1, int led3=-1);
	void set_led(int led1, int led2=-1, int led3=-1);
	void clear_led(int led1, int led2=-1, int led3=-1);
	void copy_state(int button, int led);
	int  get_button(int button);
	void play_note(float frequency);
	void stop_note(void);
    void increment_num(int val);
	void increment_num(double val);
    void decrement_num(int val);
	void decrement_num(double val);
    void mode_button_callback(void (*func)(void), int mode);
    void incr_button_callback(void (*func)(void), int mode);
    void decr_button_callback(void (*func)(void), int mode);
    //void clock_timer_callback(void (*func)(void));
    void timer_callback(float period, void (*func)(void));
	
  private:
    const int _digits[6] = {DIG0, DIG1, DIG2, DIG3, DIG4, DIG5};
	LedControl _lc = LedControl(DIN, CLK, LOAD, 1);					// Initialize MAX7219
	Ticker _timer;													// Initialize timer
	//Ticker _clockTimer;											// Initialize a timer for the clock
	byte _curr_type = 0;											// 0: nothing
																	// 1: int
																	// 2: hex
																	// 3: float
	int _curr_int = 0;
	unsigned int _curr_hex = 0x0;
	double _curr_float = 0.0;
	byte _curr_dp = 0x0;
	bool _curr_right = true;
	bool _curr_zeros = true;
	
	int _count(int n);
	byte _place_decimal(double f);
	int _getDig(double f, int ub);
	bool _check_int(int val, bool add);
	bool _check_hex(unsigned int val, bool add);
	bool _check_float(double val, bool add);
	
	/*void _update_clock24(void);
    byte _debounce(int button);*/
};

#endif