#include <EEPROM.h>

#define SENSOR_HEIGHT_ADDRESS 0
#define MAX_WATER_LEVEL_ADDRESS 0 + sizeof(int)

void persistSensorHeight(int sensorHeight) {
  EEPROM.begin(512);
  EEPROM.put(SENSOR_HEIGHT_ADDRESS, sensorHeight);
  EEPROM.end();
}

int getSensorHeight() {
  EEPROM.begin(512);
  int sensorHeight = 0;
  sensorHeight = EEPROM.get(SENSOR_HEIGHT_ADDRESS, sensorHeight);
  EEPROM.end();
  return sensorHeight;
}

void persistMaxWaterLevel(int maxWaterLevel) {
  EEPROM.begin(512);
  EEPROM.put(MAX_WATER_LEVEL_ADDRESS, maxWaterLevel);
  EEPROM.end();
}

int getMaxWaterLevel() {
  EEPROM.begin(512);
  int maxWaterLevel = 0;
  maxWaterLevel =  EEPROM.get(MAX_WATER_LEVEL_ADDRESS, maxWaterLevel);
  EEPROM.end();
  return maxWaterLevel;
}
