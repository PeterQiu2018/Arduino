#include <FastLED.h>

#define LED_PIN     2
#define NUM_LEDS    50
#define CHIPSET     WS2811
#define COLOR_ORDER RGB
#define TEMPERATURE_2 Tungsten100W
CRGB leds[NUM_LEDS];
int BRIGHTNESS = 10;
int hVal = 255;
int DELAYTIME = 50;

void setup(void) {
  Serial.begin(115200);
  FastLED.clear();
  delay( 1000 ); // power-up safety delay
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalSMD5050 );
  FastLED.setBrightness(127);
}

void loop(void) {
  hVal++;
  CHSV myHSVcolor(hVal, 255, BRIGHTNESS);
  FastLED.setBrightness(BRIGHTNESS);
  fill_solid(leds, NUM_LEDS, myHSVcolor);
  delay(DELAYTIME);
  FastLED.show();
}
