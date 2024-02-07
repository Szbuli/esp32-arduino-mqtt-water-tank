const int relay1 = 18;
const int relay2 = 19;

void setupRelay() {
  digitalWrite(relay1, HIGH);
  pinMode(relay1, OUTPUT);

  digitalWrite(relay2, HIGH);
  pinMode(relay2, OUTPUT);
}

void turnOnRelay1() {
  digitalWrite(relay1, LOW);
  Serial.println("relay 1 on");
}

void turnOffRelay1() {
  digitalWrite(relay1, HIGH);
  Serial.println("relay 1 off");
}

void turnOnRelay2() {
  digitalWrite(relay2, LOW);
  Serial.println("relay 2 on");
}

void turnOffRelay2() {
  digitalWrite(relay2, HIGH);
  Serial.println("relay 2 off");
}
