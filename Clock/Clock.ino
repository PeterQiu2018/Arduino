#include <Arduino.h>
#include <stdlib.h>
#define OUT_0     2
#define OUT_1     3
#define OUT_2     4
#define OUT_3     5
#define OUT_4     6
#define OUT_5     7
#define OUT_6     8
#define OUT_7     9
#define OUT_8     10
#define OUT_9     11
#define IN_0     A0
#define IN_1     A1
#define IN_2     A2
#define IN_3     A3
#define IN_4     A4
#define IN_5     A5
int hours = 0;
int minutes = 0;
int seconds = 0;

void setup() {
  // put your setup code here, to run once:
  Input_list[6]={IN_0,IN_1,IN_2,IN_3,IN_4,IN_5};
  for (int i=0,i<6,i++){
    analog_high();
    digital_low();
    analogWrite(Input_list[i],0);
    Bright(rand()%11);
    delay(200);
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
  first_num = 0;
  second_num = 0;
  seconds++;
  if (seconds == 60) {
    seconds = 0;
    minutes++;
  }
  if (minutes == 60) {
    minutes = 0;
    hours++;
  }
  if (hours == 24) {
    hours = 0;
  }
  
//#============================================#
  first_num = seconds / 10;
  second_num = seconds % 10;
  analog_high()
  digital_low()
  analogWrite(IN_0,0)
  Bright(first_num)
  analog_high()
  digital_low()
  analogWrite(IN_1,0)
  Bright(second_num)
//#============================================#
  first_num = minutes / 10;
  second_num = minutes % 10;
  analog_high()
  digital_low()
  analogWrite(IN_2,0)
  Bright(first_num)
  analog_high()
  digital_low()
  analogWrite(IN_3,0)
  Bright(second_num)
//#============================================#
  first_num = hours / 10;
  second_num = hours % 10;
  analog_high()
  digital_low()
  analogWrite(IN_4,0)
  Bright(first_num)
  analog_high()
  digital_low()
  analogWrite(IN_5,0)
  Bright(second_num)
//#============================================#
  delay(1000) //延迟1s
}

void Bright(num){
  switch (num)
  {
    case 0:
      digitalWrite(OUT_0, HIGH);
      break;
    case 1:
      digitalWrite(OUT_1, HIGH);
      break;
    case 2:
      digitalWrite(OUT_2,HIGH);
      break;
    case 3:
      digitalWrite(OUT_3,HIGH);
      break;
    case 4:
      digitalWrite(OUT_4,HIGH);
      break;
    case 5:
      digitalWrite(OUT_5,HIGH);
      break;
    case 6:
      digitalWrite(OUT_6,HIGH);
      break;
    case 7:
      digitalWrite(OUT_7,HIGH);
      break;
    case 8:
      digitalWrite(OUT_8,HIGH);
      break;
    case 9:
      digitalWrite(OUT_9,HIGH);
      break;
  }
}

void analog_high(){
  analogWrite(IN_0,255)
  analogWrite(IN_1,255)
  analogWrite(IN_2,255)
  analogWrite(IN_3,255)
  analogWrite(IN_4,255)
  analogWrite(IN_5,255)
}

void digital_low(){
  digitalWrite(OUT_0,LOW);
  digitalWrite(OUT_1,LOW);
  digitalWrite(OUT_2,LOW);
  digitalWrite(OUT_3,LOW);
  digitalWrite(OUT_4,LOW);
  digitalWrite(OUT_5,LOW);
  digitalWrite(OUT_6,LOW);
  digitalWrite(OUT_7,LOW);
  digitalWrite(OUT_8,LOW);
  digitalWrite(OUT_9,LOW);
}
