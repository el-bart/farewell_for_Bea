#pragma once

#include <cstdint>
#include <unordered_map>

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

namespace rainbow_unicorn
{

class LightManager final
{
  public:
	enum class Effect : uint8 {
		None,
		RainbowStatic,
		RainbowSlow,
		RainbowMedium,
		RainbowFast,
		Pulsing,
		Christmas,
		First = None,
		Last = Christmas,
	};

	struct Color {
		uint8_t red{};
		uint8_t green{};
		uint8_t blue{};
	};

	explicit LightManager(uint8_t pinLedStrip, uint16_t ledCount);
	~LightManager() = default;

	void update();
	void onButtonPressed();

	void setStateOn(bool stateOn);
	[[nodiscard]] bool isStateOn() const;

	void setBrightness(uint8_t brightness);
	[[nodiscard]] uint8_t getBrightness() const;

	void setColor(Color const &color);
	[[nodiscard]] Color const &getColor() const;

	void setEffect(LightManager::Effect const &effect);
	LightManager::Effect const &getEffect() const;

	LightManager(LightManager const &) = delete;
	LightManager(LightManager &&) = delete;
	LightManager &operator=(LightManager const &) = delete;
	LightManager &operator=(LightManager &&) = delete;

  private:
	void updateEffect();

	void applyEffectNone();
	void applyEffectRainbow();
	void applyEffectChristmas();
	void applyEffectPulsing();

	void updateState();

	Adafruit_NeoPixel pixels;

	uint64_t effectUpdateTime{};

	uint8_t brightnessRequested{};
	float brightnessIncrement{};
	Color color{};
	Color colorRequested{};
	Effect effectRequested{Effect::None};
	uint16 hue{};
	uint16 hueStepSize{};
	std::unordered_map<LightManager::Effect, uint16> hueStepSizeMap{};

	bool stateOnRequested{false};
	bool statePending{false};
	bool brightnessPending{false};
	bool colorPending{false};
	bool effectPending{false};
	bool lightStateOdd{false};
};

} // namespace rainbow_unicorn
