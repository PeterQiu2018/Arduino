#include <FastLED.h>
#define LED_PIN     2
const int analogInPin = A2;
#define NUM_LEDS    1
#define CHIPSET     WS2811
#define COLOR_ORDER GRB
#define TEMPERATURE_2 Tungsten100W
CRGB leds[NUM_LEDS];
int BRIGHTNESS = 200;
int hVal = 255;
int sensorValue = 0;
int outputValue = 0;
void loop()
{
  sensorValue = analogRead(analogInPin);
  outputValue = map(sensorValue, 0, 1023, 255, 0);
  CHSV myHSVcolor(outputValue, 255, BRIGHTNESS); //色调,饱和度,明亮度
  FastLED.setBrightness(BRIGHTNESS);
  fill_solid(leds, NUM_LEDS, myHSVcolor);
  FastLED.show();
}

void setup() {
  FastLED.clear();
  delay( 1000 ); // power-up safety delay
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalSMD5050 );
  FastLED.setBrightness(127);
}
