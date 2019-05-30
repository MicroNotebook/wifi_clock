const int MODE = 9;
const int RLED = 0;
//Bonus
const int INCR = 10;
const int DECR = 2;
const int GLED = 4;
const int BLED = 5;

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
