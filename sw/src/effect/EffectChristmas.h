#pragma once

#include <cstddef>

#include "IEffect.h"

class EffectChristmas final : public IEffect
{
  public:
	EffectChristmas() = default;
	~EffectChristmas() = default;

	EffectChristmas(EffectChristmas const &) = delete;
	EffectChristmas(EffectChristmas &&) = delete;
	EffectChristmas &operator=(EffectChristmas const &) = delete;
	EffectChristmas &operator=(EffectChristmas &&) = delete;

	void apply(Adafruit_NeoPixel &pixels, float step = 0.0F) override;
	void update(Adafruit_NeoPixel &pixels) override;

  private:
	bool lightStateOdd{false};
	uint64_t effectUpdateTime{};
};
