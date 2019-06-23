const int MODE = 12;
const int INCR = 10;
const int DECR = 2;
const int RLED = 0;
const int GLED = 4;
const int BLED = 5;

void setup() {
  pinMode(RLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(BLED, OUTPUT);
  pinMode(MODE, INPUT_PULLUP);
  pinMode(INCR, INPUT_PULLUP);
  pinMode(DECR, INPUT_PULLUP);
}

void loop() {
  int state = digitalRead(MODE);
  digitalWrite(RLED, !state);
  int state2 = digitalRead(INCR);
  digitalWrite(GLED, !state2);
  int state3 = digitalRead(DECR);
  digitalWrite(BLED, !state3);
}
