MAIN:=src/unicorn_rainbow.cpp

# these can be overwritten from shell
PORT:=/dev/ttyUSB0
BOARD:=esp8266:esp8266:nodemcuv2

COMPILER:=arduino
FLAGS+=--board "$(BOARD)"
FLAGS+=--port "$(PORT)"
FLAGS+=--pref sketchbook.path=build/
FLAGS+=--pref build.path=build/out
FLAGS+=--pref build.verbose=true
FLAGS+=--pref compiler.cpp.extra_flags="-std=c++11"

.PHONY: flash
flash: Makefile neopixel
	$(COMPILER) $(FLAGS) --upload "$(MAIN)"

.PHONY: build
build: Makefile neopixel
	$(COMPILER) $(FLAGS) --verify "$(MAIN)"

.PHONY: neopixel
neopixel: build/libraries/Adafruit_NeoPixel/Adafruit_NeoPixel.h

build/libraries/Adafruit_NeoPixel/Adafruit_NeoPixel.h: Makefile
	mkdir -p build
	$(COMPILER) $(FLAGS) --install-library "Adafruit NeoPixel:1.10.6"
	touch "$@"

.PHONY: clean
clean:
	rm -rf build/
