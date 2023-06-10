#include <Servo.h>
#include <GyverOLED.h>
#include <Math.h>
const int pingPin = 8; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 7; // Echo Pin of Ultrasonic Sensor
Servo myservo;//定义舵机变量名
GyverOLED<SSH1106_128x64> oled;
int pos = 0;
int x1, x2, y1, y2;

void setup()
{
  myservo.attach(9);//定义舵机接口（9、10 都可以，缺点只能控制2 个）
  Serial.begin(9600); // Starting Serial Terminal
  oled.init();
  // --------------------------
  oled.clear();
  oled.update();
  // --------------------------
  oled.clear();
  oled.dot(64, 63);     // точка на x,
  oled.update();
  delay(100);
}

void Draw_line(int angle, int len=60) {
  double rad;
  rad = angle * PI / 180.00;
  int x2 = int(64 - cos(rad) * len);
  int y2 = int(63 - sin(rad) * len );
  int x1 = int(64 - cos(rad) * 5);
  int y1 = int(63 - sin(rad) * 5);
  oled.line(x1, y1, x2 , y2);
  oled.update();
  delay(20);
  oled.clear();
}

void Print_angle(int angle){
  oled.home();
  oled.setScale(1);
  oled.invertText(false);
  oled.autoPrintln(true);   // автоматически переносить текст
  oled.print(angle);
}

void loop()
{
  for (pos = 0; pos < 180; pos += 1) // 从0°到180°运动
  { // 每次步进一度，实际会有些偏差属正常现象
    myservo.write(pos);            // 指定舵机转向的角度                     // 等待15ms让舵机到达指定位置
    Print_angle(pos);
    long duration, inches, cm;
    pinMode(pingPin, OUTPUT);
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(pingPin, LOW);
    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);
    cm = microsecondsToCentimeters(duration);
    Draw_line(pos, cm);
  }
  for (pos = 180; pos > 0; pos -= 1) //从180°到0°运动
  {
    myservo.write(pos);           // 指定舵机转向的角度
    Print_angle(pos);
    long duration, inches, cm;
    pinMode(pingPin, OUTPUT);
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(pingPin, LOW);
    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);
    cm = microsecondsToCentimeters(duration);
    Draw_line(pos, cm);
  }
}
long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
