#include <FastLED.h>
#define LED_PIN     7
#define NUM_LEDS    16
#define CHIPSET     WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
int BRIGHTNESS = 255;
#define TEMPERATURE_1 Tungsten100W
#define TEMPERATURE_2 OvercastSky
int DISPLAYTIME = 15;
void loop()
{
  static uint8_t starthue = 0;
  FastLED.setTemperature( TEMPERATURE_1 ); // second temperature
  fill_rainbow( leds, NUM_LEDS, --starthue, 20);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.show();
  FastLED.delay(DISPLAYTIME);
}

void setup() {
  FastLED.clear();
  delay( 1500 ); // power-up safety delay
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalSMD5050 );
  FastLED.setBrightness( BRIGHTNESS );
}
