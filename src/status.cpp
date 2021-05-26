#include "status.hpp"

CRGB leds[NUM_LEDS];
bool connected = false;

void initStatus()
{
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

void box(CRGB color)
{
	if (connected)
	{
		for (int i = 0; i < sizeof(scanPattern); i++)
		{
			if (scanPattern[i])
			{
				leds[i] = color;
			}
		}
	}
	FastLED.show();
}

void flash(bool success)
{
	FastLED.setBrightness(30);
	for (int x = 255; x >= 0; x--)
	{
		for (int i = 0; i < NUM_LEDS; i++)
		{
			if (success)
			{
				leds[i] = CRGB(0, x, 0);
			}
			else
			{
				leds[i] = CRGB(x, 0, 0);
			}
		}
		FastLED.show();
		delay(5);
	}
	FastLED.setBrightness(255);
}

void conn(bool val)
{
	connected = val;
	if(val) {
		box(standardColor);
	} else {
		setStatus(CLEAR);
	}
}