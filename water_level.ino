int waterLevelInPercentage;

int maxWaterLevel = 0;
int sensorHeight = 0;

void setupDistanceSensor() {
  Serial2.begin(9600, SERIAL_8N1, 16, 17);

  refreshMaxWaterLevelAndSensorHeightFromStorage();
}

void refreshMaxWaterLevelAndSensorHeightFromStorage() {
  maxWaterLevel = getMaxWaterLevel();
  Serial.print("Loaded max water level [cm]: ");
  Serial.println(maxWaterLevel);

  sensorHeight = getSensorHeight();
  Serial.print("Loaded sensor height [cm]: ");
  Serial.println(sensorHeight);
}

void readDistance() {
  Serial2.write(0x01);

  delay(50);
  if (Serial2.available()) {
    getDistance();
  }
}

void getDistance() {
  unsigned int distance;
  byte startByte, h_data, l_data, sum = 0;
  byte buf[3];

  startByte = (byte)Serial2.read();
  if (startByte == 255) {
    Serial2.readBytes(buf, 3);
    h_data = buf[0];
    l_data = buf[1];
    sum = buf[2];

    distance = ((h_data << 8) + l_data) / 10;
    //if (((h_data + l_data) & 0xFF) != sum) { // sum is sent incorrectly
    while (Serial2.available()) { Serial2.read(); }
    Serial.print("Water distance from sensor [cm]: ");
    Serial.println(distance);

    waterLevelInPercentage = round((sensorHeight - distance) / (float)maxWaterLevel * 100);
    publish(MQTT_WATER_LEVEL_TOPIC, String(waterLevelInPercentage).c_str());
    publish(MQTT_SENSOR_MEASURED_DISTANCE_TOPIC, String(distance).c_str());
  } else {
    while (Serial2.available()) { Serial2.read(); }
    Serial.println("Invalid start byte");
  };
}