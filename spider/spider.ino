#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// SG90-->400-2500=0-180   MG996R-->400-2500=0-120
#define SERVO_FREQ 50  // Analog servos run at ~50 Hz updates

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire);
int all_Angle = 0;
int pos_A = 0;
int neg_A = 0;
int angle0 = 0;
int angle1 = 0;
int angle2 = 0;
int angle3 = 0;
int angle4 = 0;
int angle5 = 0;

int PWM_value = 0;
int pos_PWM_value = 0;
int neg_PWM_value = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Servo test!");
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  all_Angle = 0;
  PWM_value = map(all_Angle, -90, 90, 600, 2500);

  pos_A = 30;
  pos_PWM_value = map(pos_A, -90, 90, 600, 2500);

  neg_A = -30;
  neg_PWM_value = map(neg_A, -90, 90, 600, 2500);

  //==============yaw leg==============
  pwm.writeMicroseconds(0, PWM_value);
  pwm.writeMicroseconds(1, PWM_value);
  pwm.writeMicroseconds(2, PWM_value);
  pwm.writeMicroseconds(3, PWM_value);
  pwm.writeMicroseconds(4, PWM_value);
  pwm.writeMicroseconds(5, PWM_value);
  delay(2000);

  //==============row leg==============
  pwm.writeMicroseconds(8, pos_PWM_value);  // 1
  pwm.writeMicroseconds(9, neg_PWM_value);  // 2
  pwm.writeMicroseconds(10, neg_PWM_value);  // 3
  pwm.writeMicroseconds(11, pos_PWM_value);  // 4
  pwm.writeMicroseconds(12, neg_PWM_value);  // 5
  pwm.writeMicroseconds(13, pos_PWM_value);  // 6
  delay(2000);
}

void loop() {
  //=============row up=============

  pos_A = 15;
  pos_PWM_value = map(pos_A, -90, 90, 600, 2500);
  pwm.writeMicroseconds(8, pos_PWM_value);   // 1
  pwm.writeMicroseconds(13, pos_PWM_value);  // 6
  neg_A = -15;
  neg_PWM_value = map(neg_A, -90, 90, 600, 2500);
  pwm.writeMicroseconds(9, neg_PWM_value);  // 2
  delay(1000);

  pos_A = 60;
  pos_PWM_value = map(pos_A, -90, 90, 600, 2500);
  pwm.writeMicroseconds(11, pos_PWM_value);  // 4
  neg_A = -60;
  neg_PWM_value = map(neg_A, -90, 90, 600, 2500);
  pwm.writeMicroseconds(10, neg_PWM_value);  // 3
  pwm.writeMicroseconds(12, neg_PWM_value);  // 5
  delay(1000);


  //=============yaw forword=============
  pos_A = 15;
  pos_PWM_value = map(pos_A, -90, 90, 600, 2500);
  pwm.writeMicroseconds(4, pos_PWM_value);
  neg_A = -15;
  neg_PWM_value = map(neg_A, -90, 90, 600, 2500);
  pwm.writeMicroseconds(2, neg_PWM_value);
  pwm.writeMicroseconds(3, neg_PWM_value);
  delay(1000);

  //=============row down=============
  pos_A = 15;
  pos_PWM_value = map(pos_A, -90, 90, 600, 2500);
  pwm.writeMicroseconds(11, pos_PWM_value);  // 4
  neg_A = -15;
  neg_PWM_value = map(neg_A, -90, 90, 600, 2500);
  pwm.writeMicroseconds(10, neg_PWM_value);  // 3
  pwm.writeMicroseconds(12, neg_PWM_value);  // 5
  delay(1000);


  pos_A = 60;
  pos_PWM_value = map(pos_A, -90, 90, 600, 2500);
  pwm.writeMicroseconds(8, pos_PWM_value);   // 1
  pwm.writeMicroseconds(13, pos_PWM_value);  // 6
  neg_A = -60;
  neg_PWM_value = map(neg_A, -90, 90, 600, 2500);
  pwm.writeMicroseconds(9, neg_PWM_value);  // 2
  delay(1000);

  //=============yaw forword=============
  pos_A = -15;
  pos_PWM_value = map(pos_A, -90, 90, 600, 2500);
  pwm.writeMicroseconds(4, pos_PWM_value);
  neg_A = 15;
  neg_PWM_value = map(neg_A, -90, 90, 600, 2500);
  pwm.writeMicroseconds(2, neg_PWM_value);
  pwm.writeMicroseconds(3, neg_PWM_value);
  delay(1000);

}
