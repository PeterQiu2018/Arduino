#include "DHT.h"
#include <Arduino.h>
#include "SH1106Wire.h"

#define DHTPIN 5   //DHT11 DATA 
#define DHTTYPE DHT11  //select DHT type
DHT dht(DHTPIN, DHTTYPE);


const int I2C_DISPLAY_ADDRESS = 0x3c;  //I2c地址默认
#if defined(ESP32)
const int SDA_PIN = 32;  //引脚连接
const int SDC_PIN = 33;  //
#endif

SH1106Wire     display(I2C_DISPLAY_ADDRESS, SDA_PIN, SDC_PIN);   // 1.3寸用这个

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");
  dht.begin();//DHT11初始化
  delay(1000);
  // 屏幕初始化
  display.init();
  display.flipScreenVertically(); //屏幕翻转
  display.setContrast(255); //屏幕亮度
  display.clear();
  display.display();
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  display.clear();
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  String Current=String(temperature,0)+"°C | "+String(humidity,0)+"%";
  display.drawString(0, 0, Current);
  display.display();
  delay(500);
}
