#include "status.hpp"

CRGB leds[NUM_LEDS];

void initStatus() {
    FastLED.addLeds<NEOPIXEL, 9>(leds, NUM_LEDS);
}

void setStatus(StatusCode s)
{
    for (int i = 0; i < NUM_LEDS; i++)
	{
		leds[i] = CRGB(s.r, s.g, s.b);
	}
    FastLED.show();
}

void flash() {
    for (int x = 35; x >= 0; x--)
	{
		for (int i = 0; i < NUM_LEDS; i++)
		{
            leds[i] = CRGB(0, x, 0);
		}
		FastLED.show();
		delay(40);
	}
}