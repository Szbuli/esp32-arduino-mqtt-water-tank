#include "credentials.h"

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <PubSubClient.h>

const char* ssid[] = WIFI_SSID;
const char* password[] = WIFI_PASSWD;
const char* mqtt_server = MQTT_HOST;
const int ssidCount = sizeof(ssid) / sizeof(ssid[0]);

WiFiClient espClient;
PubSubClient client(espClient);
ESP8266WiFiMulti WiFiMulti;

long lastMsg = 0;
char msg[50];
int value = 0;

void setupMqtt() {
  setup_wifi();

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
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

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if (strcmp(topic, "watertank/set/pump") == 0) {
    if ((char)payload[0] == '1') {
      turnOnRelay();
    } else {
      turnOffRelay();
    }
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), "smarthome", "smarthome")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("watertank/set/pump");
      client.subscribe("watertank/status/pump");
      client.subscribe("watertank/status/waterlevel");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
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
