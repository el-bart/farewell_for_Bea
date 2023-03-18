#pragma once

#include <cstddef>

#include <Adafruit_NeoPixel.h>

uint8_t inline constexpr BRIGHTNESS_MIN{std::numeric_limits<uint8>::min()};
uint8_t inline constexpr BRIGHTNESS_MAX{std::numeric_limits<uint8>::max()};

struct Color {
	uint8_t red{};
	uint8_t green{};
	uint8_t blue{};
};

class IEffect
{
  public:
	virtual void apply(Adafruit_NeoPixel &pixels, float step = 0.0F) = 0;
	virtual void update(Adafruit_NeoPixel &pixels) = 0;

  protected:
	float step{};
};
