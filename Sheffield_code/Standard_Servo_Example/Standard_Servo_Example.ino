// This Example code is for use with the Controlling a Standard Servomotor exercise
//

// Include the servo library to allow for connection and control of servo motors
#include <Servo.h>

// define the macro pinServo1 as 9, to use for connecting the servo to pin 9
#define pinServo1 9

// Declare a servo motor class variable servo 1
Servo servo1;
int potAnalogPin = 0; // FSR is connected to analog 0
int potReading;      // the analog reading from the FSR resistor divider
int calibrated;

// -------------------------------------
// Setup function
void setup()
{
  Serial.begin(9600);
  // "attach"  servo 1 to the defined pin
  servo1.attach(pinServo1);
  servo1.write(0);
  // Alternte command for setting the neutral position
  delay(2000);
}

// -------------------------------------
// Loop Function
void loop()
{
  potReading = analogRead(potAnalogPin);
  Serial.println(potReading);
  if (potReading<512){
    calibrated = map(potReading*1, 0, 511, 500, 1500);
  }else{
    calibrated = map(potReading*1, 512, 1023, 1500, 2500);
  }
  servo1.writeMicroseconds(calibrated);
  

}
