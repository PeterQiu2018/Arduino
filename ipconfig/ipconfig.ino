#include <WiFi.h>
 //WIFI名及密码
const char* ssid = "E05B";
const char* password =  "peter2000714";
    
void setup(){
  Serial.begin(115200);
 //默认参数连接WIFI
  WiFi.begin(ssid, password);
 //等待连接
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("Connecting...\n\n");
  }
 //IP地址
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  //子网掩码
  Serial.print("Subnet Mask: ");
  Serial.println(WiFi.subnetMask());
  //网关地址
  Serial.print("Gateway IP: ");
  Serial.println(WiFi.gatewayIP());
  //DNS
  Serial.print("DNS 1: ");
  Serial.println(WiFi.dnsIP(0));
  Serial.print("DNS 2: ");
  Serial.println(WiFi.dnsIP(1));
}
    
void loop(){}
