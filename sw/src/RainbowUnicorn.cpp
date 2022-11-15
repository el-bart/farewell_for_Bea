#include "RainbowUnicorn.h"

namespace rainbow_unicorn
{

namespace
{
uint8_t constexpr PIN_LED_STRIP{D6};
uint8_t constexpr PIN_BUTTON{D7};
uint8_t constexpr LED_COUNT{175};
} // namespace

RainbowUnicorn::RainbowUnicorn() : lightManager(PIN_LED_STRIP, LED_COUNT)
{
}

void RainbowUnicorn::initialize()
{
	pinMode(PIN_BUTTON, INPUT_PULLUP);
	lightManager.setEffect(LightManager::Effect::RainbowMedium);
}

void RainbowUnicorn::update()
{
	updateButton();

	lightManager.update();
}

void RainbowUnicorn::updateButton()
{
	bool const buttonPressedNew{digitalRead(PIN_BUTTON) == LOW};

	if (!buttonPressed && buttonPressedNew)
	{
		Serial.println("Button press detected");
		lightManager.onButtonPressed();
	}

	buttonPressed = buttonPressedNew;
}

} // namespace rainbow_unicorn
