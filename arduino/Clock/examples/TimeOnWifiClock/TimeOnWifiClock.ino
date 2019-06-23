#include <WifiClock.h>
#include <Clock.h>

// create WifiClock and Clock objects
WifiClock wc = WifiClock();
Clock c = Clock();

void setup() {
  Time t = {0, 34, 18, 20, 6, 2019, true};  // 6:34:00 PM 6/20/2019
  c.setTime(t);                             // set the time using the time struct
  c.startClock();                           // start the clock
}

/********************************************
* This function will display the time.      *
* When the seconds are 30 or 31, the date   *
* will be displayed. When the seconds are   *
* 32 or 33, the year will be displayed.     *
********************************************/
void showTime(void)
{
  wc.display_clear();
  Time t = c.getTime(false);    // get time in 12 hour mode
  if (t.seconds < 30 || t.seconds >= 34) {
    int time_to_int = t.hours * 10000 + t.minutes * 100 + t.seconds;
    wc.write_num(time_to_int);
  } else if (t.seconds >= 30 && t.seconds < 32) {
    int date_to_int = t.months * 100 + t.days;
    wc.write_num(date_to_int, 0x0, true, false);
  } else {
    wc.write_num(t.years, 0x0, false);
  }
  wc.write_led(RLED, (byte)t.PM);
}

void loop() {
  showTime();
  delay(500);
}
