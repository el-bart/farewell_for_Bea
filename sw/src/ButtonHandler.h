#pragma once

#include <cstddef>

class ButtonHandler final
{
  public:
	explicit ButtonHandler(uint8_t pinButton);
	~ButtonHandler() = default;

	ButtonHandler(ButtonHandler const &) = delete;
	ButtonHandler(ButtonHandler &&) = delete;
	ButtonHandler &operator=(ButtonHandler const &) = delete;
	ButtonHandler &operator=(ButtonHandler &&) = delete;

	bool buttonPressedEvent();

  private:
	uint8_t pinButton{};
	bool buttonPressed{false};
};
