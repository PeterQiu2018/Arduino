#include "DHTesp.h" // Click here to get the library: http://librarymanager/All#DHTesp
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifdef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP8266 ONLY!)
#error Select ESP8266 board.
#endif
#ifndef STASSID
#define STASSID "E05B"
#define STAPSK  "peter2000714"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;
const int led = 13;

ESP8266WebServer server(80);
DHTesp dht;

String HTML_head="<!DOCTYPE html><html><head><meta charset=\"utf-8\"><title>interface</title></head><body><a>";
String HTML_bottom="<a></a></body></html>";
String HTML="";

void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/html", HTML);
  digitalWrite(led, 0);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}



void setup()
{
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);
  
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)\tHeatIndex (C)\t(F)");
  String thisBoard= ARDUINO_BOARD;
  Serial.println(thisBoard);

  // Autodetect is not working reliable, don't use the following line
  // dht.setup(17);
  // use this instead: 
  dht.setup(2, DHTesp::DHT11); // Connect DHT sensor to GPIO 17

  server.begin();
  Serial.println("HTTP server started");
 }

void loop()
{
  server.handleClient();
  
  delay(dht.getMinimumSamplingPeriod());

  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

//  Serial.print(dht.getStatusString());
//  Serial.print("\t");
//  Serial.print(humidity, 1);
//  Serial.print("\t\t");
//  Serial.print(temperature, 1);
//  Serial.print("\t\t");
//  Serial.print(dht.toFahrenheit(temperature), 1);
//  Serial.print("\t\t");
//  Serial.print(dht.computeHeatIndex(temperature, humidity, false), 1);
//  Serial.print("\t\t");
//  Serial.println(dht.computeHeatIndex(dht.toFahrenheit(temperature), humidity, true), 1);
  HTML=HTML_head+temperature+"</a><a>"+humidity+HTML_bottom;
  delay(2000);
}
