const int overflowInput = 2;
int buttonState = LOW;

int counter = 100;

void setupOverflowSensor() {
  pinMode(overflowInput, INPUT_PULLUP);
}

void readOverflowSensor() {
  int newButtonState = digitalRead(overflowInput);
  if (buttonState != newButtonState || counter == 100) {
    Serial.print("Overflow sensor ");
    if (newButtonState == LOW) {
      Serial.println("ON");
      publish(MQTT_OVERFLOW_SENSOR_TOPIC, ON_PAYLOAD);
    } else {
      Serial.println("OFF");
      publish(MQTT_OVERFLOW_SENSOR_TOPIC, OFF_PAYLOAD);
    }
    counter = 0;
  }

  buttonState = newButtonState;
  counter++;
}