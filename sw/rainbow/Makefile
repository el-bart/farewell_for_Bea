# can be overwritten from shell
PIO_PORT:=/dev/ttyUSB0

.PHONY: flash
flash: Makefile build
	pio run --disable-auto-clean --target upload --upload-port "$(PIO_PORT)"

.PHONY: build
build: Makefile
	pio run --disable-auto-clean

.PHONY: clean
clean:
	rm -rf build/
	rm -rf pio_core/
