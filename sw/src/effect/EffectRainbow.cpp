#include <climits>

#include "EffectRainbow.h"

namespace
{
uint16_t constexpr HUE_MIN{std::numeric_limits<uint16_t>::min()};
uint16_t constexpr HUE_MAX{std::numeric_limits<uint16_t>::max()};
} // namespace

void EffectRainbow::apply(Adafruit_NeoPixel &pixels, float const step)
{
	this->step = step;
	hue = HUE_MIN;

	pixels.setBrightness(BRIGHTNESS_MAX);
	pixels.clear();
	pixels.show();
}

void EffectRainbow::update(Adafruit_NeoPixel &pixels)
{
	pixels.rainbow(hue);
	pixels.show();

	uint32_t const hueNew{static_cast<uint32>(hue) + static_cast<uint32>(step)};

	hue = ((hue > HUE_MAX) ? HUE_MIN : hueNew);
}
