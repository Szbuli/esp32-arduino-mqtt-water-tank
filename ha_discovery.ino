
StaticJsonDocument<200> device;


void publishDs18b20HaDiscovery() {
  StaticJsonDocument<200> doc;
  doc["name"] = "Water temperature";
  doc["availability_topic"] = MQTT_STATUS_TOPIC;
  doc["device_class"] = "temperature";
  doc["state_topic"] = MQTT_WATER_TEMP_TOPIC;
  doc["unique_id"] = MQTT_WATER_TEMP_TOPIC;
  doc["unit_of_measurement"] = "°C";

  addDeviceConfig(doc);

  publishJson(MQTT_HA_DISCOVERY_WATER_TEMP_TOPIC, doc, true);
}

void publishConnectivityHaDiscovery() {
  StaticJsonDocument<200> doc;
  doc["name"] = "Status";
  doc["availability_topic"] = MQTT_STATUS_TOPIC;
  doc["device_class"] = "connectivity";
  doc["state_topic"] = MQTT_STATUS_TOPIC;
  doc["unique_id"] = MQTT_STATUS_TOPIC;
  doc["payload_on"] = ONLINE_PAYLOAD;
  doc["payload_off"] = OFFLINE_PAYLOAD;

  addDeviceConfig(doc);

  publishJson(MQTT_HA_DISCOVERY_CONNECTIVITY_TOPIC, doc, true);
}

void publishWaterLevelDiscovery() {
  StaticJsonDocument<200> doc;
  doc["name"] = "Water level";
  doc["availability_topic"] = MQTT_STATUS_TOPIC;
  doc["state_topic"] = MQTT_WATER_LEVEL_TOPIC;
  doc["unique_id"] = MQTT_WATER_LEVEL_TOPIC;
  doc["unit_of_measurement"] = "%";

  addDeviceConfig(doc);

  publishJson(MQTT_HA_DISCOVERY_WATER_LEVEL_TOPIC, doc, true);
}

void publishSensorHeightDiscovery() {
  StaticJsonDocument<400> doc;
  doc["name"] = "Water level sensor height";
  doc["availability_topic"] = MQTT_STATUS_TOPIC;
  doc["device_class"] = "distance";
  doc["state_topic"] = MQTT_SENSOR_HEIGHT_TOPIC;
  doc["command_topic"] = MQTT_SENSOR_HEIGHT_TOPIC;
  doc["unique_id"] = MQTT_SENSOR_HEIGHT_TOPIC;
  doc["unit_of_measurement"] = "cm";
  doc["max"] = 200;
  doc["entity_category"] = "config";
  doc["retain"] = true;

  addDeviceConfig(doc);

  publishJson(MQTT_HA_DISCOVERY_SENSOR_LEVEL_TOPIC, doc, true);
}

void publishOverflowSensorDiscovery() {
  StaticJsonDocument<400> doc;
  doc["name"] = "Overflow sensor";
  doc["availability_topic"] = MQTT_STATUS_TOPIC;
  doc["state_topic"] = MQTT_OVERFLOW_SENSOR_TOPIC;
  doc["unique_id"] = MQTT_OVERFLOW_SENSOR_TOPIC;

  addDeviceConfig(doc);

  publishJson(MQTT_HA_DISCOVERY_OVERFLOW_SENSOR_LEVEL_TOPIC, doc, true);
}

void publishMaxWaterLevelDiscovery() {
  StaticJsonDocument<400> doc;
  doc["name"] = "Maximum water level";
  doc["availability_topic"] = MQTT_STATUS_TOPIC;
  doc["state_topic"] = MQTT_MAX_WATER_LEVEL_TOPIC;
  doc["command_topic"] = MQTT_MAX_WATER_LEVEL_TOPIC;
  doc["unique_id"] = MQTT_MAX_WATER_LEVEL_TOPIC;
  doc["unit_of_measurement"] = "cm";
  doc["max"] = 200;
  doc["entity_category"] = "config";
  doc["retain"] = true;

  addDeviceConfig(doc);

  publishJson(MQTT_HA_DISCOVERY_MAX_WATER_LEVEL__TOPIC, doc, true);
}

void publishPumpHaDiscovery() {
  StaticJsonDocument<200> doc;
  doc["name"] = "Pump";
  doc["availability_topic"] = MQTT_STATUS_TOPIC;
  doc["icon"] = "mdi:water-pump";
  doc["unique_id"] = MQTT_PUMP_TOPIC;
  doc["command_topic"] = MQTT_PUMP_TOPIC;

  addDeviceConfig(doc);

  publishJson(MQTT_HA_DISCOVERY_PUMP_TOPIC, doc, true);
}

void publishOverflowPumpHaDiscovery() {
  StaticJsonDocument<200> doc;
  doc["name"] = "Overflow pump";
  doc["availability_topic"] = MQTT_STATUS_TOPIC;
  doc["icon"] = "mdi:water-pump";
  doc["unique_id"] = MQTT_OVERFLOW_PUMP_TOPIC;
  doc["command_topic"] = MQTT_OVERFLOW_PUMP_TOPIC;

  addDeviceConfig(doc);

  publishJson(MQTT_HA_DISCOVERY_OVERFLOW_PUMP_TOPIC, doc, true);
}

void addDeviceConfig(JsonDocument& doc) {
  JsonObject device = doc.createNestedObject("device");
  device["sw_version"] = VERSION;
  device["manufacturer"] = "zbl";
  device["identifiers"] = "water-tank";
  device["name"] = "Water tank";
  device["model"] = "Water tank";
}
