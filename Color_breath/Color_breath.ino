#include <FastLED.h>
#define LED_PIN     7
#define NUM_LEDS    16
#define CHIPSET     WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
int BRIGHTNESS = 100;
#define TEMPERATURE_1 Tungsten100W
#define TEMPERATURE_2 OvercastSky
int DISPLAYTIME = 20;

void setup() {
  // put your setup code here, to run once:
  FastLED.clear();
  delay( 1500 ); // power-up safety delay
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalSMD5050 );
  FastLED.setBrightness( BRIGHTNESS );
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=100;i<255;i++){
    BRIGHTNESS=i;
    fill_palette(leds,NUM_LEDS,0,8,OceanColors_p,BRIGHTNESS,LINEARBLEND);
    FastLED.show();
    FastLED.delay(DISPLAYTIME);
  }
  for(int i=255;i>100;i--){
    BRIGHTNESS=i;
    fill_palette(leds,NUM_LEDS,0,8,OceanColors_p,BRIGHTNESS,LINEARBLEND);
    FastLED.show();
    FastLED.delay(DISPLAYTIME);
  }
  
}
