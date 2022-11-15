#pragma once

#include <cstddef>

#include <Arduino.h>

#include "LightManager.h"

namespace rainbow_unicorn
{

class RainbowUnicorn final
{
  public:
	explicit RainbowUnicorn();
	~RainbowUnicorn() = default;

	void initialize();
	void update();

	RainbowUnicorn(RainbowUnicorn const &) = delete;
	RainbowUnicorn(RainbowUnicorn &&) = delete;
	RainbowUnicorn &operator=(RainbowUnicorn const &) = delete;
	RainbowUnicorn &operator=(RainbowUnicorn &&) = delete;

  private:
	LightManager lightManager;
	bool buttonPressed{false};

	void updateButton();
};

} // namespace rainbow_unicorn
