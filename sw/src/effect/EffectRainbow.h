#pragma once

#include <cstddef>

#include "IEffect.h"

class EffectRainbow final : public IEffect
{
  public:
	EffectRainbow() = default;
	~EffectRainbow() = default;

	EffectRainbow(EffectRainbow const &) = delete;
	EffectRainbow(EffectRainbow &&) = delete;
	EffectRainbow &operator=(EffectRainbow const &) = delete;
	EffectRainbow &operator=(EffectRainbow &&) = delete;

	void apply(Adafruit_NeoPixel &pixels, float step = 0.0F) override;
	void update(Adafruit_NeoPixel &pixels) override;

  private:
	uint16_t hue{};
};
