INO:=$(wildcard *.ino)

# these can be overwriten from shell
ARDUINO_PORT:=/dev/ttyUSB0
ARDUINO_BOARD:=arduino:avr:nano

ARDUINO:=arduino
ARDU_FLAGS+=--board "$(ARDUINO_BOARD)"
ARDU_FLAGS+=--port "$(ARDUINO_PORT)"
ARDU_FLAGS+=--pref sketchbook.path=build/
ARDU_FLAGS+=--pref build.path=build/out
ARDU_FLAGS+=--pref build.verbose=true


.PHONY: flash
flash: Makefile fastled
	$(ARDUINO) $(ARDU_FLAGS) --upload "$(INO)"

.PHONY: build
build: Makefile fastled
	$(ARDUINO) $(ARDU_FLAGS) --verify "$(INO)"

.PHONY: fastled
fastled: build/libraries/FastLED/src/FastLED.h

build/libraries/FastLED/src/FastLED.h: Makefile
	mkdir -p build
	$(ARDUINO) $(ARDU_FLAGS) --install-library "FastLED:3.5.0"
	touch "$@"

.PHONY: clean
clean:
	rm -rf build/
