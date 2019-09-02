#include <WifiClock.h>

WifiClock wc = WifiClock();

void setup(){
  const char* ssid     = "SSID";		// replace with network SSID
  const char* password = "PASSWORD";	// replace with network password
  const int   offset   = -4;			// replace with time zone offset (-4 is EDT)

  wc.set_military_time(false);			// use a 12 hour clock
  wc.start_wifi_time(ssid, password, offset);
}

void loop() {
  wc.update_and_display_time();
  delay(1000);
}
