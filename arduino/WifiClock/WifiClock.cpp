#include "Arduino.h"
#include "WifiClock.h"

volatile byte _currPlay = 0;

void _play(void)
{
  _currPlay = !_currPlay;
  digitalWrite(BEEPER, _currPlay);
}

WifiClock::WifiClock(void)
{  
  // Initialize LEDs
  pinMode(RLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(BLED, OUTPUT);
  
  // Initialize beeper
  pinMode(BEEPER, OUTPUT);
  digitalWrite(BEEPER, HIGH);
  
  // Initialize buttons with interrupts
  pinMode(MODE, INPUT_PULLUP);
  pinMode(INCR, INPUT_PULLUP);
  pinMode(DECR, INPUT_PULLUP);

  // Initialize current number and current decimal points
  
  // Setup rtc
  
  // Clear 7-segment displays
  _lc.shutdown(0, false);
  _lc.setIntensity(0, 8);
  _lc.clearDisplay(0);
  
  // Set all LEDs to 0
  digitalWrite(RLED, LOW);
  digitalWrite(GLED, LOW);
  digitalWrite(BLED, LOW);
}

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
*/
void WifiClock::display_brightness(int value)
{
	_lc.setIntensity(0, value);
}

void WifiClock::display_clear(void)
{
	_lc.clearDisplay(0);
}

void WifiClock::write_num(int value)
{
  if (value >= 0 && value <= 999999) {
    for (int i = 0; i < 6; i++) {
      _lc.setDigit(0, _digits[i], value % 10, false);
      value /= 10;
    }
  } else if (value < 0 && value >= -99999) {
    _lc.setChar(0, DIG5, '-', false);
    value *= -1;
    for (int i = 0; i < 5; i++) {
      _lc.setDigit(0, _digits[i], value % 10, false);
      value /= 10;
    }
  }
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

byte WifiClock::_place_decimal(float f)
{
	int nd = _count((int)f);
	byte dp = 32 >> (nd - 1);
	return dp;
}

int WifiClock::_get6(float f)
{
	int nd = _count((int)f);
	int ten = 1;
	for (int i = 0; i < 6 - nd; i++) {
		ten *= 10;
	}
	return ten * f;
}

void WifiClock::write_num(float value)
{
	
	byte dp = _place_decimal(value);	// determine where to place decimal point
	int disp_val = _get6(value);		// get 6 significant digits
	write_num(disp_val, dp);			// display the value
}

void WifiClock::write_num(int value, byte dp)
{
  if (value >= 0 && value <= 999999) {
    for (int i = 0; i < 6; i++) {
      _lc.setDigit(0, _digits[i], value % 10, dp & 0x1);
      value /= 10;
      dp = dp >> 1;
    }
  } else if (value < 0 && value >= -99999) {
    value *= -1;
    for (int i = 0; i < 5; i++) {
      _lc.setDigit(0, _digits[i], value % 10, dp & 0x1);
      value /= 10;
      dp = dp >> 1;
    }
	_lc.setChar(0, DIG5, '-', dp & 0x1);
  }
}

void WifiClock::write_num_f(int value, byte dp, bool right, bool zeros)
{
	if (value >= 0 && value <= 999999) {
		if (right == true) {		// right oriented
			if (zeros == true) {	// display leading zeros
				write_num(value, dp);
			} else {				// don't display leading zeros
				int nd = _count(value);
				for (int i = 0; i < nd; i++) {
					_lc.setDigit(0, _digits[i], value % 10, dp & 0x1);
					value /= 10;
					dp = dp >> 1;
				}
			}
		} else {					// left oriented (zeros will always be ignored in this mode)
			int nd = _count(value);
			for (int i = 6 - nd; i < 6; i++) {
				_lc.setDigit(0, _digits[i], value % 10, dp & 0x1);
				value /= 10;
				dp = dp >> 1;
			}
		}
	} else if (value < 0 && value >= -99999) {
		if (right == true) {		// right oriented
			if (zeros == true) {	// display leading zeros
				write_num(value, dp);
			} else {				// dont' display leading zeros
				value *= -1;
				int nd = _count(value);
				for (int i = 0; i < nd; i++) {
					_lc.setDigit(0, _digits[i], value % 10, dp & 0x1);
					value /= 10;
					dp = dp >> 1;
				}
				_lc.setChar(0, _digits[nd], '-', dp & 0x1);
			}
		} else {					// left oriented (zeros will always be ignored in this mode)
			value *= -1;
			int nd = _count(value);
			for (int i = 5 - nd; i < 5; i++) {
				_lc.setDigit(0, _digits[i], value % 10, dp & 0x1);
				value /= 10;
				dp = dp >> 1;
			}
			_lc.setChar(0, DIG5, '-', dp & 0x1);
		}
	}
}

void WifiClock::write_hex(int value)
{
	if (value > 0 && value <= 0xFFFFFF) {
		for (int i = 0; i < 6; i++) {
			_lc.setChar(0, _digits[i], _hex[value % 16], false);
			value /= 16;
		}
	}
}

void WifiClock::toggle_led(int led)
{
	digitalWrite(led, !digitalRead(led));
}

void WifiClock::set_led(int led)
{
	digitalWrite(led, HIGH);
}

void WifiClock::set_led(int led1, int led2)
{
	digitalWrite(led1, HIGH);
	digitalWrite(led2, HIGH);
}

void WifiClock::set_led(int led1, int led2, int led3)
{
	digitalWrite(led1, HIGH);
	digitalWrite(led2, HIGH);
	digitalWrite(led3, HIGH);
}

void WifiClock::clear_led(int led)
{
	digitalWrite(led, LOW);
}

void WifiClock::clear_led(int led1, int led2)
{
	digitalWrite(led1, LOW);
	digitalWrite(led2, LOW);
}

void WifiClock::clear_led(int led1, int led2, int led3)
{
	digitalWrite(led1, LOW);
	digitalWrite(led2, LOW);
	digitalWrite(led3, LOW);
}

void WifiClock::copy_state(int button, int led)
{
	digitalWrite(led, !digitalRead(button));
}

int WifiClock::get_button(int button)
{
	return !digitalRead(button);
}

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

/*
void WifiClock::increment_num(void)
{
	
}

void WifiClock::increment_num(byte hex)
{
	
}

void WifiClock::decrement_num(void)
{
	
}

void WifiClock::decrement_num(byte hex)
{
	
}
*/
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
/*
void WifiClock::clock_timer_callback(void)
{
	
}
*/
void WifiClock::timer_callback(float period, void (*func)(void))
{
	_timer.attach(period, func);
}
/*
void WifiClock::_update_clock24(void)
{
	
}

byte WifiClock::_debounce(int button)
{
	return 0;
}*/