const int MODE = 14;
const int RLED = 12;
//Bonus
const int INCR = 2;
const int DECR = 0;
const int GLED = 13;
const int BLED = 15;

void setup() {
  pinMode(RLED, OUTPUT);
  pinMode(MODE, INPUT_PULLUP);
  //Bonus
  pinMode(INCR, INPUT_PULLUP);
  pinMode(DECR, INPUT_PULLUP);
  pinMode(GLED, OUTPUT);
  pinMode(BLED, OUTPUT);
}

void loop() {
  int state = digitalRead(MODE);
  digitalWrite(RLED, !state);
  //Bonus
  int state2 = digitalRead(INCR);
  int state3 = digitalRead(DECR);
  digitalWrite(GLED, !state2);
  digitalWrite(BLED, !state3);
}
