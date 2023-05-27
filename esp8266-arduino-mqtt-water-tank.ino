#include "mqtt_topics.h"
#include <ArduinoJson.h>

#define VERSION "1.0.0"

const int sensorReadFrequencyMin = 1;

int loopCount = sensorReadFrequencyMin * 600;

void setup() {
  Serial.begin(115200);

  setupDistanceSensor();
  setupDs18b20();
  setupRelay();

  setupMqtt();
  mqttLoop();

  publishConnectivityHaDiscovery();
  publishWaterLevelDiscovery();
  publishPumpHaDiscovery();
  publishDs18b20HaDiscovery();
  publishSensorHeightDiscovery();
  publishMaxWaterLevelDiscovery();
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
