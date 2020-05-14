#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme;

#define LIST_SIZE 3

bool bme280Status;

float temperature, humidity;

float temperatureList[LIST_SIZE] = { -1000, -1000, -1000};
float humidityList[LIST_SIZE] = { -1000, -1000, -1000};

int avgListCounter = 0;

void setupBme280() {
  bme280Status = bme.begin(0x76);
  if (!bme280Status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
  } else {
    Serial.println("Found a valid BME280 sensor");
  }

}

float getAvg(int list[], const int size) {
  float avg = 0;
  int numberOfElements = 0;
  for (int i = 0; i < size; i++) {
    if (list[i] < -1000) {
      continue;
    }
    numberOfElements++;
    avg += list[i];
    printf("%u\n", list[i]);
  }
}

void readBme280() {
  temperatureList[avgListCounter] = bme.readTemperature();
  humidityList[avgListCounter] = bme.readHumidity();


  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println("*C");

  Serial.print("Humidity = ");
  Serial.print(humidity);
  Serial.println("%");

  Serial.println();


}
