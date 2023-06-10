#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
//#include <WiFi.h>

#ifndef STASSID
#define STASSID "E05B"
#define STAPSK  "peter2000714"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;
String HTML = "<!DOCTYPE html><html> <head>    <meta charset=\"utf-8\">    <title>interface</title>  </head> <body>    <a href=\"./pin?light=on\"><input type=\"button\" value=\"TurnOn\"></a>   <a href=\"./pin?light=off\"><input type=\"button\" value=\"TurnOff\"></a> </body></html>";

ESP8266WebServer server(80);
//IPAddress 类型变量
//IPAddress staticIP(192, 168, 43, 223);
//IPAddress gateway(192, 168, 43, 1);
//IPAddress subnet(255, 255, 255, 0);
//IPAddress dns(192, 168, 43, 1);


const int led = 2;

void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/html", HTML);
  digitalWrite(led, 0);
}

void pin(){
  if (server.arg("light")=="on"){
    digitalWrite(led,HIGH);
    server.send(200,"text/html",HTML);
    Serial.println("On");
  }else if(server.arg("light")=="off"){
    digitalWrite(led,LOW);
    server.send(200,"text/html",HTML);
    Serial.println("Off");
  }else {
    digitalWrite(led,HIGH);
    delay(100);
    digitalWrite(led,LOW);
    server.send(200,"text/html",HTML);
    Serial.println("Click");
  }
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

void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  //setting web config
//  if (WiFi.config(staticIP, gateway, subnet, dns, dns) == false) {
//    Serial.println("Configuration failed.");
//  }
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

  server.on("/", handleRoot);
  server.on("/pin", HTTP_GET, pin);
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}
