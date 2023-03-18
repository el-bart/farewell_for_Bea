#pragma once

#include <cstdint>

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#include "effect/EffectChristmas.h"
#include "effect/EffectPulsing.h"
#include "effect/EffectRainbow.h"
#include "effect/IEffect.h"

class LightManager final
{
  public:
	enum class Effect : uint8 { None, RainbowStatic, RainbowSlow, RainbowMedium, RainbowFast, Pulsing, Christmas };

	explicit LightManager(uint8_t pinLedStrip, uint16_t ledCount);
	~LightManager() = default;

	LightManager(LightManager const &) = delete;
	LightManager(LightManager &&) = delete;
	LightManager &operator=(LightManager const &) = delete;
	LightManager &operator=(LightManager &&) = delete;

	void update();
	void nextEffect();
	void setEffect(LightManager::Effect const effect);

  private:
	Adafruit_NeoPixel pixels;
	Effect effect{Effect::None};
	size_t effectIndex{};

	IEffect *effectPtr{};
	EffectRainbow rainbow{};
	EffectPulsing pulsing{};
	EffectChristmas christmas{};
};
