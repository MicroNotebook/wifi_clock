#include <Clock.h>

// create clock object
Clock c = Clock();

void setup() {
  Serial.begin(9600);                 // open serial monitor with 9600 baud rate
  c.setTime(0, 4, 19, 20, 6, 2019);   // setting time without making a Time struct
  c.startClock();                     // start the clock
}

// display the time to the Serial Monitor 
void showTime(void)
{
  Time t = c.getTime(true);   // get time in 24 hour mode
  Serial.print(t.hours);      // print hours
  Serial.print(t.minutes);    // print minutes
  Serial.print(" hours and ");
  Serial.print(t.seconds);    // print seconds
  Serial.print(" seconds on ");
  Serial.print(t.months);     // print month
  Serial.print("/");
  Serial.print(t.days);       // print days
  Serial.print("/");
  Serial.println(t.years);    // print years
}

void loop() {
  showTime();
  delay(1000);
}
