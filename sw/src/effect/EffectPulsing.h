#pragma once

#include <cstddef>

#include "IEffect.h"

float inline constexpr BRIGHTNESS_PULSING_MIN{static_cast<float>(BRIGHTNESS_MAX) * 0.1F};
float inline constexpr BRIGHTNESS_PULSING_MAX{static_cast<float>(BRIGHTNESS_MAX)};

class EffectPulsing final : public IEffect
{
  public:
	EffectPulsing() = default;
	~EffectPulsing() = default;

	EffectPulsing(EffectPulsing const &) = delete;
	EffectPulsing(EffectPulsing &&) = delete;
	EffectPulsing &operator=(EffectPulsing const &) = delete;
	EffectPulsing &operator=(EffectPulsing &&) = delete;

	void apply(Adafruit_NeoPixel &pixels, float step = 0.0F) override;
	void update(Adafruit_NeoPixel &pixels) override;

  private:
	uint8_t brightness{};
};
