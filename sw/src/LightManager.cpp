#include <climits>

#include "LightManager.h"

namespace rainbow_unicorn
{
namespace
{
uint64_t constexpr UPDATE_INTERVAL_MSEC{10};
uint64_t constexpr CHRISTMAS_LIGHT_UPDATE_TIME_MSEC{100};

uint8_t constexpr BRIGHTNESS_MIN{std::numeric_limits<uint8>::min()};
uint8_t constexpr BRIGHTNESS_MAX{std::numeric_limits<uint8>::max()};

uint16_t constexpr HUE_MIN{std::numeric_limits<uint16_t>::min()};
uint16_t constexpr HUE_MAX{std::numeric_limits<uint16_t>::max()};
uint16_t constexpr HUE_STEP_SIZE_STATIC{std::numeric_limits<uint16_t>::min()};
uint16_t constexpr HUE_STEP_SIZE_SLOW{10U};
uint16_t constexpr HUE_STEP_SIZE_MEDIUM{100U};
uint16_t constexpr HUE_STEP_SIZE_FAST{1000U};

float constexpr BRIGHTNESS_PULSING_MIN{static_cast<float>(BRIGHTNESS_MAX) * 0.1F};
float constexpr BRIGHTNESS_PULSING_MAX{static_cast<float>(BRIGHTNESS_MAX)};
uint64_t constexpr UPDATE_INTERVAL_PULSING_MSEC{1000U};

LightManager::Color constexpr COLOR_RED{255, 0, 0};

float constexpr BRIGHTNESS_PULSING_INC_NONE{0.0F};
float constexpr BRIGHTNESS_PULSING_INC{static_cast<float>(BRIGHTNESS_PULSING_MAX - BRIGHTNESS_PULSING_MIN) /
									   (static_cast<float>(UPDATE_INTERVAL_PULSING_MSEC) / static_cast<float>(UPDATE_INTERVAL_MSEC))};
} // namespace

LightManager::LightManager(uint8_t const pinLedStrip, uint16_t const ledCount) : pixels(ledCount, pinLedStrip, NEO_GRB + NEO_KHZ800)
{
    // REVIEW: this can be done on c-tors init list
	hueStepSizeMap = {{LightManager::Effect::RainbowStatic, HUE_STEP_SIZE_STATIC},
					  {LightManager::Effect::RainbowSlow, HUE_STEP_SIZE_SLOW},
					  {LightManager::Effect::RainbowMedium, HUE_STEP_SIZE_MEDIUM},
					  {LightManager::Effect::RainbowFast, HUE_STEP_SIZE_FAST}};

	pixels.begin();
	pixels.clear();
	pixels.show();

	setEffect(Effect::RainbowFast);
}

void LightManager::update()
{
	updateEffect();
	updateState();
}

void LightManager::updateEffect()
{
	switch (getEffect())
	{
		case Effect::None:
			applyEffectNone();
			return;

		case Effect::RainbowStatic:
			[[fallthrough]];
		case Effect::RainbowSlow:
			[[fallthrough]];
		case Effect::RainbowMedium:
			[[fallthrough]];
		case Effect::RainbowFast:
			applyEffectRainbow();
			return;

		case Effect::Pulsing:
			applyEffectPulsing();
			return;

		case Effect::Christmas:
			applyEffectChristmas();
			return;
	}
}

void LightManager::applyEffectNone()
{
	if (effectPending)
	{
		effectPending = false;
		setStateOn(false);
	}
}

void LightManager::applyEffectRainbow()
{
	if (effectPending)
	{
		effectPending = false;
		hue = HUE_MIN;
		hueStepSize = hueStepSizeMap[getEffect()];

		setBrightness(BRIGHTNESS_MAX);

		pixels.clear();
		pixels.show();

		Serial.print("Hue step size is ");
		Serial.println(hueStepSize);
	}

	pixels.rainbow(hue);
	pixels.show();

	uint32 const hueNew{static_cast<uint32>(hue) + hueStepSize};

	hue = ((hue > HUE_MAX) ? HUE_MIN : hueNew);
	colorPending = false;
}

void LightManager::applyEffectChristmas()
{
	uint64_t const now{millis()};

	if ((now - effectUpdateTime) < CHRISTMAS_LIGHT_UPDATE_TIME_MSEC)
	{
		return;
	}

	if (effectPending)
	{
		pixels.clear();
		pixels.show();
		effectPending = false;
	}

	for (size_t i{}; i < pixels.numPixels(); ++i)
	{
		bool const red{(lightStateOdd && ((i % 2) == 0)) || ((not lightStateOdd) && ((i % 2) != 0))};

		if (red)
		{
			pixels.setPixelColor(i, getBrightness(), BRIGHTNESS_MIN, BRIGHTNESS_MIN);
		}
		else
		{
			pixels.setPixelColor(i, BRIGHTNESS_MIN, getBrightness(), BRIGHTNESS_MIN);
		}
	}

	pixels.show();
	effectUpdateTime = millis();
	lightStateOdd = (not lightStateOdd);
}

void LightManager::applyEffectPulsing()
{
	if (effectPending)
	{
		effectPending = false;
		brightnessIncrement = BRIGHTNESS_PULSING_INC;

		setColor(COLOR_RED);
		setBrightness(BRIGHTNESS_MAX);
	}

	float const brightnessTarget{std::clamp(getBrightness() + brightnessIncrement, BRIGHTNESS_PULSING_MIN, BRIGHTNESS_PULSING_MAX)};

	if ((brightnessTarget == BRIGHTNESS_PULSING_MAX) || (brightnessTarget == BRIGHTNESS_PULSING_MIN))
	{
		brightnessIncrement *= -1;
	}

	setBrightness(static_cast<uint8_t>(std::round(brightnessTarget)));
}

void LightManager::updateState()
{
	if (statePending)
	{
		statePending = false;
		setStateOn(stateOnRequested);
	}

	if (brightnessPending)
	{
		brightnessPending = false;
		setBrightness(brightnessRequested);
	}

	if (colorPending)
	{
		colorPending = false;
		setColor(colorRequested);
	}
}

// REVIEW: LightManager should not be aware of any buttons - i suggest to rename to sth. like "nextState()".
void LightManager::onButtonPressed()
{
	uint8_t effectNew{static_cast<uint8_t>(static_cast<uint8_t>(getEffect()) + 1U)};

	if (effectNew > static_cast<uint8_t>(Effect::Last))
	{
		effectNew = static_cast<uint8_t>(Effect::First);
	}

	setEffect(static_cast<Effect>(effectNew));
}

void LightManager::setStateOn(bool const stateOn)
{
	bool const currentStateOn{isStateOn()};

	if (currentStateOn == stateOn)
	{
		return;
	}

	if ((not currentStateOn) && stateOn)
	{
		// Switch on
		setBrightness(BRIGHTNESS_MAX);
		setColor({BRIGHTNESS_MAX, BRIGHTNESS_MAX, BRIGHTNESS_MAX});
	}
	else
	{
		// Switch off
		setBrightness(BRIGHTNESS_MIN);
		setColor({BRIGHTNESS_MIN, BRIGHTNESS_MIN, BRIGHTNESS_MIN});
		setEffect(Effect::None);

		pixels.clear();
		pixels.show();
	}
}

bool LightManager::isStateOn() const
{
	Color const color{getColor()};

	bool const hasNonZeroBrightness{getBrightness() > BRIGHTNESS_MIN};
	bool const hasNonZeroColor{(color.red > BRIGHTNESS_MIN) || (color.green > BRIGHTNESS_MIN) || (color.blue > BRIGHTNESS_MIN)};
	bool const hasManualColor{hasNonZeroBrightness && hasNonZeroColor};
	bool const hasEffect{getEffect() != Effect::None};

	return (hasManualColor || hasEffect);
}

void LightManager::setBrightness(uint8_t const brightness)
{
	uint8_t const brightnessCurrent{pixels.getBrightness()};
	Color const &colorCurrent{getColor()};

	bool const switchOn{(brightnessCurrent == BRIGHTNESS_MIN) && (brightness > BRIGHTNESS_MIN)};
	bool const colorSet{(colorCurrent.red > BRIGHTNESS_MIN) || (colorCurrent.green > BRIGHTNESS_MIN) || (colorCurrent.blue > BRIGHTNESS_MIN)};
	bool const colorRequestedSet{colorPending && ((colorRequested.red > BRIGHTNESS_MIN) || (colorRequested.green > BRIGHTNESS_MIN) || (colorRequested.blue > BRIGHTNESS_MIN))};

	if (switchOn && !colorSet && !colorRequestedSet)
	{
		colorRequested.red = brightness;
		colorRequested.green = brightness;
		colorRequested.blue = brightness;
		colorPending = true;
	}

	pixels.setBrightness(brightness);
	pixels.show();
}

uint8_t LightManager::getBrightness() const
{
	return pixels.getBrightness();
}

void LightManager::setColor(Color const &color)
{
	this->color = color;

	for (uint8_t i{}; i < pixels.numPixels(); ++i)
	{
		pixels.setPixelColor(i, color.red, color.green, color.blue);
	}

	pixels.show();
}

LightManager::Color const &LightManager::getColor() const
{
	return color;
}

void LightManager::setEffect(LightManager::Effect const &effect)
{
	effectRequested = effect;
	effectPending = true;

	Serial.print("New effect is ");
	Serial.println(static_cast<uint8_t>(getEffect()));
}

LightManager::Effect const &LightManager::getEffect() const
{
	return effectRequested;
}

} // namespace rainbow_unicorn
