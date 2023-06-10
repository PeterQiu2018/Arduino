#include <dht11.h>

#include <Arduino.h>
#include <DHT11.h>
dht11 myDHT11(7);

void setup()			//Arduino程序初始化程序放在这里，只在开机时候运行一次
{
  Serial.begin(9600);	//设置通讯的波特率为9600
}

void loop()			//Arduino程序的主程序部分，循环运行内部程序
{
  myDHT11.DHT11_Read();                //读取温湿度值
  Serial.print("temperature:");
  Serial.print(myDHT11.TEM_Buffer_Int);
  Serial.print("    ");
  Serial.print("humidity:");
  Serial.print(myDHT11.HUMI_Buffer_Int);
  Serial.println("");
  delay(400);			  //延时1s
}
