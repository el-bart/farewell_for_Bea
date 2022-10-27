#include <FastLED.h>
#define NUM_LEDS 10
#define DATA_PIN 0

CRGB leds[NUM_LEDS];

void setup()
{
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
}

void loop()
{
  const CRGB colors[] = { CRGB::Red, CRGB::Green, CRGB::Blue, CRGB::White, CRGB::Black };
  for(auto color: colors)
  {
    for(auto &e: leds)
      e = color;
    FastLED.show();
    delay(2*1000);
  }
}
