const int RLED = 0;
const int GLED = 4;
const int BLED = 5;

void setup() {
  pinMode(RLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(BLED, OUTPUT);
}

void loop() {
  digitalWrite(RLED, HIGH);
  delay(1000);
  digitalWrite(RLED, LOW);
  digitalWrite(GLED, HIGH);
  delay(1000);
  digitalWrite(GLED, LOW);
  digitalWrite(BLED, HIGH);
  delay(1000);
  digitalWrite(BLED, LOW);
}
