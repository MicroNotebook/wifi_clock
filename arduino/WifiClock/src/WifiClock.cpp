#include "Arduino.h"
#include "WifiClock.h"

volatile byte _currPlay = 0;

// Initializer
WifiClock::WifiClock(void)
{  
  // Initialize LEDs
  pinMode(RLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(BLED, OUTPUT);
  digitalWrite(RLED, LOW);
  digitalWrite(GLED, LOW);
  digitalWrite(BLED, LOW);
  
  // Initialize beeper
  pinMode(BEEPER, OUTPUT);
  digitalWrite(BEEPER, HIGH);
  
  // Initialize buttons with pullup resistors
  pinMode(MODE, INPUT_PULLUP);
  pinMode(INCR, INPUT_PULLUP);
  pinMode(DECR, INPUT_PULLUP);

  // Initialize current number and current decimal points
  
  // Setup rtc
  
  // Clear 7-segment displays
  _lc.shutdown(0, false);
  _lc.setIntensity(0, 8);
  _lc.clearDisplay(0);
}

// Display Control Functions
void WifiClock::display_brightness(int value)
{
	_lc.setIntensity(0, value);
}

void WifiClock::display_clear(void)
{
	_lc.clearDisplay(0);
	_curr_type = 0;
}

/****************************************
* This function turns on a single		*
* led in the display.					*
* The digit parameter is the display  	*
* number you want to write to.			*
* The led is the led you want to 		*
* turn on. The decimal point is 0,		*
* then 1 is segment a, and so on.		*
****************************************/
void WifiClock::write_led(int digit, int led, bool state)
{
	_lc.setLed(0, digit, led, state);
	_curr_type = 0;
}

void WifiClock::write_digit(int digit, int value)
{
	_lc.setDigit(0, _digits[digit], value, false);
	_curr_type = 0;
}

// Display Write Functions
void WifiClock::write_num(int value, byte dp, bool right, bool zeros)
{
	// save values
	_curr_int = value;
	_curr_dp = dp;
	_curr_right = right;
	_curr_zeros = zeros;
	_curr_type = 1;
	
	// clear display
	_lc.clearDisplay(0);
	
	// default values
	int ll = 0;
	int ul = 6;
	bool flag = false;
	
	if (value < 0 && value >= -99999) {			// value negative
		ul = 5;
		value *= -1;
		flag = true;
	} else if (value < 0 || value > 999999) {	// value outside of bounds
		return;
	}

	if (right) {					// right oriented
		if (!zeros) {				// no leading zeros
			ul = _count(value);
		}	
	} else {						// left oriented (no leading zeros)
		ll = ul - _count(value);
	}
	
	for (int i = ll ; i < ul; i++) {
		_lc.setDigit(0, _digits[i], value % 10, dp & 0x1);
		value /= 10;
		dp >>= 1;
	}
	
	if (flag) {
		_lc.setChar(0, _digits[ul], '-', dp & 0x1);
	}
}

void WifiClock::write_num(double value)
{	
	int disp_val = 0;
	double held = value;
	byte dp = 0x0;
	if (value >= 0.0 && value <= 999999.0) {
		dp = _place_decimal(value);			// determine where to place decimal point
		disp_val = _getDig(value, 6);		// get 6 significant digits
	} else if (value < 0.0 && value >= -99999.0) {
		value *= -1.0;
		dp = _place_decimal(value) >> 1;	// determine where to place decimal point
		disp_val = -1 * _getDig(value, 5);	// get 5 significant digits
	} else {
		return;
	}
	write_num(disp_val, dp, true, true);
	
	// save values
	_curr_float = held;
	_curr_type = 3;
}

void WifiClock::write_hex(unsigned int value)
{
	// save values
	_curr_hex = value;
	_curr_type = 2;
	
	// clear display
	_lc.clearDisplay(0);
	
	for (int i = 0; i < 6; i++) {
		_lc.setDigit(0, _digits[i], value % 16, false);
		value >>= 4;
	}
}

void WifiClock::increment_num(int val)
{	
	if (_curr_type == 1 && _check_int(val, true)) {				// integer
		_curr_int += val;
		write_num(_curr_int, _curr_dp, _curr_right, _curr_zeros);
	} else if (_curr_type == 2 && _check_hex(val, true)) {		// hex
		_curr_hex += (unsigned int)(val);
		write_hex(_curr_hex);
	} else if (_curr_type == 3 && _check_float(val, true)) {	// float
		_curr_float += (double)val;
		write_num(_curr_float);
	}
}

void WifiClock::increment_num(double val)
{	
	if (_curr_type == 3 && _check_float(val, true)) {	// float
		_curr_float += (double)val;
		write_num(_curr_float);
	}
}

void WifiClock::decrement_num(int val)
{
	if (_curr_type == 1 && _check_int(val, false)) {			// integer
		_curr_int -= val;
		write_num(_curr_int, _curr_dp, _curr_right, _curr_zeros);
	} else if (_curr_type == 2 && _check_hex(val, false)) {		// hex
		_curr_hex -= (unsigned int)(val);
		write_hex(_curr_hex);
	} else if (_curr_type == 3 && _check_float(val, false)) {	// float
		_curr_float -= (double)val;
		write_num(_curr_float);
	}
}

void WifiClock::decrement_num(double val)
{
	if (_curr_type == 3 && _check_float(val, false)) {	// float
		_curr_float -= (double)val;
		write_num(_curr_float);
	}
}

int WifiClock::get_curr_int(void)
{
	return _curr_int;
}

unsigned int WifiClock::get_curr_hex(void)
{
	return _curr_hex;
}

double WifiClock::get_curr_float(void)
{
	return _curr_float;
}

// Display Helper Functions
int WifiClock::_count(int n)
{
	if (n == 0) {
		return 1;
	}
	int nd = 0;
	while (n > 0) {
		n /= 10;
		nd++;
	}
	return nd;
}

byte WifiClock::_place_decimal(double f)
{
	int nd = _count((int)f);
	byte dp = 32 >> (nd - 1);
	return dp;
}

int WifiClock::_getDig(double f, int ub)
{
	int nd = _count((int)f);
	int ten = 1;
	for (int i = 0; i < ub - nd; i++) {
		ten *= 10;
	}
	return ten * f;
}

bool WifiClock::_check_int(int val, bool add)
{
	int new_val;
	if (add) {	// if adding value to int
		new_val = _curr_int + val;
	} else {	// if subtracting value from int
		new_val = _curr_int - val;
	}
	if (new_val <= MAX_INT && new_val >= MIN_INT) {
		return true;
	} else {
		return false;
	}
}

bool WifiClock::_check_hex(unsigned int val, bool add)
{
	unsigned int new_val;
	if (add) {	// if adding value to hex
		new_val = _curr_hex + val;
	} else {	// if subtracting value from hex
		new_val = _curr_hex - val;
	}
	if (new_val <= MAX_HEX && new_val >= MIN_HEX) {
		return true;
	} else {
		return false;
	}
}

bool WifiClock::_check_float(double val, bool add)
{
	double new_val;
	if (add) {	// if adding value to double
		new_val = _curr_float + val;
	} else {	// if subtracting value from double
		new_val = _curr_float - val;
	}
	if (new_val <= MAX_FLOAT && new_val >= MIN_FLOAT) {
		return true;
	} else {
		return false;
	}
}

// LED Functions
/********************************
* This function is similar to	*
* the other write_led function, *
* however this one sets or 		*
* clears the three LEDs on the 	*
* right of the board.			*
********************************/
void WifiClock::write_led(int led, byte state)
{
	digitalWrite(led, state);
}

void WifiClock::set_led(int led1, int led2, int led3)
{
	digitalWrite(led1, HIGH);
	if (led2 != -1) {
		digitalWrite(led2, HIGH);
	}
	if (led3 != -1) {
		digitalWrite(led3, HIGH);
	}
}

void WifiClock::clear_led(int led1, int led2, int led3)
{
	digitalWrite(led1, LOW);
	if (led2 != -1) {
		digitalWrite(led2, LOW);
	}
	if (led3 != -1) {
		digitalWrite(led3, LOW);
	}
}

void WifiClock::toggle_led(int led1, int led2, int led3)
{
	digitalWrite(led1, !digitalRead(led1));
	if (led2 != -1) {
		digitalWrite(led2, !digitalRead(led2));
	}
	if (led3 != -1) {
		digitalWrite(led3, !digitalRead(led3));
	}
}

// Buttons Functions
int WifiClock::get_button(int button)
{
	return !digitalRead(button);
}

void WifiClock::copy_state(int button, int led)
{
	digitalWrite(led, !digitalRead(button));
}

void WifiClock::mode_button_callback(void (*func)(void), int mode)
{
	if (mode != LOW && mode != CHANGE && mode != RISING && mode != FALLING && mode != HIGH)
		return;
	attachInterrupt(digitalPinToInterrupt(MODE), func, mode);
}

void WifiClock::incr_button_callback(void (*func)(void), int mode)
{
	if (mode != LOW && mode != CHANGE && mode != RISING && mode != FALLING && mode != HIGH)
		return;
	attachInterrupt(digitalPinToInterrupt(INCR), func, mode);
}

void WifiClock::decr_button_callback(void (*func)(void), int mode)
{
	if (mode != LOW && mode != CHANGE && mode != RISING && mode != FALLING && mode != HIGH)
		return;
	attachInterrupt(digitalPinToInterrupt(DECR), func, mode);
}

byte WifiClock::debounce(int button)
{
	byte flag = 0;
	for (int i = 0; i < ACCURACY; i++) {
		flag |= digitalRead(button);
		if (flag) {
			return !flag;
		}
		delayMicroseconds(8);
	}
	return !flag;
}

// Timer Functions
void WifiClock::timer_callback(float period, void (*func)(void))
{
	_timer.attach(period, func);
}

// Beeper Functions
void WifiClock::play_note(float frequency)
{
  timer1_detachInterrupt();
  timer1_attachInterrupt(_play);
  timer1_enable(TIM_DIV16, TIM_EDGE, TIM_LOOP);
  timer1_write(2500000 / frequency);
}

void WifiClock::stop_note(void)
{
	timer1_disable();
	digitalWrite(BEEPER, HIGH);
}

// Beeper Helper Functions
void WifiClock::_play(void)
{
  _currPlay = !_currPlay;
  digitalWrite(BEEPER, _currPlay);
}

// Not Yet Implemented
/*
void WifiClock::connect_to_wifi(char* ssid, char* password)
{
	
}

void WifiClock::set_time(int hour, int minute, int second)
{
	
}

void WifiClock::set_time_ntp(int utc_offset)
{
	
}

void WifiClock::start_clock24(void)
{
	
}

void WifiClock::clock_timer_callback(void)
{
	
}

void WifiClock::_update_clock24(void)
{
	
}
*/