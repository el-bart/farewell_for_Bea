#include <Arduino.h>

#include "ButtonHandler.h"

ButtonHandler::ButtonHandler(uint8_t const pinButtonPar) : pinButton(pinButtonPar)
{
	pinMode(pinButton, INPUT_PULLUP);
}

bool ButtonHandler::buttonPressedEvent()
{
	bool buttonPressedEvent{false};
	bool const buttonPressedNew{digitalRead(pinButton) == LOW};

	if ((not buttonPressed) && buttonPressedNew)
	{
		Serial.println("Button press detected");
		buttonPressedEvent = true;
	}

	buttonPressed = buttonPressedNew;
	return buttonPressedEvent;
}
