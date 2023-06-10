#include <WiFi.h>
//#include <ESP32Ping.h>

const char* ssid = "E05B";
const char* password =  "yourNetworkPass";
//IPAddress 类型变量
IPAddress staticIP(192, 168, 43, 223);
IPAddress gateway(192, 168, 43, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(192, 168, 43, 1);

void setup() {
  Serial.begin(115200);
  //传入参数静态IP地址,网关.DNS1,和2
  if (WiFi.config(staticIP, gateway, subnet, dns, dns) == false) {
    Serial.println("Configuration failed.");
  }
  //连接网络
  WiFi.begin(ssid, password);
  //等待连接
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("Connecting...\n\n");
  }
  //同上,打印网络参数
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("Subnet Mask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway IP: ");
  Serial.println(WiFi.gatewayIP());
  Serial.print("DNS 1: ");
  Serial.println(WiFi.dnsIP(0));
  Serial.print("DNS 2: ");
  Serial.println(WiFi.dnsIP(1));
}

void loop() {}
/*
   192.168.43.223
  Subnet Mask: 255.255.255.0
  Gateway IP: 192.168.43.1
  DNS 1: 192.168.43.1
*/
