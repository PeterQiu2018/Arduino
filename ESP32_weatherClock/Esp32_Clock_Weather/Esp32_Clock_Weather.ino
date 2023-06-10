#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

#include <time.h>
#include <sys/time.h>
//#include <coredecls.h>

#include "SH1106Wire.h"   //1.3寸用这个
#include "OLEDDisplayUi.h"
#include "HeFeng.h"
#include "WeatherStationFonts.h"

const int I2C_DISPLAY_ADDRESS = 0x3c;  //I2c地址默认
const int SDA_PIN = 32;  //引脚连接
const int SDC_PIN = 33;  //
SH1106Wire display(I2C_DISPLAY_ADDRESS, SDA_PIN, SDC_PIN);   // 1.3寸用这个

const char* ssid     = "E05B";     // WIFI账户
const char* password = "peter2000714"; // WIFI密码

const String API_Key = "acc7c7aed8e6a9cb960f546b9778ab15";
const String Value_lat = "53.63";
const String Value_lon = "-1.77";
char* Current_Weather = "https://api.openweathermap.org/data/2.5/weather?lat=53.63&lon=-1.77&appid=acc7c7aed8e6a9cb960f546b9778ab15";
char* Forecast_Weather = "https://api.openweathermap.org/data/2.5/forecast?lat=53.63&lon=-1.77&appid=acc7c7aed8e6a9cb960f546b9778ab15";

#define TZ              0      // 中国时区为8
#define DST_MN          0      // 默认为0

const int UPDATE_INTERVAL_SECS = 10 * 60; // 10钟更新一次天气
SH1106Wire     display(I2C_DISPLAY_ADDRESS, SDA_PIN, SDC_PIN);
OLEDDisplayUi   ui( &display );

HeFengCurrentData currentWeather; //实例化对象
HeFengForeData foreWeather[3];
HeFeng HeFengClient;

time_t now; //实例化时间

#define TZ_MN           ((TZ)*60)   //时间换算
#define TZ_SEC          ((TZ)*3600)
#define DST_SEC         ((DST_MN)*60)

bool readyForWeatherUpdate = false; // 天气更新标志
bool first = true;  //首次更新标志
long timeSinceLastWUpdate = 0;    //上次更新后的时间
long timeSinceLastCurrUpdate = 0;   //上次天气更新后的时间

FrameCallback frames[] = { drawDateTime, drawCurrentWeather, drawForecast };
//页面数量
int numberOfFrames = 3;

OverlayCallback overlays[] = { drawHeaderOverlay }; //覆盖回调函数
int numberOfOverlays = 1;  //覆盖数

//void setClock() {
//  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
//
//  Serial.print(F("Waiting for NTP time sync: "));
//  time_t nowSecs = time(nullptr);
//  while (nowSecs < 8 * 3600 * 2) {
//    delay(500);
//    Serial.print(F("."));
//    yield();
//    nowSecs = time(nullptr);
//  }
//
//  Serial.println();
//  struct tm timeinfo;
//  gmtime_r(&nowSecs, &timeinfo);
//  Serial.print(F("Current time: "));
//  Serial.print(asctime(&timeinfo));
//}


void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  // 屏幕初始化
  display.init();
  display.clear();
  display.display();
  display.flipScreenVertically(); //屏幕翻转
  display.setContrast(255); //屏幕亮度
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
  Serial.print("Success!");
  display.clear();
  display.drawString(10, 10, "IP address:");
  display.drawString(10, 18, WiFi.localIP().toString().c_str());
  display.display();
  delay(5000);

  //UI配置
  ui.setTargetFPS(30);  //刷新频率
  ui.setActiveSymbol(activeSymbole); //设置活动符号
  ui.setInactiveSymbol(inactiveSymbole); //设置非活动符号
  ui.setIndicatorPosition(BOTTOM);  // 符号位置
  ui.setIndicatorDirection(LEFT_RIGHT);  // 定义第一帧在栏中的位置
  ui.setFrameAnimation(SLIDE_LEFT);  // 屏幕切换方向
  ui.setFrames(frames, numberOfFrames); // 设置框架
  ui.setTimePerFrame(5000); //设置切换时间
  ui.setOverlays(overlays, numberOfOverlays); //设置覆盖

  // UI负责初始化显示
  ui.init();
  display.flipScreenVertically(); //屏幕反转

  configTime(TZ_SEC, DST_SEC, "ntp.ntsc.ac.cn", "pool.ntp.org"); //ntp获取时间
}

void loop() {
  if (first) {  //首次加载
    updateDatas(&display);
    first = false;
  }
  if (millis() - timeSinceLastWUpdate > (1000L * UPDATE_INTERVAL_SECS)) { //屏幕刷新
    setReadyForWeatherUpdate();
    timeSinceLastWUpdate = millis();
  }
  if (readyForWeatherUpdate && ui.getUiState()->frameState == FIXED) { //天气更新
    updateData(&display);
  }

  int remainingTimeBudget = ui.update(); //剩余时间预算

  if (remainingTimeBudget > 0) {
    //你可以在这里工作如果你低于你的时间预算。
    delay(remainingTimeBudget);
  }
}


void drawProgress(OLEDDisplay *display, int percentage, String label) {    //绘制进度
  display->clear();
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->setFont(ArialMT_Plain_10);
  display->drawString(64, 10, label);
  display->drawProgressBar(2, 28, 124, 10, percentage);
  display->display();
}

void updateData(OLEDDisplay *display) {  //天气更新
  HeFengClient.doUpdateCurr(&currentWeather, API_Key, Value_lat, Value_lon);
  HeFengClient.doUpdateFore(foreWeather, API_Key, Value_lat, Value_lon);
  readyForWeatherUpdate = false;
}

void updateDatas(OLEDDisplay *display) {  //首次天气更新
  
  drawProgress(display, 33, "Updating weather...");
  HeFengClient.doUpdateCurr(&currentWeather, API_Key, Value_lat, Value_lon);
  
  drawProgress(display, 66, "Updating forecasts...");
  HeFengClient.doUpdateFore(foreWeather, API_Key, Value_lat, Value_lon);
  
  readyForWeatherUpdate = false;
  drawProgress(display, 100, "Done...");
  delay(200);
}

void drawDateTime(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {  //显示时间
  now = time(nullptr);
  struct tm* timeInfo;
  timeInfo = localtime(&now);
  char buff[16];

  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->setFont(ArialMT_Plain_16);
  String date = WDAY_NAMES[timeInfo->tm_wday];

  sprintf_P(buff, PSTR("%04d-%02d-%02d  %s"), timeInfo->tm_year + 1900, timeInfo->tm_mon + 1, timeInfo->tm_mday, WDAY_NAMES[timeInfo->tm_wday].c_str());
  display->drawString(64 + x, 5 + y, String(buff));
  display->setFont(ArialMT_Plain_24);

  sprintf_P(buff, PSTR("%02d:%02d:%02d"), timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec);
  display->drawString(64 + x, 22 + y, String(buff));
  display->setTextAlignment(TEXT_ALIGN_LEFT);
}

void drawCurrentWeather(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {  //显示天气
  display->setFont(ArialMT_Plai-n_10);
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->drawString(64 + x, 38 + y, currentWeather.weather + "    |   Wind: " + currentWeather.windSpeed + "  ");

  display->setFont(ArialMT_Plain_24);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  String temp = currentWeather.temp + "°C" ;
  display->drawString(60 + x, 3 + y, temp);
  display->setFont(ArialMT_Plain_10);
  display->drawString(62 + x, 26 + y, currentWeather.temp + "°C | " + currentWeather.humidity + "%");
  display->setFont(Meteocons_Plain_36);
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->drawString(32 + x, 0 + y, currentWeather.icon);
}

void drawForecast(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {  //天气预报
  drawForecastDetails(display, x, y, 0);
  drawForecastDetails(display, x + 44, y, 1);
  drawForecastDetails(display, x + 88, y, 2);
}


void drawForecastDetails(OLEDDisplay *display, int x, int y, int dayIndex) {  //天气预报

  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->setFont(ArialMT_Plain_10);
  display->drawString(x + 20, y, foreWeather[dayIndex].datestr);
  display->setFont(Meteocons_Plain_21);
  display->drawString(x + 20, y + 12, foreWeather[dayIndex].iconMeteoCon);

  String temp = foreWeather[dayIndex].tmp_min + " | " + foreWeather[dayIndex].tmp_max;
  display->setFont(ArialMT_Plain_10);
  display->drawString(x + 20, y + 34, temp);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
}

void drawHeaderOverlay(OLEDDisplay *display, OLEDDisplayUiState* state) {   //绘图页眉覆盖
  now = time(nullptr);
  struct tm* timeInfo;
  timeInfo = localtime(&now);
  char buff[14];
  sprintf_P(buff, PSTR("%02d:%02d"), timeInfo->tm_hour, timeInfo->tm_min);

  display->setColor(WHITE);
  display->setFont(ArialMT_Plain_10);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawString(6, 54, String(buff));
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  String temp = fans;
  display->drawString(122, 54, temp);
  display->drawHorizontalLine(0, 52, 128);
}

void setReadyForWeatherUpdate() {  //为天气更新做好准备
  Serial.println("Setting readyForUpdate to true");
  readyForWeatherUpdate = true;
}
