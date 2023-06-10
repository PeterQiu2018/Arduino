#include <Adafruit_NeoPixel.h>
 
// 控制 WS2812 灯条的引脚编号
#define PIN        6
 
//定义控制的 LED 数量
#define NUMPIXELS 28
 
//Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 50
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}
 
void loop() {
  pixels.clear(); // Set all pixel colors to 'off'
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    pixels.setPixelColor(i, pixels.Color(0, 225, 0));
 
    pixels.show();   // Send the updated pixel colors to the hardware.
 
    delay(DELAYVAL); // Pause before next pass through loop
  }
  pixels.clear();
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    pixels.setPixelColor(i, pixels.Color(225, 0, 0));
 
    pixels.show();   // Send the updated pixel colors to the hardware.
 
    delay(DELAYVAL); // Pause before next pass through loop
  }
  pixels.clear();
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    pixels.setPixelColor(i, pixels.Color(0, 0, 225));
 
    pixels.show();   // Send the updated pixel colors to the hardware.
 
    delay(DELAYVAL); // Pause before next pass through loop
  }
}
