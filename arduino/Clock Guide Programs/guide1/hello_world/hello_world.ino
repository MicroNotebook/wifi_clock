const int RLED = 0;

void setup() {
  pinMode(RLED, OUTPUT);
}

void loop() {
  digitalWrite(RLED, HIGH);
  delay(1000);
  digitalWrite(RLED, LOW);
  delay(1000);
}
