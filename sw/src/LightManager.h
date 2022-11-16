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
        // REVIEW: instead of adding non-Effect enums to iterate, create a constexpr helper function, that returns std::array<>{Effect1, Effect2, ...} and use it instead. :)
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
    // REVIEW: it's better to return small types by value
	[[nodiscard]] Color const &getColor() const;

	void setEffect(LightManager::Effect const &effect);
    // REVIEW: it's better to return small types by value
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

    /* REVIEW: this class' memebers represent different and independent entities (eg. xmass-mode, rainbow mode, etc.). i'd consider moving these out into separate classes,
     *         that opperate on the same 'pixels' object, passed as a reference, but keep all the internals separatated from one another. this way these can be kept inside LightManager
     *         yet called only upon change, by eg. setting a pointer. example:
     *
     *         struct Effect
     *         {
     *           virtual Effect() = default;
     *           virtual apply(Adafruit_NeoPixel& pixels) = 0;
     *           virtual update(Adafruit_NeoPixel& pixels) = 0;
     *         };
     *
     *         struct Effect1: Effect { ... };
     *         struct Effect2: Effect { ... };
     *         // ...
     *
     *         struct LightManager
     *         {
     *            Effect1 e1_;
     *            Effect2 e2_;
     *            // ...
     *            Effect *e_{nullptr};
     *         };
     *
     *         now in order to change effect to Effect2 it's just enough to:
     *         e_ = &e2_;
     *         e_->apply(pixels);
     *
     *         then just call updates:
     *         e_->update(pixels);
     */
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
