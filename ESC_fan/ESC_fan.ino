#include <Servo.h>

Servo ESC;     // create servo object to control the ESC

int potValue;  // value from the analog pin

void setup() {
  // Attach the ESC on pin 7
  // Serial.begin(9600);
  ESC.attach(7); // (pin, min pulse width, max pulse width in microseconds) 
  ESC.writeMicroseconds(1000);
}

void loop() {
  potValue = analogRead(A0);   // reads the value of the potentiometer (value between 0 and 1023)
  potValue = map(potValue, 0, 1023, 1000,2000);   
  ESC.writeMicroseconds(potValue);    // Send the signal to the ESC
  // Serial.println(potValue);
}