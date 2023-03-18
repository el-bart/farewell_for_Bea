#include <climits>

#include "EffectPulsing.h"

void EffectPulsing::apply(Adafruit_NeoPixel &pixels, float const step)
{
	this->step = step;

	brightness = BRIGHTNESS_PULSING_MAX;
	pixels.setBrightness(BRIGHTNESS_PULSING_MAX);

	for (uint8_t i{}; i < pixels.numPixels(); ++i)
	{
		pixels.setPixelColor(i, brightness, BRIGHTNESS_MIN, BRIGHTNESS_MIN);
	}

	pixels.show();
}

void EffectPulsing::update(Adafruit_NeoPixel &pixels)
{
	float const brightnessTarget{std::clamp(static_cast<float>(brightness) + step, BRIGHTNESS_PULSING_MIN, BRIGHTNESS_PULSING_MAX)};

	if ((brightnessTarget >= BRIGHTNESS_PULSING_MAX) || (brightnessTarget <= BRIGHTNESS_PULSING_MIN))
	{
		step *= -1.0F;
	}

	brightness = static_cast<uint8_t>(std::round(brightnessTarget));

	for (uint8_t i{}; i < pixels.numPixels(); ++i)
	{
		pixels.setPixelColor(i, brightness, BRIGHTNESS_MIN, BRIGHTNESS_MIN);
	}

	pixels.show();
}
