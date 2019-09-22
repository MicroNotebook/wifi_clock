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

#include "WifiClock.h"
#include "LedControl.h"
#include "Arduino.h"

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
	_lc.setDigit(0, digit, value, false);
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
		_lc.setDigit(0, i, value % 10, dp & 0x1);
		value /= 10;
		dp >>= 1;
	}
	
	if (flag) {
		_lc.setChar(0, ul, '-', dp & 0x1);
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
	
	for (int i = 0; i < 6; i++) {
		_lc.setDigit(0, i, value % 16, false);
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

void WifiClock::_easy_write(byte digit, byte val)
{
	if (val <= 15) {
		_lc.setDigit(0, digit, val, false);
	}
}

void WifiClock::_multi_display(byte five, byte four, byte three, byte two, byte one, byte zero)
{
	_easy_write(5, five);
	_easy_write(4, four);
	_easy_write(3, three);
	_easy_write(2, two);
	_easy_write(1, one);
	_easy_write(0, zero);
}