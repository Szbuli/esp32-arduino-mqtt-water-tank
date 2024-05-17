const int overflowInput = 21;
int buttonState = LOW;

int counter = 100;
int delayCounter = 0;

int overflowPumpAutoModeEnabled = false;

void refreshOverflowPumpModeFromStorage() {
  overflowPumpAutoModeEnabled = isOverflowPumpAutoModeEnabledFromStorage();
  Serial.print("Overflow pump auto mode enabled: ");
  Serial.println(overflowPumpAutoModeEnabled);

  turnOffOverFlowPump();
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
      turnOnOverFlowPump();
    } else {
      turnOffOverFlowPump();
    }
    delayCounter = 0;
  }
  delayCounter++;
}

void turnOnOverFlowPump() {
  Serial.println("AUTO MODE - OVERFLOW PUNP ON");
  publish(MQTT_OVERFLOW_PUMP_TOPIC, ON_PAYLOAD);
  turnOnRelay2();
}

void turnOffOverFlowPump() {
  Serial.println("AUTO MODE - OVERFLOW PUNP OFF");
  publish(MQTT_OVERFLOW_PUMP_TOPIC, OFF_PAYLOAD);
  turnOffRelay2();
}