#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define LED 2

// WiFi
char* ssid = "***";  // WIFI账户
char* password = "***";           // WIFI密码


// MQTT Broker
const char *mqtt_broker = "***";
const char *topic = "***";
const char *mqtt_username = "***";
const char *mqtt_password = "***";
const int mqtt_port = 8883;
// const char *fingerprint = "***";
bool ledState = false;

WiFiClientSecure espClient;
PubSubClient client(espClient);


void setup() {
  // Set software serial baud to 115200;
  Serial.begin(115200);
  // connecting to a WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to the WiFi network");

  // connecting to a mqtt broker
  espClient.setFingerprint(fingerprint);
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
    String client_id = "esp8266-client-Shenzhen";
    Serial.printf("The client %s connects to the mqtt broker\n", client_id.c_str());
    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
        Serial.println("Connected to MQTT broker.");
        client.subscribe(topic);
    } else {
        Serial.print("Failed to connect to MQTT broker, rc=");
        Serial.print(client.state());
        Serial.println(" Retrying in 5 seconds.");
        delay(5000);
    }
  }
  client.publish(topic, "Hi EMQX I'm ESP8266 ^^");
}

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    for (int i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
    }
    Serial.println();
    Serial.println("-----------------------");
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Reconnecting to MQTT broker...");
    String client_id = "esp8266-client-";
    client_id += String(WiFi.macAddress());
    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
        Serial.println("Reconnected to MQTT broker.");
        client.subscribe(topic);
    } else {
        Serial.print("Failed to reconnect to MQTT broker, rc=");
        Serial.print(client.state());
        Serial.println("Retrying in 5 seconds.");
        delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}