
int loopCount = 0;

const int sensorReadFrequencyMin = 2;

void setup() {
  Serial.begin(115200);

  setupDistanceSensor();
  setupBme280();
  setupRelay();

  setupMqtt();
}

void loop() {
  mqttLoop();

  if (loopCount == sensorReadFrequencyMin * 600) {
    loopCount = 0;
    readBme280();
    readDistance();
  }

  loopCount++;
  delay(100);
}
