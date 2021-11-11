
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
  doc["name"] = "Waterlevel";
  doc["availability_topic"] = MQTT_STATUS_TOPIC;
  doc["state_topic"] = MQTT_WATERLEVEL_TOPIC;
  doc["unique_id"] = MQTT_WATERLEVEL_TOPIC;
  doc["unit_of_measurement"] = "%";

  addDeviceConfig(doc);

  publishJson(MQTT_HA_DISCOVERY_WATERLEVEL_TOPIC, doc, true);
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

void addDeviceConfig(JsonDocument& doc) {
  JsonObject device = doc.createNestedObject("device");
  device["sw_version"] = VERSION;
  device["manufacturer"] = "zbl";
  device["identifiers"] = "water-tank";
  device["name"] = "Water tank";
  device["model"] = "Water tank";
}
