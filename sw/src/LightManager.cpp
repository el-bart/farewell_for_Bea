#include "LightManager.h"

namespace
{
uint64_t constexpr UPDATE_INTERVAL_MSEC{10ULL};
uint64_t constexpr CHRISTMAS_LIGHT_UPDATE_TIME_MSEC{100ULL};

uint16_t inline constexpr HUE_STEP_SIZE_STATIC{0U};
uint16_t inline constexpr HUE_STEP_SIZE_SLOW{10U};
uint16_t inline constexpr HUE_STEP_SIZE_MEDIUM{100U};
uint16_t inline constexpr HUE_STEP_SIZE_FAST{1000U};

uint64_t constexpr UPDATE_INTERVAL_PULSING_MSEC{1000U};

float constexpr BRIGHTNESS_PULSING_INC{static_cast<float>(BRIGHTNESS_PULSING_MAX - BRIGHTNESS_PULSING_MIN) /
									   (static_cast<float>(UPDATE_INTERVAL_PULSING_MSEC) / static_cast<float>(UPDATE_INTERVAL_MSEC))};

std::array<LightManager::Effect, 7> constexpr effects()
{
	return {LightManager::Effect::None,		   LightManager::Effect::RainbowStatic, LightManager::Effect::RainbowSlow, LightManager::Effect::RainbowMedium,
			LightManager::Effect::RainbowFast, LightManager::Effect::Pulsing,		LightManager::Effect::Christmas};
}

} // namespace

LightManager::LightManager(uint8_t const pinLedStrip, uint16_t const ledCount) : pixels(ledCount, pinLedStrip, NEO_GRB + NEO_KHZ800)
{
	pixels.begin();
	pixels.clear();
	pixels.show();

	setEffect(Effect::RainbowMedium);
}

void LightManager::update()
{
	if (not effectPtr)
	{
		return;
	}

	effectPtr->update(pixels);
}

void LightManager::nextEffect()
{
	++effectIndex;

	if (effectIndex >= effects().size())
	{
		effectIndex = 0;
	}

	setEffect(effects()[effectIndex]);
}

void LightManager::setEffect(LightManager::Effect const effect)
{
	this->effect = effect;
	effectIndex = static_cast<size_t>(effect);
	int32_t step{};

	switch (effect)
	{
		case Effect::None:
			pixels.clear();
			pixels.show();
			effectPtr = nullptr;
			break;

		case Effect::RainbowStatic:
			step = HUE_STEP_SIZE_STATIC;
			effectPtr = &rainbow;
			break;

		case Effect::RainbowSlow:
			step = HUE_STEP_SIZE_SLOW;
			effectPtr = &rainbow;
			break;

		case Effect::RainbowMedium:
			step = HUE_STEP_SIZE_MEDIUM;
			effectPtr = &rainbow;
			break;

		case Effect::RainbowFast:
			step = HUE_STEP_SIZE_FAST;
			effectPtr = &rainbow;
			break;

		case Effect::Pulsing:
			step = BRIGHTNESS_PULSING_INC;
			effectPtr = &pulsing;
			break;

		case Effect::Christmas:
			step = CHRISTMAS_LIGHT_UPDATE_TIME_MSEC;
			effectPtr = &christmas;
			break;
	}

	if (effectPtr)
	{
		effectPtr->apply(pixels, step);
	}

	Serial.print("New effect is ");
	Serial.println(static_cast<uint8_t>(effect));
}
