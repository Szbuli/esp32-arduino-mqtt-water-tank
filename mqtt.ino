#include "credentials.h"

#include <WiFi.h>
#include "WiFiClientSecure.h"
#include <WiFiMulti.h>
#include <PubSubClient.h>

const char* ssid[] = WIFI_SSID;
const char* password[] = WIFI_PASSWD;

const int ssidCount = sizeof(ssid) / sizeof(ssid[0]);

WiFiClientSecure espClient;
PubSubClient client(espClient);
WiFiMulti WiFiMulti;

long lastMsg = 0;
char msg[50];
int value = 0;

void setupMqtt() {
  setup_wifi();

  espClient.setCACert(MQTT_CA_CERT);

  client.setServer(MQTT_HOST, MQTT_PORT);
  client.setCallback(callback);
}

void onWifiEvent(WiFiEvent_t event) {
  switch (event) {
    case WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_CONNECTED:
      Serial.println("Connected or reconnected to WiFi");
      break;
    case WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
      Serial.println("WiFi Disconnected. Enabling WiFi autoconnect");
      WiFi.reconnect();
      break;
    default: break;
  }
}

void setup_wifi() {

  delay(10);

  for (int i = 0; i < ssidCount; i++) {
    WiFiMulti.addAP(ssid[i], password[i]);
  }

  while (WiFiMulti.run() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  WiFi.onEvent(onWifiEvent);

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("Connected Network Signal Strength (RSSI): ");
  Serial.println(WiFi.RSSI()); /*Print WiFi signal strength*/
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void publish(char* topic, const char* payload) {
  client.publish(topic, payload);
}

void publishJson(char* topic, JsonDocument& doc, bool retained) {
  client.beginPublish(topic, measureJson(doc), retained);
  serializeJson(doc, client);
  client.endPublish();
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if (strcmp(topic, MQTT_PUMP_TOPIC) == 0) {
    if ((char)payload[1] == 'N') {
      turnOnRelay1();
    } else {
      turnOffRelay1();
    }
  } else if (!isOverflowPumpAutoModeEnabled() && strcmp(topic, MQTT_OVERFLOW_PUMP_TOPIC) == 0) {
    if ((char)payload[1] == 'N') {
      turnOnRelay2();
    } else {
      turnOffRelay2();
    }
  } else if (strcmp(topic, MQTT_SENSOR_HEIGHT_TOPIC) == 0) {
    payload[length] = '\0';
    persistSensorHeight(atoi((char*)payload));
    refreshMaxWaterLevelAndSensorHeightFromStorage();
  } else if (strcmp(topic, MQTT_MAX_WATER_LEVEL_TOPIC) == 0) {
    payload[length] = '\0';
    persistMaxWaterLevel(atoi((char*)payload));
    refreshMaxWaterLevelAndSensorHeightFromStorage();
  } else if (strcmp(topic, MQTT_OVERFLOW_PUMP_MODE_TOPIC) == 0) {
    persistOverflowPumpAutoMode((char)payload[0] == 'a');
    refreshOverflowPumpModeFromStorage();
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP32Client-";
    clientId += String(WiFi.macAddress());
    // Attempt to connect
    if (client.connect(clientId.c_str(), MQTT_USERNAME, MQTT_PASSWORD,
                       MQTT_STATUS_TOPIC, 0, true, OFFLINE_PAYLOAD)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(MQTT_STATUS_TOPIC, ONLINE_PAYLOAD, true);
      // ... and resubscribe
      client.subscribe(MQTT_PUMP_TOPIC);
      client.subscribe(MQTT_OVERFLOW_PUMP_TOPIC);
      client.subscribe(MQTT_SENSOR_HEIGHT_TOPIC);
      client.subscribe(MQTT_MAX_WATER_LEVEL_TOPIC);
      client.subscribe(MQTT_OVERFLOW_PUMP_MODE_TOPIC);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      char lastError[100];
      espClient.lastError(lastError, 100);
      Serial.println(lastError);
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void mqttLoop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
