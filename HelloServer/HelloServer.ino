#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FastLED.h>
#include "DHTesp.h" // Click here to get the library: http://librarymanager/All#DHTesp

#ifdef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP8266 ONLY!)
#error Select ESP8266 board.
#endif

DHTesp dht;

const char* ssid = "E05B";
const char* password = "peter2000714";

ESP8266WebServer server(80);

String HTML_head = "<!DOCTYPE html><html><head><meta charset=\"utf-8\"><title>interface</title></head><body>";
String HTML_tail = "</body></html>";
String HTML="";
String State="";
String Humidity="";
String Temperature="";
String HeatIndex="";


void handleRoot() {
  server.send(200, "text/html", HTML);
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  server.send(404, "text/plain", message);
}

void setup(void) {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.macAddress());

  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");

  Serial.begin(115200);
  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)\tHeatIndex (C)\t(F)");
  String thisBoard= ARDUINO_BOARD;
  Serial.println(thisBoard);

  // Autodetect is not working reliable, don't use the following line
  // dht.setup(17);
  // use this instead: 
  dht.setup(2, DHTesp::DHT11); // Connect DHT sensor to GPIO 17
}

void loop(void) {
  server.handleClient();
  delay(dht.getMinimumSamplingPeriod());

  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

  State=dht.getStatusString();
  Humidity=humidity;
  Temperature=temperature;
  HeatIndex=dht.computeHeatIndex(temperature, humidity, false);
  delay(2000);
  HTML=HTML_head+"<a "+State+">"+"<a "+Humidity+">"+"<a "+Temperature+">"+"<a "+HeatIndex+">"+HTML_tail;
  Serial.print(HTML);
}
