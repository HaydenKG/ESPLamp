#include <FastLED.h>

CRGBPalette16  lavaPalette = CRGBPalette16(
  CRGB::DarkRed,  CRGB::Maroon,   CRGB::DarkRed,  CRGB::Maroon,
  CRGB::DarkRed,  CRGB::Maroon,   CRGB::DarkRed,  CRGB::DarkRed,
  CRGB::DarkRed,  CRGB::DarkRed,  CRGB::Red,      CRGB::Orange,
  CRGB::Maroon,    CRGB::Orange,   CRGB::Red,      CRGB::DarkRed
);

uint16_t brightnessScale = 150;
uint16_t indexScale = 100;

void confetti(CRGB leds[], int NUM_LEDS){
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV(20 + random8(), 20 + random8(), 20 + random8());
}

void rainbow(CRGB leds[], int NUM_LEDS) {
  // FastLED's built-in rainbow generator
  uint8_t beatA = beatsin8(10, 0 , 255);
  uint8_t beatB = beatsin8(5, 0 , 255);
  fill_rainbow( leds, NUM_LEDS, (beatA + beatB), 8);
}

void fire(CRGB leds[], int NUM_LEDS) {
  uint8_t sinBeat = beatsin8(2, 0, NUM_LEDS, 0, 0);
  uint8_t sinBeat1 = beatsin8(10, 0, NUM_LEDS, 250, 85);
  uint8_t sinBeat2 = beatsin8(20, 0, NUM_LEDS, 500, 125);

  leds[sinBeat] = CRGB::Orange;
  leds[sinBeat1] = CRGB::Red;
  leds[sinBeat2] = CRGB::OrangeRed;
}

void lava(CRGB leds[], int NUM_LEDS){
  for (int i = 0; i < NUM_LEDS; i++) {
    uint8_t brightness = inoise8(i * brightnessScale, millis() / 5);
    uint8_t index = inoise8(i * indexScale, millis() /10);
    leds[i] = ColorFromPalette(lavaPalette, index, brightness);
  }
}

void fairy(CRGB leds[], int NUM_LEDS) {
  uint8_t sinBeat = beatsin8(2, 0, NUM_LEDS, 0, 0);
  uint8_t sinBeat1 = beatsin8(10, 0, NUM_LEDS, 250, 85);
  uint8_t sinBeat2 = beatsin8(20, 0, NUM_LEDS, 250, 85);

  leds[sinBeat] = CRGB::Orange;
  leds[sinBeat1] = CRGB::OrangeRed;
  leds[sinBeat2] = CRGB::DarkOrange;
}

void sparkle(CRGB leds[], int NUM_LEDS){
    int randomLED = random8(NUM_LEDS);
    if( random8() < 30) {
        leds[ randomLED ] += CRGB::DarkOrange;        
    } else {
        leds[ randomLED ] += CRGB::Red; 
    }
}

void wave(CRGB leds[], int NUM_LEDS){
  uint8_t sinBeat = beatsin8(10, 0, NUM_LEDS, 0, 0);
  uint8_t sinBeat1 = beatsin8(10, 0, NUM_LEDS, 250, 85);
  uint8_t sinBeat2 = beatsin8(10, 0, NUM_LEDS, 500, 170);

  leds[sinBeat] = CRGB::Blue;
  leds[sinBeat1] = CRGB::Red;
  leds[sinBeat2] = CRGB::Green;

  fadeToBlackBy(leds, NUM_LEDS, 10);
}