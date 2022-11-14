MAIN:=src/unicorn_rainbow.cpp

# these can be overwritten from shell
PORT:=/dev/ttyUSB0
BOARD:=esp8266:esp8266:nodemcuv2

#COMPILER:=arduino
#FLAGS+=--board "$(BOARD)"
#FLAGS+=--port "$(PORT)"
#FLAGS+=--pref sketchbook.path=build/
#FLAGS+=--pref build.path=build/out
#FLAGS+=--pref build.verbose=true
#FLAGS+=--pref compiler.cpp.extra_flags="-std=c++11"

.PHONY: flash
flash: Makefile
	pio run --disable-auto-clean

.PHONY: build
build: Makefile
	pio run --disable-auto-clean

.PHONY: clean
clean:
	rm -rf build/
	rm -rf pio_core/
