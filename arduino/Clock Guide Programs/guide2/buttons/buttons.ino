const int MODE = 12;
const int RLED = 0;

void setup() {
  pinMode(RLED, OUTPUT);
  pinMode(MODE, INPUT_PULLUP);
}

void loop() {
  int state = digitalRead(MODE);
  digitalWrite(RLED, !state);
}
