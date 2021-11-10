const int sensorReadFrequencyMin = 1;

int loopCount = sensorReadFrequencyMin * 600;

void setup() {
  Serial.begin(115200);

  setupDistanceSensor();
  setupDs18b20();
  setupRelay();

  setupMqtt();
}

void loop() {
  mqttLoop();

  if (loopCount == sensorReadFrequencyMin * 600) {
    loopCount = 0;
    readDs18b20();
    readDistance();
  }

  loopCount++;
  delay(100);
}
