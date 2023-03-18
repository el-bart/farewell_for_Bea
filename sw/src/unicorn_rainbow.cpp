#include <Arduino.h>

#include "ButtonHandler.h"
#include "LightManager.h"

namespace
{
uint32_t constexpr SERIAL_BAUD_RATE{115200UL};
uint64_t constexpr UPDATE_INTERVAL_MSEC{10ULL};

uint8_t constexpr PIN_LED_STRIP{D6};
uint8_t constexpr PIN_BUTTON{D7};
uint8_t constexpr LED_COUNT{25U};

ButtonHandler buttonHandler{PIN_BUTTON};
LightManager lightManager{PIN_LED_STRIP, LED_COUNT};
} // namespace

void setup()
{
	Serial.begin(SERIAL_BAUD_RATE);

	Serial.println();
	Serial.println("Initializing ...");

	wdt_enable(WDTO_1S);
	Serial.println("Watchdog enabled");

	lightManager.setEffect(LightManager::Effect::RainbowMedium);

	Serial.println("Unicorn Rainbow initialized");
}

void loop()
{
	wdt_reset();

	if (buttonHandler.buttonPressedEvent())
	{
		lightManager.nextEffect();
	}

	lightManager.update();

	delay(UPDATE_INTERVAL_MSEC);
}
