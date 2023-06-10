#include <Servo.h>
const int pingPin = 8; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 7; // Echo Pin of Ultrasonic Sensor
Servo myservo;//定义舵机变量名
int pos = 0;
void setup()
{
  myservo.attach(9);
  Serial.begin(9600); // Starting Serial Terminal
  myservo.write(90);
  delay(1000);
  myservo.write(0);
  delay(1000);
  myservo.write(180);
  delay(1000);
}

void loop()
{
  
}
long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
