const int RLED = 0;
//Bonus
const int GLED = 4;
const int BLED = 5;

void setup() {
  pinMode(RLED, OUTPUT);
  //Bonus
  pinMode(GLED, OUTPUT);
  pinMode(BLED, OUTPUT);
}

void loop() {
  digitalWrite(RLED, HIGH);
  delay(1000);
  digitalWrite(RLED, LOW);
  digitalWrite(GLED, HIGH); //Bonus
  delay(1000);
  //Bonus
  digitalWrite(GLED, LOW);
  digitalWrite(BLED, HIGH);
  delay(1000);
  digitalWrite(BLED, LOW);
}
