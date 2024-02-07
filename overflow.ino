const int overflowInput = 21;
int buttonState = LOW;

int counter = 100;
int delayCounter = 0;

int overflowPumpAutoModeEnabled = false;

void refreshOverflowPumpModeFromStorage() {
  overflowPumpAutoModeEnabled = isOverflowPumpAutoModeEnabledFromStorage();
  Serial.print("Overflow pump auto mode enabled: ");
  Serial.println(overflowPumpAutoModeEnabled);

  turnOffRelay2();
}

bool isOverflowPumpAutoModeEnabled() {
  return overflowPumpAutoModeEnabled;
}

void setupOverflowSensor() {
  pinMode(overflowInput, INPUT_PULLUP);

  refreshOverflowPumpModeFromStorage();
}

void readOverflowSensor() {
  int newButtonState = digitalRead(overflowInput);
  if (buttonState != newButtonState || counter == 100) {
    Serial.print("Overflow sensor ");
    if (newButtonState == LOW) {
      Serial.println("ON");
      updateOverflowPumpIfNeeded(true);
      publish(MQTT_OVERFLOW_SENSOR_TOPIC, ON_PAYLOAD);
    } else {
      Serial.println("OFF");
      updateOverflowPumpIfNeeded(false);
      publish(MQTT_OVERFLOW_SENSOR_TOPIC, OFF_PAYLOAD);
    }
    counter = 0;
  }

  buttonState = newButtonState;
  counter++;
}

void updateOverflowPumpIfNeeded(bool overflowSensorActive) {
  if (overflowPumpAutoModeEnabled && delayCounter > 5) {
    Serial.print("Turn overflow pump ");
    if (overflowSensorActive) {
      Serial.println("ON");
      turnOnRelay2();
    } else {
      Serial.println("OFF");
      turnOffRelay2();
    }
    delayCounter = 0;
  }
  delayCounter++;
}