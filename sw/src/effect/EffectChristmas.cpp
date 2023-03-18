#include <Arduino.h>
#include <climits>

#include "EffectChristmas.h"

void EffectChristmas::apply(Adafruit_NeoPixel &pixels, float const step)
{
	this->step = step;

	pixels.clear();
	pixels.show();
}

void EffectChristmas::update(Adafruit_NeoPixel &pixels)
{
	uint64_t const now{millis()};

	if ((now - effectUpdateTime) < static_cast<uint64_t>(step))
	{
		return;
	}

	for (size_t i{}; i < pixels.numPixels(); ++i)
	{
		bool const red{(lightStateOdd && ((i % 2) == 0)) || ((not lightStateOdd) && ((i % 2) != 0))};

		if (red)
		{
			pixels.setPixelColor(i, pixels.getBrightness(), BRIGHTNESS_MIN, BRIGHTNESS_MIN);
		}
		else
		{
			pixels.setPixelColor(i, BRIGHTNESS_MIN, pixels.getBrightness(), BRIGHTNESS_MIN);
		}
	}

	pixels.show();
	effectUpdateTime = now;
	lightStateOdd = (not lightStateOdd);
}
