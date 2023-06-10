#include "SH1106Wire.h"  //1.3寸用这个
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "DHT.h"
#include <Adafruit_NeoPixel.h>

#include "weatherIcon.h"
const int I2C_DISPLAY_ADDRESS = 0x3c;  //I2c地址默认


#define DHTPIN 5       //DHT11 DATA
#define DHTTYPE DHT11  //select DHT type
#define PIN 15
DHT dht(DHTPIN, DHTTYPE);

time_t now;                    //实例化时间
const int SDA_PIN = 32;        //引脚连接
const int SDC_PIN = 33;        //
char* ssid = "ASK4 Wireless";  // WIFI账户
char* password = "";           // WIFI密码
const unsigned char* Weather_Icon[] = { gImage_01, gImage_02, gImage_03, gImage_04, gImage_09, gImage_10, gImage_11, gImage_13, gImage_50 };
String Temperature = "";
String Wind = "";
String Weather = "";
String Icon = "";
int count = 0;


SH1106Wire display(I2C_DISPLAY_ADDRESS, SDA_PIN, SDC_PIN);  // 1.3寸用这个
HTTPClient http;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);

void setClock() {
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");

  Serial.print(F("Waiting for NTP time sync: "));
  time_t nowSecs = time(nullptr);
  while (nowSecs < 8 * 3600 * 2) {
    delay(500);
    Serial.print(F("."));
    yield();
    nowSecs = time(nullptr);
  }

  Serial.println();
  struct tm timeinfo;
  gmtime_r(&nowSecs, &timeinfo);
  Serial.print(F("Current time: "));
  Serial.print(asctime(&timeinfo));
}

const unsigned char* Match_icon(String Icon) {
  const unsigned char* I;
  if (Icon == "01d" || Icon == "01n") {
    I = gImage_01;
  } else if (Icon == "02d" || Icon == "02n") {
    I = gImage_02;
  } else if (Icon == "03d" || Icon == "03n") {
    I = gImage_03;
  } else if (Icon == "04d" || Icon == "04n") {
    I = gImage_04;
  } else if (Icon == "09d" || Icon == "09n") {
    I = gImage_09;
  } else if (Icon == "10d" || Icon == "10n") {
    I = gImage_10;
  } else if (Icon == "11d" || Icon == "11n") {
    I = gImage_11;
  } else if (Icon == "13d" || Icon == "13n") {
    I = gImage_13;
  } else if (Icon == "50d" || Icon == "50n") {
    I = gImage_50;
  } else {
    display.drawRect(10, 0, 32, 32);
  }
  return I;
}

void Get_Data() {
  //Serial.print("[HTTP] begin...\n");53.376016891378704, -1.476553439726451
  http.begin("http://api.openweathermap.org/data/2.5/weather?lat=53.3760&lon=-1.4765&appid=acc7c7aed8e6a9cb960f546b9778ab15&units=metric");  //HTTP

  //Serial.print("[HTTP] GET...\n");
  // start connection and send HTTP header
  int httpCode = http.GET();

  // httpCode will be negative on error
  if (httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    //Serial.printf("[HTTP] GET... code: %d\n", httpCode);

    // file found at server
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      DynamicJsonDocument doc(payload.length() * 2);  //解析的JSON数据大小
      // 重点3：反序列化数据
      deserializeJson(doc, payload);
      Temperature = doc["main"]["temp"].as<String>();
      if (Temperature.length() > 4) {
        String T = "";
        for (int i = 0; i < Temperature.indexOf(".") + 2; i++) {
          T = T + Temperature.charAt(i);
        }
        Temperature = T;
      }
      Weather = doc["weather"][0]["main"].as<String>();
      Wind = doc["wind"]["speed"].as<String>();
      Icon = doc["weather"][0]["icon"].as<String>();
    }
  } else {
    //Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    display.drawString(0, 0, http.errorToString(httpCode).c_str());
  }
  http.end();
}

void Set_LED(String Icon) {
  if (Icon == "01d" || Icon == "01n") {
    for (int i = 0; i < 8; i++) {
      int rnd = int(random(0, 5));
      pixels.setPixelColor(i, pixels.Color(RGB[0][rnd][0], RGB[0][rnd][1], RGB[0][rnd][2]));
      pixels.show();
    }
  } else if (Icon == "02d" || Icon == "02n") {
    for (int i = 0; i < 8; i++) {
      int rnd = int(random(0, 5));
      pixels.setPixelColor(i, pixels.Color(RGB[1][rnd][0], RGB[1][rnd][1], RGB[1][rnd][2]));
      pixels.show();
    }
  } else if (Icon == "03d" || Icon == "03n") {
    for (int i = 0; i < 8; i++) {
      int rnd = int(random(0, 5));
      pixels.setPixelColor(i, pixels.Color(RGB[2][rnd][0], RGB[2][rnd][1], RGB[2][rnd][2]));
      pixels.show();
    }
  } else if (Icon == "04d" || Icon == "04n") {
    for (int i = 0; i < 8; i++) {
      int rnd = int(random(0, 5));
      pixels.setPixelColor(i, pixels.Color(RGB[3][rnd][0], RGB[3][rnd][1], RGB[3][rnd][2]));
      pixels.show();
    }
  } else if (Icon == "09d" || Icon == "09n") {
    for (int i = 0; i < 8; i++) {
      int rnd = int(random(0, 5));
      pixels.setPixelColor(i, pixels.Color(RGB[4][rnd][0], RGB[4][rnd][1], RGB[4][rnd][2]));
      pixels.show();
    }
  } else if (Icon == "10d" || Icon == "10n") {
    for (int i = 0; i < 8; i++) {
      int rnd = int(random(0, 5));
      pixels.setPixelColor(i, pixels.Color(RGB[5][rnd][0], RGB[5][rnd][1], RGB[5][rnd][2]));
      pixels.show();
    }
  } else if (Icon == "11d" || Icon == "11n") {
    for (int i = 0; i < 8; i++) {
      int rnd = int(random(0, 5));
      pixels.setPixelColor(i, pixels.Color(RGB[6][rnd][0], RGB[6][rnd][1], RGB[6][rnd][2]));
      pixels.show();
    }
  } else if (Icon == "13d" || Icon == "13n") {
    for (int i = 0; i < 8; i++) {
      int rnd = int(random(0, 5));
      pixels.setPixelColor(i, pixels.Color(RGB[7][rnd][0], RGB[7][rnd][1], RGB[7][rnd][2]));
      pixels.show();
    }
  } else if (Icon == "50d" || Icon == "50n") {
    for (int i = 0; i < 8; i++) {
      int rnd = int(random(0, 5));
      pixels.setPixelColor(i, pixels.Color(RGB[8][rnd][0], RGB[8][rnd][1], RGB[8][rnd][2]));
      pixels.show();
    }
  } else {
    for (int i = 0; i < 8; i++) {
      int rnd = int(random(0, 5));
      pixels.setPixelColor(i, 0, 0, 0);
      pixels.show();
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  // 屏幕初始化
  display.init();
  display.clear();
  display.display();
  display.flipScreenVertically();  //屏幕翻转
  display.setContrast(255);        //屏幕亮度
  delay(200);

  Serial.print("Connect to WiFi");
  WiFi.begin(ssid, password);
  String Dot = ".";
  int counter = 0;
  while (WiFi.status() != WL_CONNECTED) {
    int n = 0;
    String Output = "Connecting ";
    delay(100);
    display.clear();
    while (n <= counter % 3) {
      Output += Dot;
      n++;
    }
    display.drawString(10, 10, Output);
    display.display();
    counter++;
  }
  Serial.print(WiFi.macAddress());
  display.clear();
  display.drawString(10, 10, "IP address:");
  display.drawString(10, 18, WiFi.localIP().toString().c_str());
  display.drawString(10, 26, "Setting time...");
  display.display();
  setClock();
  display.drawString(10, 34, "Setting sensor...");
  dht.begin();  //DHT11初始化
  delay(500);
  display.drawString(10, 41, "Loading weather...");
  Get_Data();
  delay(1000);
  display.display();
  delay(5000);
  pixels.begin();  // This initializes the NeoPixel library.
  pixels.setBrightness(100);
}

void loop() {
  if (count == 5000) {
    Get_Data();
    Serial.println("Refresh");
    count = 0;
  }
  if (count % 1000==0){
    Set_LED(Icon);
  }

  display.clear();
  display.setFont(ArialMT_Plain_10);
  display.drawXbm(10, 0, 40, 40, Match_icon(Icon));
  display.drawString(15, 41, Weather + "  |  Wind:" + Wind + "m/s");
  display.setFont(ArialMT_Plain_24);
  display.drawString(50, 10, Temperature + "°C");

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  String Current = String(temperature, 0) + "°C " + String(humidity, 0) + "%";
  display.setFont(ArialMT_Plain_10);
  display.drawString(80, 54, Current);

  now = time(nullptr);
  struct tm* timeInfo;
  timeInfo = localtime(&now);
  char buff[16];
  sprintf_P(buff, PSTR("%02d:%02d:%02d"), timeInfo->tm_hour + 1, timeInfo->tm_min, timeInfo->tm_sec);
  display.drawString(0, 54, String(buff));

  display.display();
  count += 1;
}
