#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

char* ssid = "XIAOMI";  // WIFI账户
char* password = "fhe87gh2vp1";           // WIFI密码

// IPAddress local_IP(192, 168, 137, 15);
// IPAddress gateway(192, 168, 137, 1);
// IPAddress subnet(255, 255, 0, 0);

ESP8266WebServer server(80);

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
    delay(100);
    digitalWrite(led, LOW);
    server.send(200, "text/html", HTML);
    Serial.println("Click");
  }
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
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  // if (!WiFi.config(local_IP, gateway, subnet)) {
  //   Serial.println("STA Failed to configure");
  // }
  
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
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");

}
void loop(void) {
  server.handleClient();
}

