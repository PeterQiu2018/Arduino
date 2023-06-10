#include <GyverOLED.h>
#include <Math.h>
GyverOLED<SSH1106_128x64> oled;
double rad;
int x1, x2, y1, y2;

void setup() {
  oled.init();
  // --------------------------
  oled.clear();
  oled.update();
  // --------------------------
  oled.dot(64, 63);     // точка на x,
  oled.update();
}

void loop() {
  for (int i = 0; i < 180; i += 3) {
    rad = i * PI / 180.00;
    int x2 = int(64 - cos(rad) * 60);
    int y2 = int(63 - sin(rad) * 60 );
    int x1 = int(64 - cos(rad) * 5);
    int y1 = int(63 - sin(rad) * 5);
    oled.line(x1, y1, x2 , y2);
    oled.update();
    delay(10);
    oled.clear();
  }
  for (int i = 180; i > 0; i -= 3) {
    rad = i * PI / 180.00;
    int x2 = int(64 - cos(rad) * 60);
    int y2 = int(63 - sin(rad) * 60 );
    int x1 = int(64 - cos(rad) * 5);
    int y1 = int(63 - sin(rad) * 5);
    oled.line(x1, y1, x2 , y2);
    oled.update();
    delay(10);
    oled.clear();
  }
}
