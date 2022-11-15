#include <Arduino.h>

#include "RainbowUnicorn.h"

using rainbow_unicorn::RainbowUnicorn;

uint32_t constexpr SERIAL_BAUD_RATE{115200};
uint64_t constexpr UPDATE_INTERVAL_MSEC{10};

RainbowUnicorn rainbowUnicorn;

void setup()
{
	Serial.begin(SERIAL_BAUD_RATE);
	Serial.println("Initializing ...");

	wdt_enable(WDTO_1S);
	Serial.println("Watchdog enabled");

	rainbowUnicorn.initialize();

	Serial.println("Main controller initialized");
}

void loop()
{
	wdt_reset();

	rainbowUnicorn.update();
	delay(UPDATE_INTERVAL_MSEC);
}
