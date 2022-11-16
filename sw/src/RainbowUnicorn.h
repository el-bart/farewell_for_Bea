#pragma once

#include <cstddef>

#include <Arduino.h>

#include "LightManager.h"

// REVIEW: for project this size i'd skip (named) namespaces altogether. :)
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
    // REVIEW: i'd pull out button-related logic into a separate class - that'd simplify state transition and probably make this class redundant, as whole logic would boild down to create LightManager and ButtonHandler.
	bool buttonPressed{false};

	void updateButton();
};

} // namespace rainbow_unicorn
