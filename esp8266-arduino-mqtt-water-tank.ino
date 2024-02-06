#include "mqtt_topics.h"
#include <ArduinoJson.h>
#include <WiFi.h>

#define VERSION "1.0.0"

const int sensorReadFrequencyMin = 1;

int loopCount = sensorReadFrequencyMin * 600;

void setup() {
  Serial.begin(115200);

  setupDistanceSensor();
  setupDs18b20();
  setupRelay();
  setupOverflowSensor();

  setupMqtt();
  mqttLoop();

  publishConnectivityHaDiscovery();
  publishWaterLevelDiscovery();
  publishPumpHaDiscovery();
  publishDs18b20HaDiscovery();
  publishSensorHeightDiscovery();
  publishOverflowSensorDiscovery();
  publishMaxWaterLevelDiscovery();
}

void loop() {
  mqttLoop();

  if (loopCount == sensorReadFrequencyMin * 600) {
    Serial.print("Connected Network Signal Strength (RSSI): ");
    Serial.println(WiFi.RSSI());
    loopCount = 0;
    readDs18b20();
    readDistance();
  }
  readOverflowSensor();

  loopCount++;
  delay(100);
}
