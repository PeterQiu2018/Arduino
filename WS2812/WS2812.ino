#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// 控制 WS2812 灯条的引脚编号
#define PIN        7

//定义控制的 LED 数量
#define NUMPIXELS 60

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//相邻 LED 之间的延迟，单位毫秒
#define DELAYVAL 50

void setup() {
  Serial.begin(9600);
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {
  int i=0;
  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  //for (int i = 1; i < NUMPIXELS; i++) { // For each pixel...
    for (int R = 0; R <= 255; R+=50) {
      for (int G = 0; G <= 255; G+=50) {
        for (int B = 0; B <= 255; B+=50) {
          //pixels.clear();
          pixels.setPixelColor(i, pixels.Color(R, G, B));
          pixels.show();   // Send the updated pixel colors to the hardware.
          delay(DELAYVAL); // Pause before next pass through loop
          i++;
          if (i==NUMPIXELS){
            i=0;
          }
        }
      }
    }
  //}
}
