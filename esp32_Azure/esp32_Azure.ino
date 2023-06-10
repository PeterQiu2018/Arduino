#include <WiFi.h>
#include <PubSubClient.h>
#include "Esp32MQTTClient.h"
 
const char* ssid = "E05B";
const char* password =  "peter2000714";
//const char* mqttServer = "Test-IoT2822.azure-devices.net";
const char* mqttServer = "51.142.192.34";
const int mqttPort = 1883;
String MQTTTopic;
String MQTTPayload;

//Azure IOT Hub Setup
static const char* connectionString = "HostName=Test-IoT2822.azure-devices.net;DeviceId=esp32;SharedAccessKey=z9gh/174ab4XpTmsv2xSMJquD3y6Vqn6RIVV1ot/oTw=";
static bool hasIoTHub = false;

//IP Setup
//IPAddress staticIP(192, 168, 43, 223);
//IPAddress gateway(192, 168, 43, 1);
//IPAddress subnet(255, 255, 255, 0);
//IPAddress dns(192, 168, 43, 1);
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void callback(char* topic, byte* payload, unsigned int length) {

  MQTTTopic = String("admin-room/temperature");
  MQTTPayload = ""; 
  for (int i = 0; i < length; i++) {
    // Serial.print((char)payload[i]); - Use for debugging
    MQTTPayload = String(MQTTPayload + (char)payload[i]);
  }
}



void MQTTConnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("MQTT : Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32Client")) {
      Serial.println("MQTT : Connected");
      // Once connected, publish an announcement...
      client.publish("stat/ESP32/IP_Address","31.205.206.172");
      //Subscribe to topics, one topic per line.
      client.subscribe("admin-room/temperature");      
    } else {
      Serial.print("MQTT : Failed to connect to MQTT , rc=");
      Serial.print(client.state());
      Serial.println("MQTT : Trying again to connect to MQTT in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  //Set baud rate
  Serial.begin(115200);
//  if (WiFi.config(staticIP, gateway, subnet, dns, dns) == false) {
//    Serial.println("Configuration failed.");
//  }
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("ESP32 : Connecting to WiFi...");
  }
  Serial.println("ESP32 : WiFi connected");
  Serial.println("ESP32 : IP address: ");
  Serial.println(WiFi.localIP());
  //Set MQTT details
  Serial.println("Setting server");
  client.setServer(mqttServer, mqttPort);
  Serial.println("Setting callback");
  client.setCallback(callback);
 
  //Connect to Azure IOT
  if (!Esp32MQTTClient_Init((const uint8_t*)connectionString))
  {
    hasIoTHub = false;
    Serial.println("Azure IoT Hub : Initializing IoT hub failed.");
    return;
  }else{
    Serial.println("Azure IoT Hub : Initializing IoT hub success.");
  }
  hasIoTHub = true;
 
}

void loop() {
   //Connect to MQTT and reconnect if connection drops
   if (!client.connected()) {
     MQTTConnect();
   }
   //Respond to messages received
   if (MQTTTopic != "") { 
      Serial.println("MQTT : Topic is [" + MQTTTopic +"]");
      Serial.println("MQTT : Payload is [" + MQTTPayload + "]");
      AzureIoTHub(); 
  }
  client.loop();
}

void AzureIoTHub() {
  if (hasIoTHub)
      {
        String tempString;
        tempString = "{" + MQTTTopic + ":" + MQTTPayload + "}";
        if (Esp32MQTTClient_SendEvent(tempString.c_str()))
        {
          Serial.println("Azure IoT Hub : Sending data to Azure IoT Hub succeed");
        }
        else
        {
          Serial.println("Azure IoT Hub : Failure...");
        }
      MQTTPayload = "";
      MQTTTopic = "";

   }
}
