#include <OneWire.h>
#include <DallasTemperature.h>


#define ONE_WIRE_BUS 4 // D2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
float temperature;

void setupDs18b20() {
  sensors.begin();
}

void readDs18b20() {
  sensors.requestTemperatures();

  temperature = sensors.getTempCByIndex(0);
  if (temperature == DEVICE_DISCONNECTED_C) {
    Serial.println("Error: Could not read temperature data");
    publish(MQTT_WATER_TEMP_TOPIC, NULL);
    return;
  }

  publish(MQTT_WATER_TEMP_TOPIC, String(temperature).c_str());
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println("*C");

}
