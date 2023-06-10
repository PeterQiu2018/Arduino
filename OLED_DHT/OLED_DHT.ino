#include <Arduino.h>
#include <dht11.h>
dht11 DHT11;
#define DHT11PIN 7

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup()      //Arduino程序初始化程序放在这里，只在开机时候运行一次
{
  Serial.begin(9600); //设置通讯的波特率为9600
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  // Draw a single pixel in white
  display.drawPixel(10, 10, SSD1306_WHITE);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display(); //display.display();相当于显示
  delay(2000);
  pinMode(11,OUTPUT);
}

void loop()     //Arduino程序的主程序部分，循环运行内部程序
{
  //display.clearDisplay();   // clears the screen and buffer
  //display.display();
  analogWrite(11,255);
  delay(50);
  analogWrite(11,0);
  //DHT11.DHT11_Read();                //读取温湿度值

  Serial.print("temperature:");
  Serial.print(DHT11.temperature);
  Serial.print("    ");
  Serial.print("humidity:");
  Serial.print(DHT11.humidity);
  Serial.println("");

  display.clearDisplay();
  display.setTextSize(1); //选择字号
  display.setTextColor(WHITE);  //字体颜色
  display.setCursor(0, 0);  //起点坐标
  display.print("temperature:");
  display.println(DHT11.temperature);
  display.print("humidity:");
  display.println(DHT11.humidity);
  display.display();

  delay(1000);
}
