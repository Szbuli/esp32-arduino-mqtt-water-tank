#include "credentials.h"

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <PubSubClient.h>

const char* ssid[] = WIFI_SSID;
const char* password[] = WIFI_PASSWD;

const int ssidCount = sizeof(ssid) / sizeof(ssid[0]);
const char* ONLINE_PAYLOAD = "online";
const char* OFFLINE_PAYLOAD = "offline";
const char* STATUS_TOPIC = "smarthome/watertank/status";
const char* PUMP_TOPIC = "smarthome/watertank/pump/set";

X509List caCertX509(MQTT_CA_CERT);
WiFiClientSecure espClient;
PubSubClient client(espClient);
ESP8266WiFiMulti WiFiMulti;

long lastMsg = 0;
char msg[50];
int value = 0;

void setupMqtt() {
  setup_wifi();

  espClient.setTrustAnchors(&caCertX509);
  espClient.allowSelfSignedCerts();
  espClient.setFingerprint(MQTT_CERT_FINGERPRINT);

  client.setServer(MQTT_HOST, MQTT_PORT);
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

void publish(char* topic, const char* payload) {
  client.publish(topic, payload);
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if (strcmp(topic, PUMP_TOPIC) == 0) {
    if ((char)payload[1] == 'N') {
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
    if (client.connect(clientId.c_str(), MQTT_USERNAME, MQTT_PASSWORD,
                       STATUS_TOPIC, 0, true, OFFLINE_PAYLOAD)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(STATUS_TOPIC, ONLINE_PAYLOAD, true);
      // ... and resubscribe
      client.subscribe(PUMP_TOPIC);
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
