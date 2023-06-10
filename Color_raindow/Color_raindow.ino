#include <Adafruit_NeoPixel.h>
#define PIN        7
#define NUMPIXELS 16
#define DELAYVAL 100
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int Red[6] = {255, 255, 0, 0, 0, 255};
int Green[6] = {0, 255, 255, 255, 0, 0};
int Blue[6] = {0, 0, 0, 255, 255, 255};

void setup() {
  pixels.begin();
}

void loop() {
  pixels.clear();
  /*
  for (int p=0;p<NUMPIXELS;p+=6) {
    for (int i=0;i<6;i++){
      int R=Red[i];
      int G=Green[i];
      int B=Blue[i];
      pixels.setPixelColor(p+i, pixels.Color(R,G,B));
      pixels.show();
      delay(DELAYVAL);
    }
  }
  */
  for (int i=0;i<NUMPIXELS;i++){
      int R=Red[i];
      int G=Green[i];
      int B=Blue[i];
      pixels.setPixelColor(i, pixels.Color(R,G,B));
      pixels.show();
      delay(DELAYVAL);
    }
}
