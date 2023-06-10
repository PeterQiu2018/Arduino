#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <HTTPClient.h>

HTTPClient http;

const char* ssid = "E05B";
const char* password = "peter2000714";

WebServer server(80);

const int led = 2;

String HTML = "<!DOCTYPE html><html> <head>    <meta charset=\"utf-8\">    <title>interface</title>  </head> <body>    <a href=\"./pin?light=on\"><input type=\"button\" value=\"TurnOn\"></a>   <a href=\"./pin?light=off\"><input type=\"button\" value=\"TurnOff\"></a>   <a href=\"./pin?light=click\"><input type=\"button\" value=\"Click\"></a> </body></html>";
//./pin?light=on  ./pin?light=off
void pin() {
  if (server.arg("light") == "on") {
    digitalWrite(led, HIGH);
    server.send(200, "text/html", HTML);
    Serial.println("On");
  } else if (server.arg("light") == "off") {
    digitalWrite(led, LOW);
    server.send(200, "text/html", HTML);
    Serial.println("Off");
  } else if (server.arg("light") == "click") {
    digitalWrite(led, HIGH);
    digitalWrite(2, HIGH);
    delay(100);
    digitalWrite(led, LOW);
    digitalWrite(2, LOW);
    server.send(200, "text/html", HTML);
    Serial.println("Click");
  }
}

void send_data() {
  String pageData="";
  http.begin("http://51.142.192.34:8080/U2172822/superadmin/listrecord");
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK) {
    pageData = http.getString();
  }
  Serial.println(pageData);
}

void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/html", HTML);
  digitalWrite(led, 0);
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  server.send(404, "text/plain", message);
}

void setup(void) {
  digitalWrite(led, LOW);
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
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

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/pin", HTTP_GET, pin);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");

}
void loop(void) {
  server.handleClient();
}
