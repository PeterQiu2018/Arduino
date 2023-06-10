#include <Servo.h>

const int A_input1=A0;
const int A_input2=A1;
const int A_input3=A2;
const int S_Pin1=1;
const int S_Pin2=2;
const int S_Pin3=3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Starting Serial Terminal
  Servo1.attach(S_Pin1);
  Servo2.attach(S_Pin2);
  Servo3.attach(S_Pin3);
  delay(1000);
  Servo1.write(0);
  delay(1000);
  Servo2.write(0);
  delay(1000);
  Servo3.write(0);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:

}
