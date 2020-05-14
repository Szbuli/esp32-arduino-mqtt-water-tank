const int relay = 14;

void setupRelay() {
   digitalWrite(relay, HIGH);
   pinMode(relay, OUTPUT);
}

void turnOnRelay() {
  digitalWrite(relay, LOW);
  Serial.println("relay on");
}

void turnOffRelay() {
  digitalWrite(relay, HIGH);
  Serial.println("relay off");
}
