#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

const char* ssid     = "***";     // your network SSID (name of wifi network)
const char* password = "***"; // your network password

const char*  server = "***";  // Server URL
const char *topic = "***";
const char *mqtt_username = "***";
const char *mqtt_password = "***";
const int mqtt_port = 8883;

const char* test_root_ca=***;


WiFiClientSecure espClient;
PubSubClient client(espClient);

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  delay(100);

  WiFi.begin(ssid, password);

  // attempt to connect to Wifi network:
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    // wait 1 second for re-trying
    delay(1000);
  }

  Serial.print("Connected to ");
  Serial.println(ssid);

  espClient.setCACert(test_root_ca);
  

  Serial.println("\nStarting connection to server...");
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
      String client_id = "esp8266-client-";
      client_id += String(WiFi.macAddress());
      Serial.printf("The client %s connects to the public MQTT broker\n", client_id.c_str());
      if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
          Serial.println("Public EMQX MQTT broker connected");
      } else {
          Serial.print("Failed with state ");
          Serial.print(client.state());
          delay(2000);
      }
  }
    // if there are incoming bytes available
    // from the server, read them and print them:
    client.publish(topic, "hello emqx");
    client.subscribe(topic);
  }
}

void callback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message: ");
    String message;
    for (int i = 0; i < length; i++) {
        message += (char) payload[i];  // Convert *byte to string
    }
    Serial.print(message);
    if (message == "on" && !ledState) {
        digitalWrite(LED, HIGH);  // Turn on the LED
        ledState = true;
    }
    if (message == "off" && ledState) {
        digitalWrite(LED, LOW); // Turn off the LED
        ledState = false;
    }
    if (message == "blink") {
        digitalWrite(LED, LOW); // Turn off the LED
        delay(500);
        digitalWrite(LED, HIGH); // Turn off the LED
        delay(500);
        digitalWrite(LED, LOW); // Turn off the LED
        ledState = false;
    }
    Serial.println();
    Serial.println("-----------------------");
}

void loop() {
    client.loop();
    delay(100); // Delay for a short period in each loop iteration
}