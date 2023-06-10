const int LED1=2;
const int LED2=3;
const int LED3=4;
bool LED1_Flag = false;
bool LED2_Flag = false;
bool LED3_Flag = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  digitalWrite(LED1,HIGH);
  delay(10);
  digitalWrite(LED2,HIGH);
  delay(10);
  digitalWrite(LED3,HIGH);
  delay(50);
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,LOW);
  delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,LOW);
  delay(500);
  digitalWrite(LED1,HIGH);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,LOW);
  delay(500);
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,HIGH);
  digitalWrite(LED3,LOW);
  delay(500);
  digitalWrite(LED1,HIGH);
  digitalWrite(LED2,HIGH);
  digitalWrite(LED3,LOW);
  delay(500);
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,HIGH);
  delay(500);
  digitalWrite(LED1,HIGH);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,HIGH);
  delay(500);
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,HIGH);
  digitalWrite(LED3,HIGH);
  delay(500);
  digitalWrite(LED1,HIGH);
  digitalWrite(LED2,HIGH);
  digitalWrite(LED3,HIGH);
  delay(500);
}
