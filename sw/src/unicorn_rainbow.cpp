#include <Arduino.h>

#include "RainbowUnicorn.h"

using rainbow_unicorn::RainbowUnicorn;

uint32_t constexpr SERIAL_BAUD_RATE{115200};
uint64_t constexpr UPDATE_INTERVAL_MSEC{10};

RainbowUnicorn rainbowUnicorn;

void setup()
{
	Serial.begin(SERIAL_BAUD_RATE);
    // REVIEW: i'd start 1st line with a new line, as usually duringin uC reset some garbage shows up on terminal
	Serial.println("Initializing ...");

	wdt_enable(WDTO_1S);
	Serial.println("Watchdog enabled");

    // REVIEW: consider using RainbowUnicorn's c-tor instead
	rainbowUnicorn.initialize();

	Serial.println("Main controller initialized");
}

void loop()
{
	wdt_reset();

	rainbowUnicorn.update();
	delay(UPDATE_INTERVAL_MSEC);
}

// REVIEW: for embedded devices it's quite common to put even more stuff into header-only elements. this way compiler can inline much more, w/o a need for LTO. eg. compiler can then use value from getColor() directly, as it understands the context.
