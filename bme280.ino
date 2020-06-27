#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme;

bool bme280Status;

float temperature, humidity;

void setupBme280() {
  bme280Status = bme.begin(0x76);
  if (!bme280Status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
  } else {
    Serial.println("Found a valid BME280 sensor");
  }

}

void readBme280() {
  temperature = bme.readTemperature();
  humidity = bme.readHumidity();



  publish("smarthome/watertank/temperature", String(temperature).c_str());
  publish("smarthome/watertank/humidity", String(humidity).c_str());
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println("*C");

  Serial.print("Humidity = ");
  Serial.print(humidity);
  Serial.println("%");

  Serial.println();


}
